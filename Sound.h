#pragma once

#include <windows.h>
#include <mmsystem.h>

#pragma comment(lib, "winmm.lib")

class Sound
{
public:
    Sound();

    void PlayRain();
    void StopRain();

private:
    bool isRainPlaying;
};