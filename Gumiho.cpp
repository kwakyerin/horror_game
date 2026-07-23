#include "Gumiho.h"
#include "Character.h"

Gumiho::Gumiho(
    const wchar_t* walkPath,
    const wchar_t* attackPath,
    float startX,
    float startY,
    float detect,
    float attack)
    : Monster(
        walkPath,
        attackPath,
        startX,
        startY,
        detect,
        attack)
{
    SetMoveSpeed(83.0f);
}

Gumiho::~Gumiho()
{
    for (FireBall* fireBall : fireBalls)
    {
        delete fireBall;
    }

    fireBalls.clear();
}

void Gumiho::UpdateAttack(float deltaTime, Character& character)
{
    if (GetCurrentFrame() == 1 && !HasAttacked())
    {
        float dirX = character.GetX() - GetX();
        float dirY = character.GetY() - GetY();

        FireBall* newFireBall =
            new FireBall(GetX(), GetY(), dirX, dirY);

        fireBalls.push_back(newFireBall);

        SetHasAttacked(true);
    }
}

void Gumiho::UpdateSpecial(float deltaTime)
{
    for (FireBall* fireBall : fireBalls)
    {
        fireBall->Update(deltaTime);
    }

    for (auto it = fireBalls.begin();
        it != fireBalls.end();)
    {
        if (!(*it)->IsActive())
        {
            delete* it;
            it = fireBalls.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

void Gumiho::DrawSpecial(Gdiplus::Graphics& graphics)
{
    for (FireBall* fireBall : fireBalls)
    {
        fireBall->Draw(graphics);
    }
}