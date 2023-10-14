#pragma once
#include <vector>
#include <cstdint>
#include <memory>

// a simple miniaudio based class that plays back audio from a buffer while
// providing a second buffer to be filled for the next playback round

class player_impl;

class player {
public:
    player(const uint32_t nChannels = 2, const uint32_t sampleRate = 441800);
    ~player();
    void play(const std::vector<double>& buffer);
private:
    player_impl* m_impl;
};