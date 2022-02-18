#include <sstream>
#include "Utils.h"

Utils::Utils()
{
}

Utils::~Utils()
{
}

std::string Utils::intToString(int value)
{
	std::string temp;
	std::stringstream ss;
	ss << value;
	ss >> temp;
	return temp;
}