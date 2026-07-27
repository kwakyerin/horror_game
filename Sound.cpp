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

//ÄûÁî
void Sound::PlayQuizBGM()
{
    PlaySound(
        L"Sound\\Quiz_background.wav",
        nullptr,
        SND_FILENAME | SND_ASYNC | SND_LOOP);
}

void Sound::StopQuizBGM()
{
    PlaySound(nullptr, nullptr, 0);
}

void Sound::PlayCorrect()
{
    PlaySound(
        L"Sound\\Correct.wav",
        nullptr,
        SND_FILENAME | SND_ASYNC);
}

void Sound::PlayWrong()
{
    PlaySound(
        L"Sound\\Wrong.wav",
        nullptr,
        SND_FILENAME | SND_ASYNC);
}

void Sound::PlayTitleBGM()
{
    PlaySound(
        L"Sound\\TitleBGM.wav",
        nullptr,
        SND_FILENAME | SND_ASYNC | SND_LOOP);
}

void Sound::StopTitleBGM()
{
    PlaySound(nullptr, nullptr, 0);
}

// ¿£µù BGM
void Sound::PlayEndingBGM()
{
    PlaySound(
        L"Sound\\EndingBGM.wav",
        nullptr,
        SND_FILENAME | SND_ASYNC | SND_LOOP);
}

void Sound::StopEndingBGM()
{
    PlaySound(nullptr, nullptr, 0);
}

void Sound::PlayFailEndingBGM()
{
    PlaySound(
        L"Sound\\failEnding.wav",
        nullptr,
        SND_FILENAME | SND_ASYNC | SND_LOOP
    );
}

void Sound::StopFailEndingBGM()
{
    PlaySound(
        nullptr,
        nullptr,
        0
    );
}