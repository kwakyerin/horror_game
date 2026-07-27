#include "ResetGame.h"

#include "Map.h"
#include "Character.h"
#include "MonsterSpawner.h"
#include "kkamakGhost.h"
#include "QuizGhost.h"

#include "Amulet.h"
#include "StatueManager.h"

#include <vector>

extern Map VillageMap;
extern Character* player;

extern MonsterSpawner* oniSpawner;
extern MonsterSpawner* gumihoSpawner;
extern MonsterSpawner* shadowSpawner;
extern KkamakGhost* kkamakGhost;
extern QuizGhost* quizGhost;

extern std::vector<Amulet> amulets;
extern StatueManager* statueManager;


void ResetGame() {

    // 1. 조각상 부착 기록 초기화
    if (statueManager != nullptr)
    {
        statueManager->Reset();
    }

    // 2. 부적 획득/사용 상태 초기화
    for (Amulet& amulet : amulets)
    {
        amulet.Reset();
    }

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

    if (quizGhost != nullptr)
    {
        quizGhost->Reset();
    }
}