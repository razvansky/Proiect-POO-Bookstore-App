#ifndef A_FISIER
#define A_FISIER


#include <iostream>
#include <fstream>
#include <string>

class fisier {
private:
	std::string _nume_fisier;
public:
	fisier(std::string nume_fisier);
	bool scriere(std::string continut);
	bool citire(std::string& continut,bool silent);
	bool scriereApp(std::string continut);

};


#endif 
