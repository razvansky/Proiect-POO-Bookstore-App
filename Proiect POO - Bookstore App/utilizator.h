#ifndef A_UTILIZATOR
#define A_UTILIZATOR

#include <iostream>
#include <string>
#include <list>

#include "fisier.h"


class utilizator {
private:
	std::string _nume, _prenume, _email, _parola,_cnp;
public:
	utilizator(std::string nume, std::string prenume, std::string email, std::string parola,std::string cnp); 
	bool conectare(std::string email, std::string parola);
	bool resetare(std::string email);
	std::string getEmail();
	std::string getUtilizator();
	std::string getCNP();
};

#endif