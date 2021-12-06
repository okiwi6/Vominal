#include <iostream>

#include <SFML/Audio.hpp>
#include "audio/OutputStream.hpp"
#include "audio/Recorder.hpp"
#include "audio/SoundManager.hpp"
#include <chrono>
#include <thread>
#include <stdint.h>


int main(int argc, char* argv[]) {
    // sf::SoundBufferRecorder rec;
    // rec.start();
    // std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    // rec.stop();

    std::string path = __FILE__;
    size_t last_occ = path.find_last_of('/');
    path = path.substr(0, last_occ) + "/../assets/test.ogg";

    // // std::this_thread::sleep_for(std::chrono::milliseconds(4000));
    
    sf::SoundBuffer buffer; // = rec.getBuffer();
    while(buffer.getSamples() == 0x0) {
        buffer.loadFromFile(path);
    }
    
    // OutputStream out(buffer);
    // out.play();


    // while(out.getStatus() == OutputStream::Playing) {
    sf::sleep(sf::seconds(0.1f));
    // }

    SoundManager sm;
    sm.addSound(buffer);
    sf::sleep(sf::milliseconds(800));
    sm.addSound(buffer);
    sm.startRecording();
    
    while(true) {
        sm.update();
        sf::sleep(sf::milliseconds(10));
    }

    std::cout << "end reached\n";
}