#include <sstream>
#include "Utils.h"

Utils::Utils()
{
}

Utils::~Utils()
{
}

std::string Utils::int_to_string(int value)
{
	std::string temp;
	std::stringstream ss;
	ss << value;
	ss >> temp;
	return temp;
}