#include "Recorder.hpp"
#include <iostream>

Recorder::Recorder(std::string inputDevice) {
    if(!Recorder::isAvailable()) {
        throw std::runtime_error("The terminal doesn't support coloring");
    }
    if(!setDevice(inputDevice)) {
        throw std::runtime_error(inputDevice + " couldn't be selected as recorder device");
    }
    std::cout << "Started with recorder device " << inputDevice << "\n";
}

Recorder::~Recorder() {
    stop();
}

std::vector<std::string> Recorder::getInputDevices() {
    return sf::SoundRecorder::getAvailableDevices();
}

void Recorder::setProcessCallback(std::function<void(const sf::Int16* samples, std::size_t sampleCount, uint16_t channelCount, uint32_t sampleRate)> func) {
    processCallback = func;
}

bool Recorder::onProcessSamples(const sf::Int16* samples, std::size_t sampleCount) {
    // // TODO: performance increase if there is no SoundBuffer object created
    // manager.
    // sf::SoundBuffer buffer;
    // buffer.loadFromSamples(samples, sampleCount, getChannelCount(), getSampleRate());
    // out.loadBuffer(buffer);
    // // out.play();

    //manager.processSamples(samples, sampleCount, getChannelCount(), getSampleRate());

    processCallback(samples, sampleCount, getChannelCount(), getSampleRate());

    return true;
}