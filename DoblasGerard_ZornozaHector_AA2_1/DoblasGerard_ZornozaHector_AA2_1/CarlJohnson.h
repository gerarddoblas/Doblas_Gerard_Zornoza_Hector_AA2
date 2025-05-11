#pragma once
#include <iostream>
#include <Windows.h>
#include "Types.h"
#include "Map.h"
#include "FileReader.h"
#include "Pedestrian.h"

class Map;


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

    void MoveCJ(int mapBorderX, int mapBorderY, Map& map, Pedestrians& pedestrians);

private:

    CJMovement currentMove;

    void SetCJPos(int mapBorderX, int mapBorderY);

};

