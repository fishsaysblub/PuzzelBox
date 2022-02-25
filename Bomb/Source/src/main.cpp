#include <iostream>
#include <AssembleConnection.h>
#include <Bom.h>
#include <thread>
#include <alsa/asoundlib.h>
#include <cmath>
#include <Peripherals/Tca8418Interface.h>
#include <linux/spi/spidev.h>
#include <JumperInterconnect.h>

int main()
{
    try
    {
        // Main game class
        Bom bom;
        
        // Non blocking gameloop while game is running
        while (bom.loop()) 
        {
            // Update communication here
        }

        std::cout << "END GAME" << std::endl;
    }
    catch (const char *err)
    {
        std::cerr << err << std::endl;
        return 1;
    }
    catch (std::string &err)
    {
        std::cerr << err << std::endl;
        return 1;
    }
    catch (const std::exception &err)
    {
        std::cerr << err.what() << std::endl;
        return 1;
    }
    return 0;
}