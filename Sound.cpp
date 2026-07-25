#include "Sound.h"

Sound::Sound()
    : isRainPlaying(false)
{
}

void Sound::PlayRain()
{
    if (isRainPlaying)
    {
        return;
    }

    PlaySound( L"Sound\\Rain_Thunder.wav",nullptr,SND_FILENAME | SND_ASYNC | SND_LOOP );

    isRainPlaying = true;
}

void Sound::StopRain()
{
    if (!isRainPlaying)
    {
        return;
    }

    PlaySound(nullptr, nullptr, 0);

    isRainPlaying = false;
}