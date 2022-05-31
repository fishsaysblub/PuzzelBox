#include "I2C_Controller.h"

// Build with: g++ -o I2CController ctest.cpp DataChecker.cpp DataWrapper.cpp DataUnwrapper.cpp I2C_Controller.cpp I2C.cpp -I ./

int test_write()
{
	uint8_t i2c_data_length = 3;
    int rv;

    unsigned char values[i2c_data_length] = 
	{
		0x04, 0x00, 0x04
	};

    rv = I2C_Controller::Instance().write_device(0x40, 0x02, i2c_data_length, values);

    if (rv < 0)
    {
        std::cerr << "Writing I2C Bus Error..." << std::endl;
        return -1;
    }

	return 0;
}

int test_read()
{
	uint8_t i2c_data_length = 5;
    int rv;
    unsigned char buffer[i2c_data_length + 1] = {0};

	rv = I2C_Controller::Instance().read_device(0x40, 0x22, i2c_data_length, buffer);

    if (rv < 0)
    {
        std::cerr << "Reading I2C Bus Error..." << std::endl;
        return -1;
    }

    std::cout << "Buffer Value: " ;

    for (int i = 0; i < i2c_data_length; i++)
    {
        std::cout << "0x" << std::setfill('0') << std::setw(2) << std::hex << (int) buffer[i] << " " ;
    }

	std::cout << std::endl;
	return 0;
}

int main()
{
    // Add device by hex.
	I2C_Controller::Instance().add_device(0x40);

    // Active check to device status.
    uint8_t status = I2C_Controller::Instance().pollDeviceStatus(0x40);

    std::cout << "Status [" << (int)status << "]" << std::endl;

    // Test mail, status will be taken and returned in next poll.
	// put your setup code here, to run once:
	MailP1Type* test = AllocateMail<MailP1Type>(0x00, 0x40, sizeof(MailP1Type) /* + sizeof(data_array)*/);
	test->Primitive = GAME_START;
	test->status = SUCCESS;
	test->P1 = 0xFF;

    // Sending game data.
    I2C_Controller::Instance().send_mail(test);

    status = I2C_Controller::Instance().pollDeviceStatus(0x40);
    
    std::cout << "Status [" << (int)status << "]" << std::endl;
    return 0;
}