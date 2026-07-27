#include "Character.h"
#include "Amulet.h"



Amulet::Amulet(MapType mapType,float x,float y, AmuletType type)
	:mapType(mapType),
    x(x),
	y(y),
	collected(false),
    type(type),
    used(false)

{

}

bool Amulet::Interact(Character* character,MapType currentMap)
{
    if (character == nullptr)
    {
        return false;
    }

    if (collected)
    {
        return false;
    }

    if (currentMap != mapType)
    {
        return false;
    }

    if (!IsPlayerNear(character))
    {
        return false;
    }

    collected = true;

    // 나중에 추가
    //dialogue.Open(L"부적을 획득했다.");
    // 효과음 재생

    return true;
}

bool Amulet::IsCollected() const
{
    return collected;
}

bool Amulet::IsPlayerNear(Character* player) const
{
    if (player == nullptr)
    {
        return false;
    }

    float dx = player->GetX() - x;
    float dy = player->GetY() - y;

    float distanceSquared = dx * dx + dy * dy;
    float interactionRange = 40.0f;

    return distanceSquared <= interactionRange * interactionRange;
}
MapType Amulet::GetMapType() const
{
    return mapType;
}
AmuletType Amulet::GetType() const
{
    return type;
}

float Amulet::GetX() const
{
    return x;
}

float Amulet::GetY() const
{
    return y;
}

bool Amulet::IsUsed() const
{
    return used;
}

void Amulet::Use()
{
    used = true;
}

void Amulet::Reset()
{
    collected = false;
    used = false;
}