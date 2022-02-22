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
        //        Peripherals::Sound sound;
        //        sound.Biem();
        //        std::this_thread::sleep_for(std::chrono::seconds(5));

        Bom bom;
        bom.WaitForArmed();
        bom.WaitForCountdown();
        bom.CountDown();
        bom.WaitForClose();

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