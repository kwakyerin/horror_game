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

    void PlayEndingBGM();
    void StopEndingBGM();

    void PlayFailEndingBGM();
    void StopFailEndingBGM();

    void PlayLaughing();


private:
    bool isRainPlaying;
};