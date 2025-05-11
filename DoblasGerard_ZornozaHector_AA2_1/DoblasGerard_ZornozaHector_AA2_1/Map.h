#pragma once
#include <iostream>
#include <fstream>
#include <Windows.h>
#include <algorithm>
#include "Types.h"
#include "CarlJohnson.h"
#include "FileReader.h"

enum class Boxes {
    VACIO = '.',

    PARED = 'X',

    SEPARADOR = 'x',

    PEATÓN = 'P',

    DINERO = '$',

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

    int limiteMov_X;
    int limiteMov_Y;




    Boxes** box;


private:

    int ROWS;
    int COLUMNS;
    int SANTOS_PEDESTRIANS_NUMBER;
    int SANTOS_MONEY_REQUIRED;
    int FIERRO_PEDESTRIANS_NUMBER;
    int FIERRO_MONEY_REQUIRED;

    int mapBoundary_x;
    int mapBoundary_y;

    const int PLAYER_VIEW_RANGE_X = 22;
    const int PLAYER_VIEW_RANGE_Y = 12;

};
