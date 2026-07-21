#pragma once
#include <windows.h>
#include <gdiplus.h>

class Monster;
class Character;

class MonsterSpawner {
private:
    float spawnX;
    float spawnY;

    float spawnRange;
    float detectRange;
    float attackRange;

    bool spawned;

    Monster* monster;

    const wchar_t* walkImagePath;
    const wchar_t* attackImagePath;

public:
    MonsterSpawner(
        float x,
        float y,
        float spawnTriggerRange,
        float monsterDetectRange,
        float monsterAttackRange,
        const wchar_t* walkPath,
        const wchar_t* attackPath
    );

    ~MonsterSpawner();

    void Update(float deltaTime, Character* player);
    void Draw(Gdiplus::Graphics& graphics);
};
