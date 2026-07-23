#pragma once
#include <windows.h>
#include<gdiplus.h>

#include "Character.h"

class KkamakGhost {
private:
	float x;
	float y;
	float moveSpeed;

	Gdiplus::Image* image;

public:
	KkamakGhost();
	~KkamakGhost();

	bool LoadImage(const wchar_t* path);

	void Update();
	void Draw();

	RECT GetCollisionRect() const;
};