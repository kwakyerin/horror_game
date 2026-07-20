#include "Character.h"

Character::Character(const wchar_t* path) :

    x(450.0f),
    y(350.0f),
    moveSpeed(450.0f),
    currentFrame(0),
    animationTimer(0),
    direction(Direction::Down),
    hp(15),
	image(nullptr)
{
	LoadImage(path);

}

Character::~Character()
{
	delete image;
}

bool Character::LoadImage(const wchar_t* path) {
	image = new Gdiplus::Image(path);
	if (image->GetLastStatus()!=Gdiplus::Ok)
	{
		return false;
	}
	return true;
}

void Character::Draw(Gdiplus::Graphics& graphics) {

    if (image == nullptr)
        return;
    
    int sourceX = currentFrame*16;
    int sourceY = static_cast<int>(direction) * 20;
    
    graphics.DrawImage(
        image,          
        // 화면에 그릴 위치와 크기
        Gdiplus::Rect(
            static_cast<int>(x),    // 화면 X
            static_cast<int>(y),    // 화면 Y
            32,                     // 출력 너비
            32                      // 출력 높이
        ),

        // 원본 이미지에서 잘라올 위치
        sourceX,
        sourceY,      // 원본 Y
        15,     // 원본 너비
        20,     // 원본 높이

        Gdiplus::UnitPixel
    );

    Gdiplus::Pen collisionPen(
        Gdiplus::Color(255, 255, 0, 0), 1.0f
    );

    graphics.DrawRectangle(
        &collisionPen,
        static_cast<int>(x),
        static_cast<int>(y),
        32,
        32
    );
}

void Character::Move(float deltaTime) {

    bool isMoving = false;

    if (GetAsyncKeyState('W') & 0x8000)
    {
        y -= moveSpeed*deltaTime;
        direction = Direction::Up;
        isMoving = true;
    }
    else if (GetAsyncKeyState('S') & 0x8000)
    {
        y += moveSpeed*deltaTime;
        direction = Direction::Down;
        isMoving = true;
    }
    else if (GetAsyncKeyState('A') & 0x8000)
    {
        x -= moveSpeed*deltaTime;
        direction = Direction::Left;
        isMoving = true;
    }
    else if (GetAsyncKeyState('D') & 0x8000)
    {
        x += moveSpeed*deltaTime;
        direction = Direction::Right;
        isMoving = true;
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

RECT Character::GetCollisionRect() const {
    RECT collisionRect;

    collisionRect.left = x;
    collisionRect.top = y;
    collisionRect.right = x + 32.0f;
    collisionRect.bottom = y + 32.0f;

    return collisionRect;
}

float Character::GetX() const {
    return x;
}

float Character::GetY() const {
    return y;
}

void Character::SetPosition(float newX, float newY) {
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

