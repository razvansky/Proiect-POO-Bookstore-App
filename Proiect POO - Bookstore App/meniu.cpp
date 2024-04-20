#include "meniu.h"


// constructor meniu
// initializez lista de utilizatori(utilizator.txt) si stocul de carti(stoc.txt)

Meniu::Meniu()
{
	std::string nume, prenume, cnp, email, parola;
	utilizator* u;
	std::ifstream F(fisier_util);
	if (!F.is_open())
	{
		std::cout << "Deschiderea fisierului utilizator.txt a esuat!" << std::endl;
		exit(0);
	}
	while (F>>email)
	{
		F  >> parola >> nume >> prenume >> cnp;
		u = new utilizator(nume, prenume, email, parola, cnp);
		lista_utilizatori.push_back(u);
	}
	F.close();

	int tip, pretbaza, nrpag, an,stoc;
	std::string titlu,editura;
	carte* c;
	carte_fictiune* cf;
	carte_normala* cn;

	std::ifstream f(fisier_stoc);
	if (!f.is_open())
	{
		std::cout << "Deschiderea fisierului stoc.txt a esuat!" << std::endl;
		exit(0);
	}

	while (f>>tip)
	{
		if (tip == 1)
		{
			f >> titlu >> editura >> pretbaza >> nrpag >> stoc ;
			std::getline(f, nume);
			cf = new carte_fictiune(titlu, nume, editura, pretbaza, nrpag, stoc);
			c = (carte*)cf;
			stoc_carti.push_back(c);
		}
		else if (tip == 2)
		{
			f >> titlu >> editura >> pretbaza >> an >> stoc;
			std::getline(f, nume);
			cn = new carte_normala(titlu, nume, editura, pretbaza, an, stoc);
			c = (carte*)cn;
			stoc_carti.push_back(c);
		}
	}

	f.close();
}

// loopul pentru meniu
// am pus in header cu #define nume pentru optiuni ca sa fie mai usor de inteles
// doar se apeleaza functiile pentru fiecare optiune/status
// fiecare functie transmite inapoi in var _status ,nr reprezentativ statusului

void Meniu::loop() {
	bool iesit = false;
	do {
		//system("cls");
		switch (_status)  // este initializat cu 0 _status in header
		{
		case ST_IESIRE:
			iesit = iesire();
			break;
		case ST_PORNIRE:
			pornire(_status);
			break;
		case ST_CONECTARE:
			conectare(_status);
			break;
		case ST_CONTACT:
			contact(_status);
			break;
		case ST_CONECTAT:
			conectat(_status);
			break;
		case ST_REZERVARE:
			rezervare(_status);
			break;
		default:
			_status = ST_PORNIRE;
			break;
		}

	} while (!iesit);
}

// prima "pagina" cu asta practic se deschide programul
// se citeste optiunea 
// in rest nimic prea special aici

void Meniu::pornire(int& status)
{
	_status_anterior = ST_PORNIRE;
	for (std::string x : opt_pornire)
	{
		std::cout << x << std::endl;
	}
	std::cin >> status;
	switch (status)
	{
	case ST_CONECTARE:
		break;
	case ST_CONTACT:
		break;
	case 3:
		status = ST_IESIRE;
		break;
	default:
		std::cout << "Incorect!" << std::endl;
		status = _status_anterior;
		break;
	}
}

// functia care afiseaza pagina pentru conectare
// in fctie de optiuni se executa cod/apeleaza diferite fctii : inregistrare,resetare
// LA CONECTARE
// se verifica cu o functie ce apartine clasei utilizator daca parola si emailul corespund (fctia returneaza bool) daca = true se duce mai departe,daca = false se incearca din nou
void Meniu::conectare(int& status)
{
	_status_anterior = ST_PORNIRE;
	bool incercare = false;
	std::string utilizator, parola;

		for (std::string x : opt_conectare)
		{
			std::cout << x << std::endl;
		}
		std::cin >> status;
		switch (status)
		{
		case ST_CONECTARE_AUTENTIFICARE:
			do {
				std::cout << "email:"; std::cin >> utilizator;
				std::cout << "parola:"; std::cin >> parola;
				for (auto x : lista_utilizatori)
				{
					if (x->conectare(utilizator, parola))
					{
						status = ST_CONECTAT;
						mail_conectat = utilizator;
						return;
					}
				}

				std::cout << "email sau parola incorecta,vrei sa incerci din nou?da/nu(1/0)"; std::cin >> incercare;

			} while (incercare);
			break;
		case ST_CONECTARE_INREGISTRARE:
			if (inregistrare())
				status = ST_CONECTAT;
			else
				status = ST_CONECTARE;
			break;
		case ST_CONECTARE_RESETAREPAROLA:
			std::cout << "Email:"; std::cin >> utilizator;
			status = resetare_parola(utilizator);
			break;
		case ST_CONECTARE_INAPOI:
			status = _status_anterior;
			break;
		default:
			std::cout << "Incorect" << std::endl;
			break;
		}
}

// functia cae afiseaza pagina de contact
// de aici pleaca sesizarea , se citesc datele se pun intr-un string le scriu intr-un fisier(e necesar ptr a trimite mail cu curl) dupa care se deschide curl
// cu comanda WinExec

void Meniu::contact(int& status) 
{
	std::string nume_prenume,nume, prenume, motiv, continut,cnp;
	fisier f(fisier_email);


	if (_conectat)
		_status_anterior = ST_CONECTAT;
	else
		_status_anterior = ST_PORNIRE;

	for (std::string x : opt_contatct)
	{
		std::cout << x << std::endl;
	}

	std::cin >> status;
	switch (status)
	{
	case ST_CONTACT_SESIZARE:
		std::cout << "Nume:"; std::cin >> nume;
		std::cout << "Prenume:"; std::cin >> prenume;
		std::cout << "CNP:"; std::cin >> cnp;
		std::cin.ignore();
		std::cout << "Motiv:"; std::getline(std::cin,motiv);

		nume_prenume = nume + " " + prenume;

		continut = "Buna ziua,\nSubsemnatul," + nume_prenume + ",avand CNP : " + cnp + "\n" + motiv + "\nMultumesc,\n"+ nume_prenume;
		
		if (!f.scriere(continut))
		{
			std::cout << std::endl << "A esuat salvarea sesizarii!" << std::endl;
		}
		else
		{
				if(WinExec("curl --ssl-reqd --url smtps://smtp.gmail.com:465 --user bookstorepoo@gmail.com:srgmazrgasjvyzkp --mail-from bookstorepoo@gmail.com --mail-rcpt razvan.peia@student.upt.ro --upload-file email.txt --silent", SW_HIDE))
				{
					std::cout << std::endl << "Sesizarea a fost trimisa" << std::endl;
				}
		}
		
		status = _status_anterior;

		break;
	case ST_CONTACT_INAPOI:
		status = _status_anterior;
		break;
	default:
		std::cout << "Incorect!" << std::endl;
		status = ST_CONTACT;
		break;
	}

}

// functia care afiseaza pagina odata ce s-a trecut de conectare
// nimic prea special,doar citeste 

void Meniu::conectat(int& status)
{
	_status_anterior = ST_CONECTARE;
	_conectat = true;

	for (std::string x : opt_conectat)
	{
		std::cout << x << std::endl;
	}
	std::cin >> status;
	switch (status) {
	case ST_CONECTAT_ACHZIMPR:
		status = ST_REZERVARE;
		break;
	case ST_CONECTAT_ISTORIC:
		istoric();
		status = ST_CONECTAT;
		break;
	case ST_CONECTAT_CONTACT:
		status = ST_CONTACT;
		break;
	case ST_CONECTAT_INAPOI:
		_conectat = false;
		status = _status_anterior;
		break;
	default:
		std::cout << "Incorect!" << std::endl;
		status = ST_CONECTAT;
		break;
	}
}

// functia care se afiseaza daca utilizatorul alege sa Cumpere/Imprumute
// in functie de urmatoarea alegere se afiseaza stocul si se apeleaza fctia ptr achizite/inchiriat

void Meniu::rezervare(int& status) 
{
	_status_anterior = ST_CONECTAT;
	for (std::string x : opt_rezervare)
	{
		std::cout << x << std::endl;
	}
	std::cin >> status;
	switch (status)
	{
	case ST_REZERVARE_ACHIZITE:
		for (auto x : stoc_carti)
		{
			x->afisare();
		}
		achizitie();
		status = _status_anterior;
		break;
	case ST_REZERVARE_IMPRUMUT:
		for (auto x : stoc_carti)
		{
			x->afisare();
		}
		inchiriere();
		status = _status_anterior;
		break;
	case ST_REZERVARE_INAPOI:
		status = _status_anterior;
		break;
	default:
		std::cout << "Incorect!" << std::endl;
		status = ST_REZERVARE;
		break;
	}
}

// fctia ptr istoric
// citeste din fisier informatiile
// fisierul e sub forma
// nume fisier: nume_utilizator.txt
// ///////////TEXT_FISIER/////////////////
// TOTAL CHELTUIT (int)
// LINII TEXT CU INFORMATIA DESPRE CARTIILE CUMPARATE/INCHIRIATE
//////////////////////////////////////////

void  Meniu::istoric() 
{
	int sold;
	std::string txt;
	std::ifstream f("istoric\\" + mail_conectat + ".txt");
	if (!f.is_open()) 
	{
		std::cout << "Fisierul pentru istoric nu a putut fi deschis!" << std::endl;
		return;
	}
	f >> sold;
	std::cout << "Total cheltuit:" << sold << std::endl;
	while (std::getline(f,txt))
	{
		std::cout << txt << std::endl;
	}
}

// Functia pentru inregistrare
// intr-un bloc try verific daca cnp si email sunt unice si parola>3
// in catch urmeaza sa scriu in fisier(log.txt) greselile 
// daca totul este in regula se adauga un nou utilizator in lista_utilizatori si acesta este scris la finalul fisierului utilizatori.txt
// functia e de tip bool,daca s-a parcurs rezultatul e true,daca criteriile ptr inregistrare nu au fost indeplinitate se returneaza false

bool Meniu::inregistrare()
{
	fisier log(fisier_log);
	utilizator* u;
	std::string nume, prenume, cnp, email, parola,continut;
	fisier f(fisier_util);
	std::cout << "Email-ul si CNP trebuie sa fie unice(sa nu existe deja in baza de date), parola trebuie sa contina minim 3 caractere" << std::endl;
	try
	{
		std::cout << "Nume:"; std::cin >> nume;
		std::cout << "Prenume:"; std::cin >> prenume;
		std::cout << "CNP:"; std::cin >> cnp;
		for (auto x : lista_utilizatori)
		{
			if (x->getCNP() == cnp)
			{
				throw 1;
			}
		}
		std::cout << "Email:"; std::cin >> email;
		for (auto x : lista_utilizatori)
		{
			if (x->getEmail() == email)
			{
				throw 2;
			}
				
		}
		std::cout << "Parola:"; std::cin >> parola;
		if (parola.size() < 3)
		{
			throw std::string("Parola trebuie sa contina minim 3 caractere!");
		}
	}
	catch (int x)
	{
		if (x == 1)
		{
			log.scriereApp("Acest CNP exista deja in baza de date va recomandam sa resetati parola! CNP:"+cnp+"\n");
			std::cout << "Acest CNP exista deja in baza de date va recomandam sa resetati parola!" << std::endl;
		}
		else if (x == 2)
		{
			log.scriereApp("Acest email exista deja in baza de date va recomandam sa resetati parola! email:" + email+"\n");
			std::cout << "Acest email exista deja in baza de date va recomandam sa resetati parola!" << std::endl;
		}
		return false;
	}
	catch (std::string s)
	{
		log.scriereApp(s+"\n");
		std::cout << s<<std::endl;
		return false;
	}
	continut = email + " " + parola + " " + nume + " " + prenume + " " + cnp + "\n";

	u = new utilizator(nume, prenume, email, parola, cnp);
	lista_utilizatori.push_back(u);
	mail_conectat = email;
	f.scriereApp(continut);
	return true;
}


// functia ptr resetarea parolei
// se verifica daca emailul introdus de utilizator exista -- daca nu exista se iese din functie
// -- daca exista se reseteaza parola (fctia x->resetare(email) care returneaza bool) si urmeaza scrierea in fisier
// se goleste fisierului anterior utilizator.txt mai apoi fiind fiecare utilizator scris rand cu rand

int Meniu::resetare_parola(std::string email)
{
	bool resetat = false;
	fisier f(fisier_util);
	for (auto x : lista_utilizatori)
	{
			if(resetat=x->resetare(email))
				break;
	}
	if (!resetat)
	{
		std::cout << "Emailul introdus nu exista!" << std::endl;
		return ST_CONECTARE;
	}

	f.scriere("");
	for (auto x : lista_utilizatori)
	{
		f.scriereApp(x->getUtilizator() + "\n");
	}
	mail_conectat = email;
	return ST_CONECTAT;
}

// functia pentru achizite
// se verifica daca exista cartea cautata ,dca exista se adauga in istoricul utilizatorului conectat + schimbarea totalului cheltuit
// tot odata prin (*x) cu suprascrierea operatorului "--" scad cu 1 din stocul de carti

void Meniu::achizitie()
{
	int k;
	fisier f("istoric\\" + mail_conectat + ".txt");
	fisier fs(fisier_stoc);
	std::ifstream in("istoric\\" + mail_conectat + ".txt");
	std::list<std::string> istoric;
	std::string linie,titlu;
	in >> k;
	while (std::getline(in,linie))
	{
		istoric.push_back(linie);
	}
	in.close();
	std::cout << "Titlu cartii pe care doriti sa o cumparati:"; std::cin >> titlu;
	for (carte* x : stoc_carti)
	{
		if(x->getTitlu()==titlu)
		{
			if (x->exstoc())
			{
				(*x)--;
				k += x->pret();
				linie = "Vandut:" + x->getTitlu() + x->getNume() + " " + x->getEditura() + " Pret:" + std::to_string(x->pret());
				istoric.push_back(linie);
			}
			else
			{
				std::cout << "Cartea nu mai este in stoc" << std::endl;
				return;
			}
		}
	}
	f.scriere(std::to_string(k));
	for (std::string x : istoric)
	{
		f.scriereApp(x+"\n");
	}
	fs.scriere("");
	for (auto x : stoc_carti)
	{
		fs.scriereApp(x->getCarteStoc()+"\n");
	}
}

// functia ptr inchiriere 
// este cam acelasi lucru 
// singura diferenta ar fi ca in istoric nu se modifica total cheltuilei si inloc de vandut: scrie inchiriat:

void Meniu::inchiriere()
{
	int k;
	fisier f("istoric\\" +  mail_conectat + ".txt");
	fisier fs(fisier_stoc);
	std::ifstream in("istoric\\" + mail_conectat + ".txt");
	std::list<std::string> istoric;
	std::string linie, email;
	in >> k;
	while (std::getline(in, linie))
	{
		istoric.push_back(linie);
	}
	in.close();
	std::cout << "Titlu cartii pe care doriti sa o inchiriati:"; std::cin >> email;
	for (carte* x : stoc_carti)
	{
		if (x->getTitlu() == email)
		{
			if (x->exstoc())
			{
				(*x)--;
				linie = "Inchiriat:" + x->getTitlu() + x->getNume() + " " + x->getEditura();
				istoric.push_back(linie);
			}
			else
			{
				std::cout << "Cartea nu mai este in stoc" << std::endl;
				return;
			}
		}
	}
	f.scriere(std::to_string(k));
	for (std::string x : istoric)
	{
		f.scriereApp(x + "\n");
	}
	fs.scriere("");
	for (auto x : stoc_carti)
	{
		fs.scriereApp(x->getCarteStoc() + "\n");
	}
}

// fctia de iesire
// se sterg obiectele din liste

bool Meniu::iesire()
{
	for (auto x : lista_utilizatori)
		delete x;
	for (auto x : stoc_carti)
		delete x;
	return true;
}

