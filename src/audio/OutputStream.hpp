#pragma once

#include <SFML/Audio.hpp>
#include <stdint.h>
#include <vector>

class OutputStream : public sf::SoundStream {
    public:
    //OutputStream();
    OutputStream(const sf::SoundBuffer& samples);
    OutputStream(const OutputStream&);
    ~OutputStream();

    // only tells whether playback is not running in the moment
    bool hasEnded() const;

    virtual bool onGetData(Chunk& data);
    virtual void onSeek(sf::Time timeOffset);

    void loadBuffer(const sf::SoundBuffer& samples);
    size_t getSampleIndexFromTime(double timeInSeconds);

    private:
    std::vector<sf::Int16> sampleBuffer{};
    size_t currentSample{0};
    uint16_t channelCount{2};
    uint16_t sampleRate{44100};
};