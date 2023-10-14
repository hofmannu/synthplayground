#include "player.h"
#include <cassert>
#include <stdexcept>

#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"

void data_callback(ma_device *pDevice, void *pOutput, const void *pInput, ma_uint32 frameCount)
{
    // In playback mode copy data to pOutput. In capture mode read data from pInput. In full-duplex mode, both
    // pOutput and pInput will be valid and you can move data from pInput into pOutput. Never process more than
    // frameCount frames.

    // for now we just add random noise to pOutput
    constexpr std::size_t nChannels = 2;
    // todo fix this
    std::vector<float> output(frameCount * nChannels);
    for (std::size_t iSample = 0; iSample < frameCount; iSample++)
    {
        const float noise = 2.0f * static_cast<float>(rand()) / static_cast<float>(RAND_MAX) - 1.0f;
        for (std::size_t iChannel = 0; iChannel < nChannels; iChannel++)
        {
            output[iSample * nChannels + iChannel] = noise;
        }
    }

    // copy into pOutput
    memcpy(pOutput, output.data(), frameCount * nChannels * sizeof(float));
}

class player_impl
{
public:
    player_impl(const uint32_t nChannels, const uint32_t sampleRate);
    ~player_impl();

private:
    ma_device_config m_config;

    const uint32_t m_nChannels;               //!< number of channels for playbacl
    const uint32_t m_sampleRate;              //!< samples per second
    ma_channel m_channelMap[MA_MAX_CHANNELS]; //!< channel map for playback
    ma_result m_result;                       //!< this is used mostly for error checking
    ma_device m_device;                       //!< the device we use for playback

    void check_result();
};

player_impl::player_impl(const uint32_t nChannels, const uint32_t sampleRate) : m_nChannels(nChannels), m_sampleRate(sampleRate)
{
    m_config = ma_device_config_init(ma_device_type_playback);
    m_config.playback.format = ma_format_f32; //  ma_format_f32 is 32-bit floating point [-1, 1]
    m_config.playback.channels = m_nChannels; // Set to 0 to use the device's native channel count.
    m_config.sampleRate = m_sampleRate;       // Set to 0 to use the device's native sample rate.
    m_config.dataCallback = data_callback;    // This function will be called when miniaudio needs more data.

    m_result = ma_device_init(NULL, &m_config, &m_device);
    check_result();

    // The device is sleeping by default so you'll need to start it manually
    ma_device_start(&m_device);
}

player_impl::~player_impl()
{
    ma_device_uninit(&m_device);
}

void player_impl::check_result()
{
    if (m_result != MA_SUCCESS)
    {
        // todo add some decryption of the error codes here
        throw std::runtime_error("Something went wrong with the miniaudio player");
    }
}

player::player(const uint32_t nChannels, const uint32_t sampleRate) : 
    m_impl(new player_impl(nChannels, sampleRate))
{
}

player::~player()
{
    delete m_impl;
}

void player::play(const std::vector<double> &buffer)
{
    // make sure that buffer has length % 2
    assert(buffer.size() % 2 == 0);

    // play back buffer using miniaudio
}

