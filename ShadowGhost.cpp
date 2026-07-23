#include "ShadowGhost.h"
#include "Character.h"

#include <cstdlib>
#include <algorithm>

const float MAP_WIDTH = 500.0f;
const float MAP_HEIGHT = 400.0f;// 임시로 몬스터 생성 위치 정한것임. 맵에 따라 수정

ShadowGhost::ShadowGhost(const wchar_t* warningPath,const wchar_t* attackPath,float startX,float startY)
{
    x = startX;
    y = startY;

    state = ShadowState::Waiting;
    direction = ShadowDirection::Down;

    warningImage = nullptr;
    attackImage = nullptr;

    currentFrame = 0;
    animationTimer = 0.0f;

    // 실제 스프라이트 프레임 개수
    warningFrameCount = 6;
    attackFrameCount = 6;

    waitTimer = 0.0f;
    
    // 다음 순간이동까지 기다리는 시간
    waitDuration = 3.0f;

    hasAttacked = false;

    LoadImages(warningPath, attackPath);
}

ShadowGhost::~ShadowGhost()
{
    delete warningImage;
    delete attackImage;

    warningImage = nullptr;
    attackImage = nullptr;
}

bool ShadowGhost::LoadImages(
    const wchar_t* warningPath,
    const wchar_t* attackPath)
{
    warningImage = new Gdiplus::Image(warningPath);

    if (warningImage->GetLastStatus() != Gdiplus::Ok)
    {
        delete warningImage;
        warningImage = nullptr;
    }

    attackImage = new Gdiplus::Image(attackPath);

    if (attackImage->GetLastStatus() != Gdiplus::Ok)
    {
        delete attackImage;
        attackImage = nullptr;
    }

    return warningImage != nullptr &&
        attackImage != nullptr;
}

void ShadowGhost::Update(float deltaTime,Character& character)
{
    switch (state)
    {
    case ShadowState::Waiting:
        UpdateWaiting(deltaTime, character);
        break;

    case ShadowState::Warning:
        UpdateWarning(deltaTime,character);
        break;

    case ShadowState::Attack:
        UpdateAttack(deltaTime, character);
        break;
    }
}

void ShadowGhost::UpdateWaiting(float deltaTime,Character& character)
{
    waitTimer += deltaTime;

    if (waitTimer < waitDuration)
        return;

    waitTimer = 0.0f;

    TeleportNearCharacter(character);

    state = ShadowState::Warning;

    currentFrame = 0;
    animationTimer = 0.0f;
    
    hasAttacked = false;
}

void ShadowGhost::TeleportNearCharacter(Character& character)
{
    const float distance = 100.0f;

    int dir = rand() % 4;

    switch (dir)
    {
    case 0: // 플레이어 위에 등장
        x = character.GetX();
        y = character.GetY() - distance;
        direction = ShadowDirection::Down;
        break;

    case 1: // 플레이어 아래에 등장
        x = character.GetX();
        y = character.GetY() + distance;
        direction = ShadowDirection::Up;
        break;

    case 2: // 플레이어 왼쪽에 등장
        x = character.GetX() - distance;
        y = character.GetY();
        direction = ShadowDirection::Right;
        break;

    case 3: // 플레이어 오른쪽에 등장
        x = character.GetX() + distance;
        y = character.GetY();
        direction = ShadowDirection::Left;
        break;
    }

    x = std::clamp(x, 0.0f, MAP_WIDTH - 128.0f);
    y = std::clamp(y, 0.0f, MAP_HEIGHT - 128.0f);
}

void ShadowGhost::UpdateWarning(float deltaTime,Character& character)
{
    animationTimer += deltaTime;

    const float frameDuration = 0.2f;
    
    if (animationTimer >= frameDuration)
    {
        animationTimer -= frameDuration;
        currentFrame++;

        if (currentFrame >= warningFrameCount)
        {
            float dx = character.GetX() - x;
            float dy = character.GetY() - y;

            if (std::abs(dx) > std::abs(dy))
            {
                if (dx > 0)
                    direction = ShadowDirection::Right;
                else
                    direction = ShadowDirection::Left;
            }
            else
            {
                if (dy > 0)
                    direction = ShadowDirection::Down;
                else
                    direction = ShadowDirection::Up;
            }
            state = ShadowState::Attack;

            currentFrame = 0;
            animationTimer = 0.0f;

            hasAttacked = false;
        }
    }
    
}

void ShadowGhost::UpdateAttack(float deltaTime,Character& character)
{
    animationTimer += deltaTime;

    // 공격 애니메이션 속도
    const float frameDuration = 0.1f;

    if (animationTimer >= frameDuration)
    {
        animationTimer -= frameDuration;
        currentFrame++;

        // 마지막 공격 프레임까지 재생한 경우
        if (currentFrame >= attackFrameCount)
        {
            state = ShadowState::Waiting;

            currentFrame = 0;
            animationTimer = 0.0f;
            waitTimer = 0.0f;

            hasAttacked = false;

            return;
        }
    }
    if (currentFrame >= 6 && !hasAttacked)
    {
        RECT ghostRect = GetCollisionRect();
        RECT characterRect = character.GetCollisionRect();

        RECT collisionRect;

        if (IntersectRect(&collisionRect, &ghostRect, &characterRect))
        {
            character.Damage(3);
            hasAttacked = true;
        }
    }

    
}

void ShadowGhost::Draw(Gdiplus::Graphics& graphics)
{
    if (state == ShadowState::Waiting)
        return;

    Gdiplus::Image* currentImage = nullptr;

    int frameCount = 0;
    int row = 0;
    int rowCount = 1;

    if (state == ShadowState::Warning)
    {
        currentImage = warningImage;

        frameCount = warningFrameCount; // 6
        rowCount = 1;
        row = 0;
    }
    else if (state == ShadowState::Attack)
    {
        currentImage = attackImage;

        frameCount = attackFrameCount; 
        rowCount = 4;

        switch (direction)
        {
        case ShadowDirection::Up:
            row = 0;
            break;

        case ShadowDirection::Down:
            row = 1;
            break;

        case ShadowDirection::Right:
            row = 2;
            break;

        case ShadowDirection::Left:
            row = 3;
            break;
        }
    }

    if (currentImage == nullptr || frameCount <= 0)
        return;

    int imageWidth =
        static_cast<int>(currentImage->GetWidth());

    int imageHeight =
        static_cast<int>(currentImage->GetHeight());

    // 현재 이미지의 실제 프레임 개수로 계산
    int frameWidth = imageWidth / frameCount;
    int frameHeight = imageHeight / rowCount;

    int sourceX = currentFrame * frameWidth;
    int sourceY = row * frameHeight;

    graphics.DrawImage(
        currentImage,
        Gdiplus::Rect(
            static_cast<int>(x),
            static_cast<int>(y),
            frameWidth,
            frameHeight
        ),
        sourceX,
        sourceY,
        frameWidth,
        frameHeight,
        Gdiplus::UnitPixel
    );

    Gdiplus::Pen pen(
        Gdiplus::Color(255, 255, 0, 0),
        1.0f
    );

    RECT collisionRect = GetCollisionRect();

    graphics.DrawRectangle(
        &pen,
        static_cast<INT>(collisionRect.left),
        static_cast<INT>(collisionRect.top),
        static_cast<INT>(collisionRect.right - collisionRect.left),
        static_cast<INT>(collisionRect.bottom - collisionRect.top)
    );
}

RECT ShadowGhost::GetCollisionRect() const
{
    RECT rect;

    rect.left = static_cast<LONG>(x+20);
    rect.top = static_cast<LONG>(y);

    rect.right = static_cast<LONG>(x + 100.0f);
    rect.bottom = static_cast<LONG>(y + 82.0f);

    return rect;
}

float ShadowGhost::GetX() const
{
    return x;
}

float ShadowGhost::GetY() const
{
    return y;
}