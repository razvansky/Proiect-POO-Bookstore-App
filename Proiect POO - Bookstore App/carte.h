#ifndef A_CARTE
#define A_CARTE

#include <iostream>
#include <string>
#include <list>

#include "fisier.h"


class carte {
private:
	std::string anterior = "";
	std::string _titlu, _nume, _editura;
	bool _vandut = false;
	bool _imprumut = false;

public:
	carte(std::string titlu, std::string nume, std::string editura, int pret_baza,int stoc);
	virtual int pret() = 0;
	virtual int tip() = 0;
	virtual void afisare() = 0;
	std::string getTitlu() {
		return this->_titlu;
	}
	std::string getNume() {
		return this->_nume;
	}
	std::string getEditura() {
		return this->_editura;
	}
	virtual std::string getCarteStoc() = 0;

	// suprascriere -- : Obsvertie cerinta;
	carte& operator--(int)
	{
		this->stoc--;
		return *this;
	}
	bool exstoc()
	{
		if (this->stoc == 0)
			return false;
		return true;
	}

protected:
	int stoc;
	int _pret_baza;
};

// mosteneste carte 

class carte_fictiune : private carte {
private:
	int _nr_pag;
public:
	carte_fictiune(std::string titlu, std::string nume, std::string editura, int pret_baza, int nr_pag,int stoc) : carte(titlu, nume, editura, pret_baza,stoc)
	{
		this->_nr_pag = nr_pag; 
	};
	int pret() override
	{
		return this->_pret_baza + _nr_pag;
	}
	int tip() override
	{
		return 1;
	}
	void afisare() override
	{
		std::cout << "Titlu:" << this->getTitlu() << std::endl;
		std::cout << "Nume autor:" << this->getNume() << std::endl;
		std::cout << "Editura:" << this->getEditura() << std::endl;
		std::cout << "Pret:" << this->pret() << std::endl;
		std::cout << "Nr pagini:" << this->_nr_pag << std::endl;
		std::cout << "Stoc:" << this->stoc << std::endl;
	}
	
	// fctia folosita pentru stoc.txt 
	std::string getCarteStoc() override
	{
		std::string l;
		l = "1 " + this->getTitlu() + " " +  this->getEditura() + " " + std::to_string(this->_pret_baza) + " " + std::to_string(this->_nr_pag) + " " + std::to_string(this->stoc) + this->getNume();
		return l;
	}
};

// mosteneste carte 

class carte_normala : private carte {
private:
	int _an;
public:
	carte_normala(std::string titlu, std::string nume, std::string editura, int pret_baza, int an,int stoc) : carte(titlu, nume, editura, pret_baza,stoc) 
	{ 
		this->_an = an;
	};
	int pret() override
	{
		return this->_pret_baza - (25 * this->_an);
	}
	int tip() override
	{
		return 2;
	}
	void afisare() override
	{
		std::cout << "Titlu:" << this->getTitlu() << std::endl;
		std::cout << "Nume autor:" << this->getNume() << std::endl;
		std::cout << "Editura:" << this->getEditura() << std::endl;
		std::cout << "Pret:" << this->pret() << std::endl;
		std::cout << "An:" << this->_an << std::endl;
		std::cout << "Stoc:" << this->stoc << std::endl;
	}
	std::string getCarteStoc() override
	{
		std::string l;
		l = "2 " + this->getTitlu() + " " + this->getEditura() + " " + std::to_string(this->_pret_baza) + " " + std::to_string(this->_an) + " " + std::to_string(this->stoc) + this->getNume();
		return l;
	}
	
};

#endif 
