#include "FixedI2C/DataChecker.h"

uint8_t DataChecker::calc(uint8_t *data, unsigned int length)
{
	_seed = 0;
	return update(data, length);
}

uint8_t DataChecker::update(uint8_t *data, unsigned int length)
{
	uint8_t crc = _seed;
	uint8_t extract = 0;
	uint8_t sum = 0;

	for (unsigned int i = 0; i < length; i++) 
	{
		extract = *data;

		for (int8_t j = 8; j; j--) 
		{
			sum = (crc ^ extract) & 0x01;
			crc >>= 1;
			if (sum) 
				crc ^= 0x8C;

			extract >>= 1;
		}

		data++;
	}

	return crc;
}