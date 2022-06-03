#include "../include/StateMachine.h"
#include "../include/GpioManager.h"

#include "iostream"
#include "sstream"
#include <chrono>
#include <stdio.h>
#include <sio_client.h>

/**************************************************************
 * @brief Client instance
 * 
 **************************************************************/
sio::client* h;
bool connected = false;
unsigned long lastMillis = 0;

unsigned long millis()
{
	std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(
		std::chrono::system_clock::now().time_since_epoch());
	unsigned long millis = ms.count();
	return millis;
}

/**************************************************************
 * @brief Execute shell command
 * 
 * @param cmd Command string
 * @return std::string Command result
 **************************************************************/
std::string exec(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}

std::string getmac() {
    return exec("getmac");
}

std::string getip() {
    return exec("/home/pi/socketCom/getip.sh");
}

/**************************************************************
 * @brief On connect example
 * 
 **************************************************************/
void on_connect()
{
    h->socket()->emit("device_error", sio::string_message::create("Panic"));
    connected = true;
}

/**************************************************************
 * @brief On message event example
 * 
 **************************************************************/
void OnMessage(sio::event &)
{
    std::cout << "Type req\n";
}

void OnBlink(sio::event &)
{
	GpioManager::instance().blink_leds();
}

int main()
{
	// Start state machine
	StateMachine::instance().start_engine();

	// Create client
    h = new sio::client();

    // Make auth object
    auto device_data = sio::object_message::create();
    device_data->get_map()["token"] = sio::string_message::create(std::string("A123"));
    device_data->get_map()["type_id"] = sio::int_message::create(2);
    device_data->get_map()["mac_address"] = sio::string_message::create(getmac());
    device_data->get_map()["ip_address"] = sio::string_message::create(getip());

    /**************************************************************
     * @brief Connect to socket with auth settings
     **************************************************************/
    //h->connect("http://192.168.199.1:5000", device_data);

	while(1)
	{
        // Connect
        if (!connected && millis() > lastMillis + 10'000)
        {
            std::cout << "Connecting\n";
            h->connect("http://192.168.199.1:5000", device_data);
            lastMillis = millis();
        }

		h->set_open_listener(&on_connect);
        h->socket()->on("type_req", &OnMessage);
        h->socket()->on("device_ident_req", &OnBlink);

		StateMachine::instance().update();
	}

	return 0;
}