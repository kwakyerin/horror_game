#pragma once
#include <Windows.h>
#include <gdiplus.h>
class Character;

class QuizGhost {
private:
	float x;
	float y;

	Gdiplus::Image* image;

public:
	QuizGhost(float startX, float startY,const wchar_t* path);
	~QuizGhost();

	void Draw(Gdiplus::Graphics& graphics);
	void Update(float deltaTime, Character& character);
	RECT GetCollisionRect() const;
};

