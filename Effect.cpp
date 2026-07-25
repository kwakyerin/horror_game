#include "Effect.h"
#include <cstdlib>

Effect::Effect()
{
}

void Effect::InitRain(int count, int width, int height)
{
    rainDrops.clear();
    rainDrops.reserve(count);

    for (int i = 0; i < count; i++)
    {
        RainDrop drop;

        drop.x = static_cast<float>(rand() % width);
        drop.y = static_cast<float>(rand() % height);
        drop.speed = static_cast<float>(8 + rand() % 8);
        drop.length = static_cast<float>(8 + rand() % 8);

        rainDrops.push_back(drop);
    }
}

void Effect::UpdateRain(int width, int height)
{
    for (auto& rain : rainDrops)
    {
        rain.y += rain.speed;
        rain.x -= 1;

        if (rain.y > height)
        {
            rain.y = -10;
            rain.x = rand() % width;
        }
    }
}

void Effect::DrawRain(Gdiplus::Graphics& graphics)
{
    Gdiplus::Pen rainPen(
        Gdiplus::Color(160, 180, 210, 255),
        1.0f
    );

    for (const RainDrop& drop : rainDrops)
    {
        graphics.DrawLine(
            &rainPen,
            drop.x,
            drop.y,
            drop.x - 2.0f,
            drop.y + drop.length
        );
    }
}