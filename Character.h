#pragma once

#include <windows.h>
#include <gdiplus.h>
#include "Map.h"

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
	int hp;
	Direction direction;
	Gdiplus::Image* image;
	bool LoadImage(const wchar_t*path);

public:

	Character(const wchar_t* path);
	~Character();
    void Move(float deltaTime, Map& gameMap);
	void Draw(Gdiplus::Graphics& graphics);

	//충돌박스
	RECT GetCollisionRect() const;
	float GetX() const;
	float GetY() const;
	void SetPosition(float newX, float newY);
	int GetHP() const;
	void Damage(int amount);
};