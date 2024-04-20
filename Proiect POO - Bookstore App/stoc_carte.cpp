#include "stoc_carte.h"

stoc_carte::stoc_carte(std::string titlu) {
	stoc = 0;
	this->_titlu = titlu;
}

bool stoc_carte::gasireStoc(std::string titlu)
{
	if (this->_titlu == titlu)
	{
		return true;
	}
	return false;
}