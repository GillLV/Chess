#include "BoardString.h"

std::string& CBoardString::operator=(const std::string& input)
{
	//Guard agaisnt self assignment
	if (this->baordStr == input)
		return this->baordStr;


}
