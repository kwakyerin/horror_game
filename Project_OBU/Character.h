#pragma once

#include <windows.h>
#include <gdiplus.h>

enum class Direction {
	Down,
	Left,
	Right,
	Up
};
class Character {
private:
	float x, y;
	float moveSpeed;
	int currentFrame;
	float animationTimer;
	Direction direction;
	Gdiplus::Image* image;
	bool LoadImage(const wchar_t*path);
public:
	Character(const wchar_t* path);
	~Character();
	void Move(float deltaTime);
	void Draw(Gdiplus::Graphics& graphics);
};