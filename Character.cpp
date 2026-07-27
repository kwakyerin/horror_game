#include <cmath>
#include "Character.h"
#include "Map.h"
#include "QuizGhost.h"


Character::Character(const wchar_t* path)
    : x(10 * Tile_Size),
    y(10 * Tile_Size),
    moveSpeed(400.0f),
    currentFrame(0),
    animationTimer(0.0f),
    hp(15),
    direction(Direction::Down),
    image(nullptr),
    deathImage(nullptr),
    isDying(false),
    deathAnimationFinished(false),
    facingLeft(false),
    deathFacingLeft(false),
    deathFrame(0),
    deathAnimationTimer(0.0f)
{
    LoadImage(path);
    deathImage = new Gdiplus::Image(L"Image\\character\\death.png");
    if (deathImage->GetLastStatus() != Gdiplus::Ok)
    {
        delete deathImage;
        deathImage = nullptr;
    }
}

Character::~Character()
{
    delete image;
    image = nullptr;

    delete deathImage;
    deathImage = nullptr;
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
void Character::Move(float deltaTime, Map& gameMap,const std::vector<RECT>& monsterRects)
{
    if (isDying) {
        return;
    }
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
        facingLeft = true;
        isMoving = true;
    }
    else if (GetAsyncKeyState('D') & 0x8000)
    {
        nextX += moveSpeed * deltaTime;
        direction = Direction::Right;
        facingLeft = false;
        isMoving = true;
    }

    //충돌체크 박스 크기 여기서 수정 ㄱ
    bool blocked =
        gameMap.IsBlocked(nextX + 4, nextY + 4) ||
        gameMap.IsBlocked(nextX + 27, nextY + 4) ||
        gameMap.IsBlocked(nextX + 4, nextY + 27) ||
        gameMap.IsBlocked(nextX + 27, nextY + 27);

    RECT nextPlayerRect =
    {
        static_cast<LONG>(nextX + 4),
        static_cast<LONG>(nextY + 4),
        static_cast<LONG>(nextX + 28),
        static_cast<LONG>(nextY + 32)
    };

    if (!blocked)
    {
        for (const RECT& monsterRect : monsterRects)
        {
            RECT collisionResult;

            if (IntersectRect(&collisionResult,&nextPlayerRect,&monsterRect))
            {
                blocked = true;
                break;
            }
        }
    }

    if (!blocked)
    {
        x = nextX;
        y = nextY;
    }

    //캐릭터 프레임
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
    if (isDying)
    {
        if (deathImage == nullptr)
        {
            return;
        }

        const int deathFrameWidth = 20;
        const int deathFrameHeight = 16;

        const int deathDrawWidth = 32;
        const int deathDrawHeight = 32;

        int sourceX = deathFrame * deathFrameWidth;

        if (deathFacingLeft)
        {
            // 왼쪽을 보다가 죽으면 원본 그대로 출력
            graphics.DrawImage(
                deathImage,
                Gdiplus::Rect(
                    static_cast<int>(x),
                    static_cast<int>(y),
                    deathDrawWidth,
                    deathDrawHeight
                ),
                sourceX,
                0,
                deathFrameWidth,
                deathFrameHeight,
                Gdiplus::UnitPixel
            );
        }
        else
        {
            // 오른쪽을 보다가 죽으면 좌우 반전
            Gdiplus::GraphicsState oldState = graphics.Save();

            graphics.TranslateTransform(
                x + deathDrawWidth,
                y
            );

            graphics.ScaleTransform(
                -1.0f,
                1.0f
            );

            graphics.DrawImage(
                deathImage,
                Gdiplus::Rect(
                    0,
                    0,
                    deathDrawWidth,
                    deathDrawHeight
                ),
                sourceX,
                0,
                deathFrameWidth,
                deathFrameHeight,
                Gdiplus::UnitPixel
            );

            graphics.Restore(oldState);
        }

        return;
    }
    if (image == nullptr)
        return;

    int sourceX = currentFrame * 16;
    int sourceY = static_cast<int>(direction) * 20;

    int drawX = static_cast<int>(std::round(x));
    int drawY = static_cast<int>(std::round(y));

    graphics.DrawImage(
        image,
        Gdiplus::Rect(
            drawX,
            drawY,
            32,
            32
        ),
        sourceX,
        sourceY,
        15,
        20,
        Gdiplus::UnitPixel
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

Direction Character::GetDirection()const
{
    return direction;
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
    if (isDying)
    {
        return;
    }

    hp -= damage;

    if (hp <= 0)
    {
        hp = 0;

        isDying = true;
        deathAnimationFinished = false;

        deathFrame = 0;
        deathAnimationTimer = 0.0f;

        deathFacingLeft = facingLeft;
    }
}

void Character::UpdateDeath(float deltaTime)
{
    if (!isDying || deathAnimationFinished)
    {
        return;
    }

    deathAnimationTimer += deltaTime;

    if (deathAnimationTimer >= 0.15f)
    {
        deathAnimationTimer = 0.0f;
        deathFrame++;

        if (deathFrame >= 4)
        {
            deathFrame = 3;
            deathAnimationFinished = true;
        }
    }
}

bool Character::IsDying() const
{
    return isDying;
}

bool Character::IsDeathAnimationFinished() const
{
    return deathAnimationFinished;
}

void Character::Reset()
{
    x = 10 * Tile_Size;
    y = 10 * Tile_Size;

    hp = 15;

    direction = Direction::Down;
    currentFrame = 0;
    animationTimer = 0.0f;

    facingLeft = false;

    isDying = false;
    deathAnimationFinished = false;

    deathFrame = 0;
    deathAnimationTimer = 0.0f;

    deathFacingLeft = false;
}