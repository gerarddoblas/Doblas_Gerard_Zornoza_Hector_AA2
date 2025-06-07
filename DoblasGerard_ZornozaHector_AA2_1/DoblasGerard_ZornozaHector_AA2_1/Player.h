#pragma once
#include <iostream>
#include <Windows.h>
#include "Types.h"
#include "Map.h"
#include "FileReader.h"
#include "Walker.h"
#include "Car.h"

#define VK_E 'E'

class Map;
class Walkers;
class Cars;

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

    CJ();

    int money;
    Position pos;
    Position prevPos;
    char CJLook;
    CJDrive driving;

    void MoveCJ(int mapBorderX, int mapBorderY, Map& map, Walkers& pedestrians, Settings& settings, Cars& cars);

private:

    CJMovement currentMove;



    void SetCJPos(int mapBorderX, int mapBorderY);
    void GetMoney(Map& map, Settings& settings);
    void WalkersMoneyCars(Map& map, Settings& settings);

};


