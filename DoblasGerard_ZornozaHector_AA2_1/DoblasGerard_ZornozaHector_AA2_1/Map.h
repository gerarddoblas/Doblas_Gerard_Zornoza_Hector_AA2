#pragma once
#include <iostream>
#include <Windows.h>
#include <algorithm>
#include <conio.h>
#include "ConsolUtils.h"
#include "Player.h"
#include "FileReader.h"
#include "Walker.h"

using namespace std;

enum class Boxes {
    VACIO = ' ',

    PARED = 'X',

    PEAJE = 'T',

    PEATÓN = 'P',

    DINERO = '$',

    COCHE = 'C',

    BIGSMOKE = 'B',

    DIRECCION_IZQUIERDA = '<',

    DIRECCION_DERECHA = '>',

    DIRECCION_ABAJO = 'v',

    DIRECCION_ARRIBA = '^'
};

enum class Zones {
    LOS_SANTOS,
    SAN_FIERRO,
    LAS_VENTURAS,
};

struct Map {
public:
    Map(const Settings& settings);

    ~Map();

    void PintarVista(Position playerPos);
    void PintarTodo();
    void UnlockFierro();
    void UnlockVenturas();

    int limiteMov_X;
    int limiteMov_Y;

    int newBossX;
    int newBossY;

    Boxes** box;

private:

    int ROWS;
    int COLUMNS;
    int SANTOS_PEDESTRIANS_NUMBER;
    int SANTOS_MONEY_REQUIRED;
    int SANTOS_HP;
    int SANTOS_DM;
    int FIERRO_PEDESTRIANS_NUMBER;
    int FIERRO_MONEY_REQUIRED;
    int FIERRO_HP;
    int FIERRO_DM;
    int VENTURAS_PEDESTRIANS_NUMBER;
    int VENTURAS_HP;
    int VENTURAS_DM;

    int mapBoundary_x;
    int mapBoundary_y;

    const int PLAYER_VIEW_RANGE_X = 22;
    const int PLAYER_VIEW_RANGE_Y = 12;

};