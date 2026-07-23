#pragma once
#include "Monster.h"
#include "FireBall.h"

#include<vector>

class Gumiho :public Monster {
private:
	std::vector<FireBall*> fireBalls;
public:
	Gumiho(const wchar_t* walkPath, const wchar_t* attackPath, float startX, float startY, float detectRange, float attackRange);
	~Gumiho();

	void UpdateFireBalls(float deltaTime);
	void DrawFireBalls(Gdiplus::Graphics& graphics);

protected:
	void UpdateAttack(float deltaTime, Character& character)override;
};