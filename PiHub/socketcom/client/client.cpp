/**************************************************************
 * @file client.cpp
 * @author Jef B (hj.baars@student.avans.nl)
 * @brief Client example
 * @version 0.1
 * @date 2022-02-22
 * 
 * @copyright Copyright (c) 2022
 * 
 **************************************************************/
#include "iostream"
#include "sstream"
#include <sio_client.h>

/**************************************************************
 * @brief Client instance
 * 
 **************************************************************/
sio::client* h;

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
    return exec("/home/jef/Git/PuzzelBox/PiHub/localcmd/getip.sh");
}

/**************************************************************
 * @brief On connect example
 * 
 **************************************************************/
void on_connect()
{
    h->socket()->emit("device_error", sio::string_message::create("Panic"));
}

/**************************************************************
 * @brief On message event example
 * 
 **************************************************************/
void OnMessage(sio::event &)
{
    std::cout << "Type req\n";
}

// demo2.C - Sample C++ program 
int main(void) 
{
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
    h->connect("http://127.0.0.1:5000", device_data);
    
    // Loop
    std::cout << "Start\n";
    while (true)
    {
        h->set_open_listener(&on_connect);
        h->socket()->on("type_req", &OnMessage);
    }
    
    return 0;
}

/**
 * Make
 * g++ client.cpp -o client -L. -lsioclient -lpthread
 * 
 */