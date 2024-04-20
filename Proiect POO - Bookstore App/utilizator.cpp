#include "utilizator.h"

// constructor utilizator
// initializez datele
// daca nu exista fisierul de istoric ptr utilizator il creez cu suma cheltuita 0

utilizator::utilizator(std::string nume, std::string prenume, std::string email, std::string parola,std::string cnp)
{
	std::string zz;
	this->_nume = nume;
	this->_prenume = prenume;
	this->_email = email;
	this->_parola = parola;
	this->_cnp = cnp;
	fisier f("istoric\\" + email + ".txt");
	if (!f.citire(zz,true))
	{
		f.scriere("0\n");
	}
}

// functia care verifica daca mailul si parola corespund

bool utilizator::conectare(std::string email, std::string parola)
{
	if (this->_email == email)
	{
		if (this->_parola == parola)
		{
			return true;
		}
	}
	return false;
}

// functia care schimba parola

bool utilizator::resetare(std::string email)
{
	std::string parola;
	try
	{
		if (this->_email == email)
		{
			std::cout << "Introduceti noua parola:"; std::cin >> parola;
			if (parola.size() < 3)
				throw new std::exception("Parola trebuie sa contina minim 3 caractere!");
			return true;
		}
		return false;
	}
	catch (std::exception* e)
	{
		std::cout << e->what();
		return false;
	}
}

// cele 3 fctii de mai jos returneaza diverse informatii necesare in program

std::string utilizator::getEmail()
{
		return this->_email;
}

std::string utilizator::getUtilizator()
{
	return this->_email + " " + this->_parola + " " + this->_nume + " " + this->_prenume + " " + this->_cnp;
}

std::string utilizator::getCNP()
{
	return this->_cnp;
}