#pragma once
#include <vector>

#include "Map.h"
#include "Amulet.h"

class Character;
class StatueManager
{
public:
    StatueManager();

    bool Interact(Character* player,Map& map,std::vector<Amulet>& amulets);

private:
    bool TryAttachAmulet(Character* player,Map& map,std::vector<Amulet>& amulets,
        int tileX,
        int tileY,
        AmuletType requiredType,
        int changedTile,
        bool& done
    );
    bool yellowDone;
    bool redDone;
    bool blueDone;
    bool blackDone;
    bool whiteDone;
};