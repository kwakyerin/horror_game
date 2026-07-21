#include "Character.h"
#include "Map.h"

Character::Character(const wchar_t* path)
    : x(0.0f), //캐릭터 스폰지역?
    y(0.0f),
    moveSpeed(450.0f),
    currentFrame(0),
    animationTimer(0.0f),
    hp(15),
    direction(Direction::Down),
    image(nullptr)
{
    LoadImage(path);
}

Character::~Character()
{
    delete image;
}

bool Character::LoadImage(const wchar_t* path)
{
    image = new Gdiplus::Image(path);

    if (image->GetLastStatus() != Gdiplus::Ok)
    {
        delete image;
        image = nullptr;
        return false;
    }

    return true;
}

//캐릭터 움직임
void Character::Move(float deltaTime, Map& gameMap)
{
    bool isMoving = false;

    float nextX = x;
    float nextY = y;

    if (GetAsyncKeyState('W') & 0x8000)
    {
        nextY -= moveSpeed * deltaTime;
        direction = Direction::Up;
        isMoving = true;
    }
    else if (GetAsyncKeyState('S') & 0x8000)
    {
        nextY += moveSpeed * deltaTime;
        direction = Direction::Down;
        isMoving = true;
    }
    else if (GetAsyncKeyState('A') & 0x8000)
    {
        nextX -= moveSpeed * deltaTime;
        direction = Direction::Left;
        isMoving = true;
    }
    else if (GetAsyncKeyState('D') & 0x8000)
    {
        nextX += moveSpeed * deltaTime;
        direction = Direction::Right;
        isMoving = true;
    }

    bool blocked =
        gameMap.IsBlocked(nextX, nextY) ||
        gameMap.IsBlocked(nextX + 31.0f, nextY) ||
        gameMap.IsBlocked(nextX, nextY + 31.0f) ||
        gameMap.IsBlocked(nextX + 31.0f, nextY + 31.0f);

    if (!blocked)
    {
        x = nextX;
        y = nextY;
    }

    if (isMoving)
    {
        animationTimer += deltaTime;

        if (animationTimer >= 0.15f)
        {
            currentFrame = (currentFrame + 1) % 3;
            animationTimer = 0.0f;
        }
    }
    else
    {
        currentFrame = 1;
        animationTimer = 0.0f;
    }
}

void Character::Draw(Gdiplus::Graphics& graphics)
{
    if (image == nullptr)
        return;

    int sourceX = currentFrame * 16;
    int sourceY = static_cast<int>(direction) * 20;

    graphics.DrawImage(
        image,
        Gdiplus::Rect(
            static_cast<int>(x),
            static_cast<int>(y),
            32,
            32
        ),
        sourceX,
        sourceY,
        15,
        20,
        Gdiplus::UnitPixel
    );

    // 충돌 박스 시각화
    Gdiplus::Pen collisionPen(
        Gdiplus::Color(255, 255, 0, 0),
        1.0f
    );

    graphics.DrawRectangle(
        &collisionPen,
        static_cast<int>(x),
        static_cast<int>(y),
        32,
        32
    );
}

RECT Character::GetCollisionRect() const
{
    RECT collisionRect;

    collisionRect.left = static_cast<LONG>(x);
    collisionRect.top = static_cast<LONG>(y);
    collisionRect.right = static_cast<LONG>(x + 32.0f);
    collisionRect.bottom = static_cast<LONG>(y + 32.0f);

    return collisionRect;
}

float Character::GetX() const
{
    return x;
}

float Character::GetY() const
{
    return y;
}

void Character::SetPosition(float newX, float newY)
{
    x = newX;
    y = newY;
}

int Character::GetHP() const
{
    return hp;
}

void Character::Damage(int damage)
{
    hp -= damage;

    if (hp < 0)
        hp = 0;
}