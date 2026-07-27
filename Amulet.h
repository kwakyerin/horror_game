#pragma once
#include "Map.h"
class Character;
enum class AmuletType
{
	Yellow=0,
	Red,
	Blue,
	White,
	Black
};
class Amulet {
private:
	MapType mapType;
	float x;
	float y;

	bool collected;
	AmuletType type;

	bool used;

public:
	Amulet(MapType mapType, float x, float y, AmuletType type);
	MapType GetMapType() const;
	AmuletType GetType() const;
	bool Interact(Character* character, MapType currentMap);
	bool IsPlayerNear(Character* character)const;
	bool IsCollected()const;
	float GetX() const;
	float GetY() const;
	bool IsUsed() const;
	void Use();
	void Reset();
};