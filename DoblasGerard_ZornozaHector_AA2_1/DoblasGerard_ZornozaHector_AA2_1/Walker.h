#pragma once
#include "FileReader.h"
#include "Map.h"
#include <ctime>
#include <chrono>

class Map;

class Walkers {
public:


    int x;
    int y;
    int healthSantos;
    int healthFierro;
    int healthVenturas;
    int damage;

    Walkers(Settings& settings);

    ~Walkers();

    void WalkerManagment(int cJX, int cJY, Map& map, const Settings& settings);
    void WalkerReward(int posX, int posY, Map& map);
    bool WalkerFound(int posX, int posY, Map& map);
    void WalkerAttack(int pedestrianX, int pedestrianY, int& CJ_HP, Map& map, const Settings& settings);

protected:

    int WalkersInSantos;
    int WalkersInFierro;
    int WalkersInVenturas;
    int newWalkerX;
    int newWalkerY;

    int minTime;
    int maxTime;
    int waitTime;

    chrono::time_point<chrono::system_clock> now;
    chrono::duration<double> elapsed_seconds;
    chrono::time_point<chrono::system_clock> lastMoveTime;
    std::chrono::time_point<std::chrono::system_clock> lastAttackTime;

    void WalkerMove(int cJX, int cJY, Map& map, const Settings& settings);
    bool WalkerStop(int cJX, int cJY, int pedestrianX, int pedestrianY);
};


