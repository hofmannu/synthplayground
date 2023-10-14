#include "oscillator.h"

#include <cmath>

oscillator::oscillator(/* args */)
{
}

oscillator::~oscillator()
{
}

void oscillator::set_wave_type(wave_type type)
{
    wave = type;
}

void oscillator::set_frequency(float frequency)
{
    freq = frequency;
}

void oscillator::set_amplitude(float amplitude)
{
    amp = amplitude;
}

void oscillator::set_phase(float phase)
{
    phs = phase;
}

float oscillator::get_sample(const float time)
{
    float sample = 0.0f;
    float angle = phs + freq * time;

    switch (wave)
    {
    case wave_type::sine:
        sample = amp * sin(angle);
        break;
    case wave_type::square:
        sample = amp * (sin(angle) > 0.0f ? 1.0f : -1.0f);
        break;
    case wave_type::saw:
        sample = amp * (1.0f - 2.0f * fmod(angle, 1.0f));
        break;
    case wave_type::triangle:
        sample = amp * (1.0f - 4.0f * fabsf(fmod(angle, 1.0f) - 0.5f));
        break;
    case wave_type::noise:
        sample = amp * (2.0f * static_cast<float>(rand()) / static_cast<float>(RAND_MAX) - 1.0f);
        break;
    default:
        break;
    }

    return sample;
}