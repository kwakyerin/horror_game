#pragma once
#include <vector>
#include <windows.h>
#include <gdiplus.h>

struct RainDrop
{
    float x;
    float y;
    float speed;
    float length;
};

class Effect
{
public:
    Effect();

    void InitRain(int count, int width, int height);
    void UpdateRain(int width, int height);
    void DrawRain(Gdiplus::Graphics& graphics);

private:
    std::vector<RainDrop> rainDrops;
};