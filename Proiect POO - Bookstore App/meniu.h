#ifndef A_MENIU
#define A_MENIU

#include <iostream>
#include <list>
#include <string>
#include <Windows.h>

#include "fisier.h"
#include "utilizator.h"
#include "carte.h"

#define ST_IESIRE -1
#define ST_PORNIRE 0
#define ST_CONECTARE 1
#define ST_CONTACT 2
#define ST_CONECTAT 3
#define ST_REZERVARE 4

#define ST_CONECTARE_AUTENTIFICARE 1
#define ST_CONECTARE_INREGISTRARE 2
#define ST_CONECTARE_RESETAREPAROLA 3
#define ST_CONECTARE_INAPOI 4

#define ST_CONTACT_SESIZARE 1
#define ST_CONTACT_INAPOI 2

#define ST_CONECTAT_ACHZIMPR 1
#define ST_CONECTAT_ISTORIC 2
#define ST_CONECTAT_CONTACT 3
#define ST_CONECTAT_INAPOI 4

#define ST_REZERVARE_ACHIZITE 1
#define ST_REZERVARE_IMPRUMUT 2
#define ST_REZERVARE_INAPOI 3


const std::string fisier_util  = "db\\utilizatori.txt";
const std::string fisier_email = "email.txt";
const std::string fisier_stoc  = "db\\stoc.txt";
const std::string fisier_log   = "db\\log.txt";

class Meniu {
private:
	int _status_anterior = 0;
	int _status = 0;
	bool _conectat = false;
	std::string mail_conectat;

	std::list<utilizator*> lista_utilizatori;
	std::list<carte*> stoc_carti;
	std::list<std::string> opt_pornire = 
	{ "Alegeti o optiune:",
		"\t1. Conectare",
		"\t2. Contact",
		"\t3. Iesire"};

	std::list<std::string> opt_conectare =
	{"Alegeti o optiune :",
	"\t1. Autentificare",
	"\t2. Inregistrare",
	"\t3. Resetare parola",
	"\t4. Inapoi"};

	std::list<std::string> opt_contatct =
	{"Suport tehnic",
	"In cazul in care intalniti dificultati echipa de suport va sta la dispozitie",
	"Tot ce trebuie sa faceti este completati urmatorul formular in care trebuie descrisa problema.",
	"Alegeti o optiune",
	"\t1. Trimitere sesizare",
	"\t2. Inapoi"};

	std::list<std::string> opt_conectat =
	{ "Alegeti o optiune :",
	"\t1. Achizite/Imprumut",
	"\t2. Istoric",
	"\t3. Contact",
	"\t4. Inapoi.(delogare)" };

	std::list<std::string> opt_rezervare =
	{ "Alegeti optiunea:",
	"\t1.Achizite",
	"\t2.Imprumut",
	"\t3.Inapoi" };

	
	void pornire(int& status);
	void conectare(int& status);
	void contact(int& status); 
	void conectat(int& status);
	void rezervare(int& status);
	bool iesire();
	void istoric();
	bool inregistrare();
	int resetare_parola(std::string email);
	void achizitie();
	void inchiriere();
public:
	Meniu();
	void loop();
};

#endif