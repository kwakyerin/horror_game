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
    SetDrawSize(256, 256);
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
            new FireBall(GetX(), GetY()+80.0f, dirX, dirY);

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

        if (IntersectRect(&intersection,&fireBallRect,&characterRect))
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

RECT Gumiho::GetCollisionRect() const
{
    RECT rect;

    if (IsFacingLeft())
    {
        rect.left = static_cast<LONG>(GetX() + 70);
        rect.right = static_cast<LONG>(GetX() + 220);
    }
    else
    {
        rect.left = static_cast<LONG>(GetX() + 36);
        rect.right = static_cast<LONG>(GetX() + 186);
    }

    rect.top = static_cast<LONG>(GetY() + 80);
    rect.bottom = static_cast<LONG>(GetY() + 255);

    return rect;

    
}