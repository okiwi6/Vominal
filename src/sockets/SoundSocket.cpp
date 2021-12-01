#include "SoundSocket.hpp"

SoundServer::SoundServer(uint16_t port):
port(port)
{
    if(listener.listen(port) != sf::Socket::Done) {
        throw std::runtime_error("Could not open port " << port);
    }
    
    // wait for new connection
    sf::TcpSocket client;
    if(listener.accept(client) != sf::Socket::Done)
}