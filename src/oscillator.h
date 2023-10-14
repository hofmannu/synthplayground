#pragma once

enum class wave_type {
    sine,
    square,
    saw,
    triangle,
    noise
};

class oscillator
{
public:
    // constructor and destructor
    oscillator(/* args */);
    ~oscillator();

    // set functions for the synth properties
    void set_wave_type(wave_type type);
    void set_frequency(float frequency);
    void set_amplitude(float amplitude);
    void set_phase(float phase);

    // get function for the sample
    float get_sample(const float time);
private:
    // properties of the osillator
    wave_type wave;
    float freq;
    float amp;
    float phs;
};

