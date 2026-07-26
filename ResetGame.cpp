#include "ResetGame.h"
#include "Map.h"
#include "Character.h"
#include "MonsterSpawner.h"
#include "kkamakGhost.h"

extern Map VillageMap;
extern Character* player;
extern MonsterSpawner* oniSpawner;
extern MonsterSpawner* gumihoSpawner;
extern MonsterSpawner* shadowSpawner;
extern KkamakGhost* kkamakGhost;


void ResetGame() {

    VillageMap.changeMap(MapType::Room);

    // 캐릭터를 집 안 시작 좌표로 초기화
    if (player != nullptr)
    {
        player->Reset();
    }
    if (oniSpawner != nullptr)
    {
        oniSpawner->Reset();
    }

    if (gumihoSpawner != nullptr)
    {
        gumihoSpawner->Reset();
    }

    if (shadowSpawner != nullptr)
    {
        shadowSpawner->Reset();
    }

    if (kkamakGhost != nullptr)
    {
        kkamakGhost->Reset();
    }
}