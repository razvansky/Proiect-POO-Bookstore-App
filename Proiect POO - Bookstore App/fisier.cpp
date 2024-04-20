#include "fisier.h"

// constructorul initializez numele
fisier::fisier(std::string nume_fisier)
{
	this->_nume_fisier = nume_fisier;
}

// fctia de citire din fisier
// returneaza bool in functie de reusita

bool fisier::citire(std::string& continut,bool silent)
{
	std::ifstream f(this->_nume_fisier);
	if (!f.is_open())
	{
		if(!silent)
			std::cout << "Fisierul \"" << this->_nume_fisier << "\" nu a putut fi deschis!" << std::endl;
		return false;
	}
	while (f)
		{
			continut = f.get();
		}
	f.close();
	return true;
}


// fctia de scriere(rescrie tot) din fisier
// returneaza bool in functie de reusita

bool fisier::scriere(std::string continut)
{
	std::ofstream f(this->_nume_fisier);
	if (!f.is_open())
	{
		std::cout << "Fisierul \"" << this->_nume_fisier << "\" nu a putut fi deschis!" << std::endl;
		return false;
	}
	f << continut;
	f.close();
	return true;
}


// fctia de scriere append ( scrie in continuare nu rescrie tot ) din fisier
// returneaza bool in functie de reusita

bool fisier::scriereApp(std::string continut)
{
	std::ofstream f(this->_nume_fisier,std::fstream::app);
	if (!f.is_open())
	{
		std::cout << "Fisierul \"" << this->_nume_fisier << "\" nu a putut fi deschis!" << std::endl;
		return false;
	}
	f << continut;
	f.close();
	return true;
}

