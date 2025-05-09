#pragma once
#include <iostream>
#include <fstream>
#include <Windows.h>
#include <algorithm>
#include "Types.h"
#include "CarlJohnson.h"
#include "FileReader.h"

enum class Box {
    VACIO = ' ',

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

struct Mapa {
public:

    Mapa(const Settings& settings);

    ~Mapa();

    void PintarVista(Position playerPos);
    void PintarTodo();
    void UnlockBosque();
    void UnlockCueva();
    Zones GetZona(const Position& playerPos) const;

    int limiteMov_X;
    int limiteMov_Y;




    Box** boxes;


private:

    int FILAS;
    int COLUMNAS;
    int SANTOS_PEDESTRIANS_NUMBER;
    int SANTOS_MONEY_REQUIRED;
    int FIERRO_PEDESTRIANS_NUMBER;
    int FIERRO_MONEY_REQUIRED;

    int limiteMapa_x;
    int limiteMapa_y;

    const int RANGO_VISTA_JUGADOR_X = 22;
    const int RANGO_VISTA_JUGADOR_Y = 12;

};
