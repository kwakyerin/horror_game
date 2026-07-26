#pragma once
#include <Windows.h>
#include <gdiplus.h>
class Character;

class QuizGhost {
private:
	float x;
	float y;

	bool isTalking;
	
	Gdiplus::Image* image;
	Gdiplus::Image* Dialogue_box;

public:
	QuizGhost(float startX, float startY,const wchar_t* path);
	~QuizGhost();

	void Draw(Gdiplus::Graphics& graphics);
	void Update(float deltaTime, Character& character);
	void HandleInteraction(Character& player);
	bool IsPlayerNear(const Character& character)const;
	RECT GetCollisionRect() const;
};

