#pragma once
#include <vector>
#include <windows.h>
#include <gdiplus.h>

class Map;

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
    void Move(float deltaTime, Map& gameMap,const std::vector<RECT>& monsterRects);
	void Draw(Gdiplus::Graphics& graphics);

	//충돌박스
	RECT GetCollisionRect() const;
	float GetX() const;
	float GetY() const;
	void SetPosition(float newX, float newY);
	Direction GetDirection() const;
	int GetHP() const;
	void Damage(int amount);
};