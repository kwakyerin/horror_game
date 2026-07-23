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

void Gumiho::UpdateSpecial(float deltaTime,Character& character)
{
    for (auto it = fireBalls.begin();
        it != fireBalls.end();)
    {
        FireBall* fireBall = *it;

        fireBall->Update(deltaTime);

        RECT fireBallRect =
            fireBall->GetCollisionRect();

        RECT characterRect =
            character.GetCollisionRect();

        RECT intersection;

        if (IntersectRect(
            &intersection,
            &fireBallRect,
            &characterRect))
        {
            character.Damage(2);

            fireBall->Deactivate();
        }

        if (!fireBall->IsActive())
        {
            delete fireBall;
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