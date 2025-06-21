#pragma once
#include <iostream>
#include <Windows.h>
#include "ConsolUtils.h"
#include "Map.h"
#include "FileReader.h"
#include "Walker.h"
#include "Car.h"
#include "Boss.h"

#define VK_E 'E'

class Map;
class Walkers;
class Cars;
class Boss;


enum class CJMovement {
    UP,

    DOWN,

    LEFT,

    RIGHT,

    NONE
};

enum class CJDrive {
    WALK,

    CAR
};

struct CJ {
public:

    CJ(Settings& settings);

    int health;
    int money;
    Position pos;
    Position prevPos;
    char CJLook;
    bool walkerHurt;
    bool bossHurt;
    int chance;
    CJDrive driving;

    void MoveCJ(int mapBorderX, int mapBorderY, Map& map, Walkers& pedestrians, Settings& settings, Cars& cars, Boss& boss);

private:
    

    CJMovement currentMove;

    void SetCJPos(int mapBorderX, int mapBorderY);
    void GetMoney(Map& map, Settings& settings);
    void WalkersMoneyCars(Map& map, Settings& settings);
    void PlayerAttack(Walkers& walkers, Map& map, Settings& settings, Boss& boss);
};