#include "MonsterSpawner.h"
#include "Map.h"
#include "Character.h"
#include "Monster.h"
#include "Gumiho.h"
#include "ShadowGhost.h"
#include <cmath>

MonsterSpawner::MonsterSpawner(MonsterType type,float x,float y,float spawnTriggerRange,float monsterDetectRange,float monsterAttackRange,const wchar_t* walkPath,const wchar_t* attackPath)
{
    monsterType = type;
    spawnX = x;
    spawnY = y;

    spawnRange = spawnTriggerRange;
    detectRange = monsterDetectRange;
    attackRange = monsterAttackRange;

    walkImagePath = walkPath;
    attackImagePath = attackPath;

    spawned = false;
    monster = nullptr;
    shadowGhost = nullptr;
}

MonsterSpawner::~MonsterSpawner()
{
    delete monster;
    delete shadowGhost;
    monster = nullptr;
    shadowGhost = nullptr;
}

void MonsterSpawner::Update(float deltaTime,Character* player)
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

            switch (monsterType)
            {
            case MonsterType::Oni:
                monster = new Monster(
                    walkImagePath,
                    attackImagePath,
                    spawnX,
                    spawnY,
                    detectRange,
                    attackRange
                );
                break;

            case MonsterType::Gumiho:
                monster = new Gumiho(
                    walkImagePath,
                    attackImagePath,
                    spawnX,
                    spawnY,
                    detectRange,
                    attackRange
                );
                break;

            case MonsterType::ShadowGhost:
                shadowGhost = new ShadowGhost{
                    walkImagePath,
                    attackImagePath,
                    spawnX,
                    spawnY
                };

               // MessageBox(
                   // nullptr,
                   // L"ShadowGhost 생성됨",
                    //L"Debug",
                   // MB_OK
                //);
                break;

            }

            spawned = true;
        }
    }

    // 생성된 이후에는 몬스터를 업데이트한다.
    if (monster != nullptr)
    {
        monster->Update(deltaTime, *player);
        monster->UpdateSpecial(deltaTime,*player);
    }

    if (shadowGhost != nullptr)
    {
        shadowGhost->Update(deltaTime, *player);
    }
}

void MonsterSpawner::Draw(Gdiplus::Graphics& graphics)
{
    if (monster != nullptr)
    {
        monster->Draw(graphics);
        monster->DrawSpecial(graphics);
    }

    if (shadowGhost != nullptr)
    {
        shadowGhost->Draw(graphics);
    }
}

bool MonsterSpawner::HasSpawnedMonster() const
{
    return monster != nullptr || shadowGhost != nullptr;
}

RECT MonsterSpawner::GetCollisionRect() const
{
    // 오니 또는 구미호
    if (monster != nullptr)
    {
        return monster->GetCollisionRect();
    }

    // 그림자 요괴
    if (shadowGhost != nullptr)
    {
        return shadowGhost->GetCollisionRect();
    }

    return RECT{ 0, 0, 0, 0 };
}