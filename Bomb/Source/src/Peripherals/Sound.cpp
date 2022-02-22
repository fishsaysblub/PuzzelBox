//
// Created by david on 16-5-19.
//

#include <string>
#include <alsa/error.h>
#include <math.h>
#include "Peripherals/Sound.h"
#include <iostream>
#include <Biem.h>

Peripherals::Sound::Sound()
    : m_running(true), m_playAsset(false), m_buffer(nullptr), m_loops(0),
      m_thread(&Peripherals::Sound::Loop, this)
{
    static std::string device = "default";
    int err;

    if ((err = snd_pcm_open(&m_handle, device.c_str(), SND_PCM_STREAM_PLAYBACK, 0)) < 0)
    {
        printf("Playback open error: %s\n", snd_strerror(err));
        exit(EXIT_FAILURE);
    }

    if ((err = snd_pcm_set_params(m_handle,
                                  SND_PCM_FORMAT_FLOAT,
                                  SND_PCM_ACCESS_RW_INTERLEAVED,
                                  CHANNELS,
                                  SAMPLE_RATE,
                                  true,
                                  500000)) < 0)
    { /* 0.5sec */
        printf("Playback open error: %s\n", snd_strerror(err));
        exit(EXIT_FAILURE);
    }

    m_playAsset = true;
    for (long j = 0; j < BUFFER_SIZE; j++)
    {
        m_beepBuffer[j] = sin(2 * M_PI * j / SAMPLE_RATE * 2000) * 0.25;
    }
    for (long j = 0; j < BUFFER_SIZE * 10; j++)
    {
        if ((j / BUFFER_SIZE) % 5 < 3)
            m_wrongBuffer[j] = sin(2 * M_PI * j / SAMPLE_RATE * 100) * 20;
        else
            m_wrongBuffer[j] = 0;
    }
}

Peripherals::Sound::~Sound()
{
    Stop();
    snd_pcm_close(m_handle);
}

void Peripherals::Sound::Beep()
{
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        if (m_playAsset)
            return;

        m_buffer = m_beepBuffer;
        m_loops = 1;
        m_playAsset = true;
    }
}

void Peripherals::Sound::Wrong()
{
    {
        std::lock_guard<std::mutex> lock(m_mutex);

        m_buffer = m_wrongBuffer;
        m_loops = 10;
        m_playAsset = true;
    }
}

void Peripherals::Sound::Biem()
{
    std::lock_guard<std::mutex> lock(m_mutex);
    union BiemConvert convert;
    convert.biem_char = biem_raw;

    m_buffer = convert.biem_float;
    m_loops = biem_raw_len / sizeof(float) / BUFFER_SIZE;
    m_playAsset = true;
}

void Peripherals::Sound::Stop()
{
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        m_running = false;
        m_playAsset = true;
        m_loops = 0;
    }

    m_cv.notify_one();
    m_thread.join();
}

void Peripherals::Sound::Loop()
{
    snd_pcm_sframes_t frames;
    float *buffer;
    unsigned loops;
    float empty[BUFFER_SIZE / 2] = {0};

    while (!m_playAsset)
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    while (m_running)
    {
        {
            std::unique_lock<std::mutex> lock(m_mutex);
            if (!m_running)
                return;

            if (m_playAsset)
            {
                buffer = m_buffer;
                loops = m_loops;
                m_playAsset = false;
            }
            else
            {
                buffer = nullptr;
            }
        }

        if (buffer == nullptr)
        {
            snd_pcm_writei(m_handle, empty, BUFFER_SIZE / 2);
            continue;
        }

        for (unsigned i = 0; i < loops; ++i)
        {
            frames = snd_pcm_writei(m_handle, buffer + (i * BUFFER_SIZE), BUFFER_SIZE);
            if (frames < 0)
            {
                std::cout << "underrun" << std::endl;
                frames = snd_pcm_recover(m_handle, frames, 0);
            }
            if (frames < 0)
            {
                printf("snd_pcm_writei failed: %s\n", snd_strerror(frames));
                i = loops;
            }
            if (frames > 0 && frames < BUFFER_SIZE)
                printf("Short write (expected %i, wrote %li)\n", BUFFER_SIZE, frames);
        }
    }
}
