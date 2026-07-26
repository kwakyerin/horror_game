#include "ResetGame.h"
#include "Map.h"
#include "Character.h"

extern Map VillageMap;
extern Character* player;

void ResetGame() {

    VillageMap.changeMap(MapType::Room);

    // 캐릭터를 집 안 시작 좌표로 초기화
    if (player != nullptr)
    {
        player->Reset();
    }
}