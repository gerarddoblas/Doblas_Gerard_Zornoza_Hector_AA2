#pragma once
#include "Walker.h"
#include "FileReader.h"
#include "Map.h"
#include <ctime>
#include <chrono>

class Map;

class Boss {
public:

    void WalkerManagment(int cJX, int cJY, Map& map, Settings& settings);
    void WalkerFound(int posX, int posY, Map& map);
    void WalkerHunting(int pedestrianX, int pedestrianY, Map& map, Settings& settings);
    void WalkerAttack(int cJX, int cJY, Map& map, Settings& settings, int& playerHealth);

protected:

    int WalkersInSantos;
    int WalkersInFierro;
    int newWalkerX;
    int newWalkerY;

    int minTime;
    int maxTime;
    int waitTime;


    chrono::time_point<chrono::system_clock> now;
    chrono::duration<double> elapsed_seconds;
    chrono::time_point<chrono::system_clock> lastMoveTime;
    std::chrono::time_point<std::chrono::system_clock> lastAttackTime;

    void WalkerMove(int cJX, int cJY, Map& map, Settings& settings);
    bool WalkerStop(int cJX, int cJY, int pedestrianX, int pedestrianY);
};

