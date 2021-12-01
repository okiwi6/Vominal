#include "SoundManager.hpp"
#include <iostream>

SoundManager::SoundManager()
{
    using namespace std::placeholders;
    recorder.setProcessCallback(std::bind(&SoundManager::processSamples, this, _1, _2, _3, _4));
}

SoundManager::~SoundManager() {

}

void SoundManager::update() {
    // TODO maybe better use Pool of outputstreams to gain performance 
    std::cout << outputStreams.size() << std::endl;

    if(outputStreams.size() > 0) {
        while(outputStreams.begin() -> hasEnded()) {
            outputStreams.pop_front();
        }
    }

}

void SoundManager::startRecording() {
    recorder.start();
}

void SoundManager::stopRecording() {
    recorder.stop();
}

void SoundManager::processSamples(const sf::Int16* samples, std::size_t sampleCount, uint16_t channelCount, uint32_t sampleRate) {
    // at the moment the recorder self inputs into the output device
    // This function is called from recorder thread
    sf::SoundBuffer buffer;
    buffer.loadFromSamples(samples, sampleCount, channelCount, sampleRate);
    OutputStream out{buffer};
    out.play();
    outputStreams.push_back(out);
}

void SoundManager::addSound(sf::SoundBuffer& buffer) {
    OutputStream out{buffer};
    out.play();
    sf::sleep(sf::seconds((3)));
    outputStreams.push_back(out);
}