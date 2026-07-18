#include "MonsterSpawner.h"
#include <cmath>

MonsterSpawner::MonsterSpawner(
    float x,
    float y,
    float spawnTriggerRange,
    float monsterDetectRange,
    float monsterAttackRange,
    const wchar_t* walkPath,
    const wchar_t* attackPath)
{
    spawnX = x;
    spawnY = y;

    spawnRange = spawnTriggerRange;
    detectRange = monsterDetectRange;
    attackRange = monsterAttackRange;

    walkImagePath = walkPath;
    attackImagePath = attackPath;

    spawned = false;
    monster = nullptr;
}

MonsterSpawner::~MonsterSpawner()
{
    delete monster;
    monster = nullptr;
}

void MonsterSpawner::Update(
    float deltaTime,
    Character* player)
{
    if (player == nullptr)
        return;

    // 아직 생성되지 않은 경우에만
    // 플레이어와 스폰 지점 사이의 거리를 검사한다.
    if (!spawned)
    {
        float dx = player->GetX() - spawnX;
        float dy = player->GetY() - spawnY;

        float distance = std::sqrt(dx * dx + dy * dy);

        if (distance <= spawnRange)
        {
            monster = new Monster(
                walkImagePath,
                attackImagePath,
                spawnX,
                spawnY,
                detectRange,
                attackRange
            );

            spawned = true;
        }
    }

    // 생성된 이후에는 몬스터를 업데이트한다.
    if (monster != nullptr)
    {
        monster->Update(deltaTime, *player);
    }
}

void MonsterSpawner::Draw(Gdiplus::Graphics& graphics)
{
    if (monster != nullptr)
    {
        monster->Draw(graphics);
    }
}