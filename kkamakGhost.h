#pragma once
#include <windows.h>
#include<gdiplus.h>

#include "Character.h"

class KkamakGhost {
private:
	float x;
	float y;
	float moveSpeed;
	float startX;
	float startY;
	Gdiplus::Image* image;

public:
	KkamakGhost(float startX,float startY,const wchar_t* path);
	~KkamakGhost();

	bool LoadImage(const wchar_t* path);

	bool Update(float deltaTime,const Character& character);
	void Draw(Gdiplus::Graphics& graphics);

	bool IsPlayerLooking(const Character& character) const;
	bool IsCollidingWithPlayer(const Character& character)const;

	RECT GetCollisionRect() const;
	void Reset();
};