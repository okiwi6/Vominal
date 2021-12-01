#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

//std
#include <string>
#include <stdint.h>

class SoundServer {
    public:
        SoundServer(uint16_t port);
        ~SoundSocketHandler();
    private:
        sf::TcpSocket socket;
        uint16_t port;
}

class SoundClient {
    public:
        SoundClient(std::string inet_addr, uint16_t port);
        ~SoundClient();
    private:
        sf::TcpListener listener;
        uint16_t port;
        std::string inet_addr;
}