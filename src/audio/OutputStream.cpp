#include "OutputStream.hpp"

OutputStream::OutputStream(const sf::SoundBuffer& samples) {
    loadBuffer(std::move(samples));
    play();
}

OutputStream::OutputStream(const OutputStream& other) {
    currentSample = other.currentSample;
    sampleRate = other.sampleRate;
    channelCount = other.channelCount;
    sampleBuffer = other.sampleBuffer;
}

OutputStream::~OutputStream() {

}

bool OutputStream::hasEnded() const {
    return getStatus() == OutputStream::Playing;
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
    sampleBuffer.assign(samples.getSamples(), samples.getSamples() + samples.getSampleCount());
    currentSample = 0;
    channelCount = samples.getChannelCount();
    sampleRate = samples.getSampleRate();
    initialize(samples.getChannelCount(), sampleRate);
}

size_t OutputStream::getSampleIndexFromTime(double timeInSeconds) {
    return static_cast<size_t>(timeInSeconds * channelCount * sampleRate);
}
