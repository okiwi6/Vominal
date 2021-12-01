#include <iostream>

#include <SFML/Audio.hpp>
#include "audio/OutputStream.hpp"
#include "audio/Recorder.hpp"
#include "audio/SoundManager.hpp"
#include <chrono>
#include <thread>


int main() {
    // sf::SoundBufferRecorder rec;
    // rec.start();
    // std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    // rec.stop();
    

    // // std::this_thread::sleep_for(std::chrono::milliseconds(4000));
    sf::SoundBuffer buffer; // = rec.getBuffer();
    buffer.loadFromFile("../assets/test.ogg");

    // OutputStream out(buffer);
    // out.play();


    // while(out.getStatus() == OutputStream::Playing) {
    //     sf::sleep(sf::seconds(0.1f));
    // }

    SoundManager sm;
    sm.addSound(buffer);
    //sm.startRecording();
    
    while(true) {
        sm.update();
        sf::sleep(sf::milliseconds(10));
    }

    std::cout << "end reached\n";
}