#pragma once
#include <windows.h>
#include <gdiplus.h>

class Monster;
class ShadowGhost;
class Character;

enum class MonsterType
{
    Oni,
    Gumiho,
    ShadowGhost
};

class MonsterSpawner {
private:
    float spawnX;
    float spawnY;

    float spawnRange;
    float detectRange;
    float attackRange;

    bool spawned;

    Monster* monster;
    ShadowGhost* shadowGhost;

    MonsterType monsterType;

    const wchar_t* walkImagePath;
    const wchar_t* attackImagePath;

public:
    MonsterSpawner(
        MonsterType type,
        float x,
        float y,
        float spawnTriggerRange,
        float monsterDetectRange,
        float monsterAttackRange,
        const wchar_t* walkPath,
        const wchar_t* attackPath
    );

    ~MonsterSpawner();
    bool HasSpawnedMonster()const;
    RECT GetCollisionRect()const;
    void Update(float deltaTime, Character* player);
    void Draw(Gdiplus::Graphics& graphics);
    void Reset();
};
