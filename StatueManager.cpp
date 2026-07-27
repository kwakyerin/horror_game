#include "StatueManager.h"
#include "Character.h"

StatueManager::StatueManager()
    : yellowDone(false),
    redDone(false),
    blueDone(false),
    blackDone(false),
    whiteDone(false)
{
}

bool StatueManager::Interact(Character* player,Map& map,std::vector<Amulet>& amulets)
{
    if (player == nullptr)
    {
        return false;
    }

    if (TryAttachAmulet(
        player,
        map,
        amulets,
        12,
        2,
        AmuletType::White,
        Status_White,
        whiteDone
    ))
    {
        return true;
    }

    if (TryAttachAmulet(
        player,
        map,
        amulets,
        17,
        11,
        AmuletType::Red,
        Status_Red,
        redDone
    ))
    {
        return true;
    }

    if (TryAttachAmulet(
        player,
        map,
        amulets,
        8,
        14,
        AmuletType::Blue,
        Status_Blue,
        blueDone
    ))
    {
        return true;
    }

    if (TryAttachAmulet(
        player,
        map,
        amulets,
        20,
        5,
        AmuletType::Yellow,
        Status_Yellow,
        yellowDone
    ))
    {
        return true;
    }

    if (TryAttachAmulet(
        player,
        map,
        amulets,
        3,
        8,
        AmuletType::Black,
        Status_Black,
        blackDone
    ))
    {
        return true;
    }

    return false;
}

bool StatueManager::TryAttachAmulet(Character* player,Map& map,std::vector<Amulet>& amulets,
    int tileX,
    int tileY,
    AmuletType requiredType,
    int changedTile,
    bool& done
)
{

    if (map.GetCurrentMap() != MapType::Field)
    {
        return false;
    }

    if (done)
    {
        return false;
    }

    float statueX =
        static_cast<float>(tileX * Tile_Size);

    float statueY =
        static_cast<float>(tileY * Tile_Size);

    float distanceX =
        player->GetX() - statueX;

    float distanceY =
        player->GetY() - statueY;

    if (distanceX < 0)
    {
        distanceX = -distanceX;
    }

    if (distanceY < 0)
    {
        distanceY = -distanceY;
    }

    float interactionRange =
        Tile_Size * 2.0f;

    if (distanceX > interactionRange ||
        distanceY > interactionRange)
    {
        return false;
    }

    for (Amulet& amulet : amulets)
    {
        if (amulet.GetType() == requiredType &&
            amulet.IsCollected() &&
            !amulet.IsUsed())
        {
            map.SetTile(
                tileX,
                tileY,
                changedTile
            );

            amulet.Use();
            done = true;

            return true;
        }
    }

    return false;
}

void StatueManager::Reset()
{
    whiteDone = false;
    redDone = false;
    blueDone = false;
    yellowDone = false;
    blackDone = false;
}

void StatueManager::ApplyCompletedStatues(Map& map)
{
    if (whiteDone)
    {
        map.SetTile(
            12,
            2,
            Status_White
        );
    }

    if (redDone)
    {
        map.SetTile(
            17,
            11,
            Status_Red
        );
    }

    if (blueDone)
    {
        map.SetTile(
            8,
            14,
            Status_Blue
        );
    }

    if (yellowDone)
    {
        map.SetTile(
            20,
            5,
            Status_Yellow
        );
    }

    if (blackDone)
    {
        map.SetTile(
            3,
            8,
            Status_Black
        );
    }
}