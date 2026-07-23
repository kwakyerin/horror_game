#pragma once

#include <Windows.h>
#include <gdiplus.h>
class FireBall {
private:
	float x;
	float y;

	float dirX;
	float dirY;

	float speed;

	Gdiplus::Image* image;

	bool active;

	int currentFrame;
	float animationTimer;

	bool LoadImage(const wchar_t* path);
public:
	FireBall(float startX, float startY, float directionX, float directionY);
	~FireBall();

	void Update(float deltaTime);
	void Draw(Gdiplus::Graphics& graphics);
	bool IsActive() const;
	RECT GetCollisionRect() const;
	void Deactivate();
};