#include "OutputStream.hpp"
#include <iostream>

OutputStream::OutputStream():
sampleBuffer(),
currentSample(0),
sampleRate(44100),
channelCount(2)
{
    sampleBuffer.push_back(0);

}

// OutputStream::OutputStream(const sf::SoundBuffer& samples) {
//     loadBuffer(std::move(samples));
//     play();
// }

OutputStream::OutputStream(const OutputStream& other):
sampleBuffer()
{
    currentSample = other.currentSample;
    sampleRate = other.sampleRate;
    //sampleBuffer -> reserve(other.sampleBuffer -> size());
    sampleBuffer.assign(other.sampleBuffer.begin(), other.sampleBuffer.end());
    channelCount = other.channelCount;
}


bool OutputStream::hasEnded() const {
    return getStatus() == OutputStream::Stopped;
}

void OutputStream::init() {
    initialize(channelCount, sampleRate);
}

void OutputStream::setParams(int channelCount, int sampleRate) {
    channelCount = channelCount;
    sampleRate = sampleRate;
    currentSample = 0;
}

void OutputStream::onSeek(sf::Time timeOffset) {
    currentSample = static_cast<size_t>(getSampleIndexFromTime(timeOffset.asSeconds()));
}


bool OutputStream::onGetData(Chunk& data) {
    // get 1s of stream
    const auto samplesToStream = getSampleIndexFromTime(1.);

    data.samples = &sampleBuffer[currentSample];

    if(currentSample + samplesToStream <= sampleBuffer.size()) {
        // end still not reached
        data.sampleCount = samplesToStream;
        currentSample += samplesToStream;
        return true; // return true to resume output
    } else {
        // end of stream reached
        data.sampleCount = sampleBuffer.size() - currentSample;
        currentSample = sampleBuffer.size();
        return false; // return false to stop output
    }
}

void OutputStream::loadBuffer(const sf::SoundBuffer& samples) {
    currentSample = 0;
    channelCount = samples.getChannelCount();
    sampleRate = samples.getSampleRate();
    
    sampleBuffer.assign(samples.getSamples(), samples.getSamples() + samples.getSampleCount());

    initialize(channelCount, sampleRate);
}

size_t OutputStream::getSampleIndexFromTime(double timeInSeconds) {
    return static_cast<size_t>(timeInSeconds * channelCount * sampleRate);
}
