#include "carte.h"

// constructor carte

carte::carte(std::string titlu, std::string nume, std::string editura, int pret_baza,int stoc)
{
	this->_titlu = titlu;
	this->_nume = nume;
	this->_editura = editura;
	this->_pret_baza = pret_baza;
	this->stoc = stoc;
}


