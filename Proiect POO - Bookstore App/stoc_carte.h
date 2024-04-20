#ifndef A_STOCCARTE
#define A_STOCCARTE
#include <iostream>
#include <string>
#include <list>

class stoc_carte {
private:
	
	std::string _titlu;
public:
	int stoc;
	stoc_carte(std::string titlu);
	bool gasireStoc(std::string titlu);
};
#endif
