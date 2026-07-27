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

    void PlayQuizBGM();
    void StopQuizBGM();

    void PlayCorrect();
    void PlayWrong();

    void PlayTitleBGM();
    void StopTitleBGM();

private:
    bool isRainPlaying;
};