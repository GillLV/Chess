#ifndef H_BOARDSTRING
#define H_BOARDSTRING

#include <String>

class CBoardString {

private: 
	std::string baordStr;

public:

	std::string& operator=(const std::string& input);

};

#endif