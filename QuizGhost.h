#pragma once
#include <Windows.h>
#include <gdiplus.h>
#include "Dialogue.h"

class Character;
class Dialogue;

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

	void HandleInteraction(Character& character,Dialogue& dialogue);
	bool IsPlayerNear(const Character& character)const;

	RECT GetCollisionRect() const;
};

