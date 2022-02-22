//
// Created by david on 16-5-19.
//

#ifndef MAIN_BOM_SOUND_H
#define MAIN_BOM_SOUND_H

#include <alsa/asoundlib.h>
#include <thread>
#include <mutex>
#include <condition_variable>

#define CHANNELS 1
#define SAMPLE_RATE 8000
#define FRAME_PER_PERIOD 1024
#define SAMPLE_SIZE 1
#define BUFFER_SIZE (FRAME_PER_PERIOD * SAMPLE_SIZE * CHANNELS)

namespace Peripherals
{
    class Sound
    {
    public:
        Sound();
        ~Sound();

    public:
        void Beep();
        void Wrong();
        void Biem();
        void Stop();

    private:
        bool m_running;
        bool m_playAsset;

        snd_pcm_t *m_handle;

        float *m_buffer;
        unsigned m_loops;

        std::mutex m_mutex;
        std::condition_variable m_cv;
        std::thread m_thread;

    private:
        float m_beepBuffer[BUFFER_SIZE];
        float m_wrongBuffer[BUFFER_SIZE * 10];

    private:
        void Loop();
    };
};

#endif // MAIN_BOM_SOUND_H
