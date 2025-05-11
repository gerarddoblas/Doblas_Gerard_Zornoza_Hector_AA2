#pragma once
#include <iostream>
#include <Windows.h>
#include "Types.h"
#include "Map.h"
#include "FileReader.h"
#include "Pedestrian.h"

class Map;
class Pedestrians;

enum class CJMovement {
    UP,

    DOWN,

    LEFT,

    RIGHT,

    NONE
};


struct CJ {
public:

    CJ();

    int money;
    Position pos;
    Position prevPos;
    char CJLook;

    void MoveCJ(int mapBorderX, int mapBorderY, Map& map, Pedestrians& pedestrians, Settings& settings);

private:

    CJMovement currentMove;

    void SetCJPos(int mapBorderX, int mapBorderY);
    void GetMoney(Map& map, Settings& settings);

};

