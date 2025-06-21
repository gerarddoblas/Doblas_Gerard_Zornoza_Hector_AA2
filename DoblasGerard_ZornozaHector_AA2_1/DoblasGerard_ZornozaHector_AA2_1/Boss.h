#pragma once
#include "Walker.h"
#include "FileReader.h"
#include "Map.h"
#include <ctime>
#include <chrono>

class Map;

class Boss {
public:
    Boss(const Settings& settings, Map& map);

    ~Boss();
    void BossAttack(int cJX, int cJY, Map& map, const Settings& settings, int& playerHealth);
    bool BossFound(int posX, int posY, Map& map);
    int health;

protected:
    int damage;

    chrono::time_point<chrono::system_clock> now;
    chrono::duration<double> elapsed_seconds;
    std::chrono::time_point<std::chrono::system_clock> lastAttackTime;
};