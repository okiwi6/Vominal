#pragma once

#include <SFML/Audio.hpp>
#include <vector>
#include <string>
#include <functional>

#include "OutputStream.hpp"

class Recorder : public sf::SoundRecorder {
    public:
        Recorder(std::string inputDevice=Recorder::getInputDevices()[0]);
        ~Recorder();

        void setProcessCallback(std::function<void(const sf::Int16* samples, std::size_t sampleCount, uint16_t channelCount, uint32_t sampleRate)> func);

        static std::vector<std::string> getInputDevices();
        virtual bool onProcessSamples(const sf::Int16* samples, std::size_t sampleCount);

    private:
        std::function<void(const sf::Int16* samples, std::size_t sampleCount, uint16_t channelCount, uint32_t sampleRate)> processCallback;
};