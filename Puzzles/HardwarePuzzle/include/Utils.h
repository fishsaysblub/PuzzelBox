#pragma once
#include <string>

/**
 * @brief Class used to share utility functions any other class needed.
 */
class Utils
{
public:
	/**
	 * @brief Construct a new Utils object.
	 */
    Utils();
	/**
	 * @brief Destroy the Utils object.
	 */
    virtual ~Utils();

	/**
	 * @brief Method to convert integer into std::string.
	 * 
	 * @param value Integer which is converted.
	 * @return std::string Output std::string.
	 */
	std::string int_to_string(int value);
};