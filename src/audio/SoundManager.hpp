#pragma once

#include "Recorder.hpp"
#include "OutputStream.hpp"
#include <SFML/Audio.hpp>

#include <deque>

class SoundManager {
    public:
        SoundManager();
        ~SoundManager();

        void startRecording();
        void stopRecording();

        void processSamples(const sf::Int16* samples, std::size_t sampleCount, uint16_t channelCount, uint32_t sampleRate);
        void addSound(sf::SoundBuffer& buffer);

        void update();

    private:
        // receiveSocket
        // sendSocket
        std::deque<OutputStream> outputStreams;
        Recorder recorder;
};