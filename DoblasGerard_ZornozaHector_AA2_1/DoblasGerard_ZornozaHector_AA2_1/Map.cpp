#include "Map.h"


Mapa::Mapa(const Settings& settings) {
    srand(time(0));

    FILAS = settings.FILAS;
    COLUMNAS = settings.COLUMNAS;
    SANTOS_PEDESTRIANS_NUMBER = settings.SANTOS_PEDESTRIANS_NUMBER;
    SANTOS_MONEY_REQUIRED = settings.SANTOS_MONEY_REQUIRED;
    FIERRO_PEDESTRIANS_NUMBER = settings.FIERRO_PEDESTRIANS_NUMBER;
    FIERRO_MONEY_REQUIRED = settings.FIERRO_MONEY_REQUIRED;

    limiteMapa_x = settings.COLUMNAS;
    limiteMapa_y = settings.FILAS;
    limiteMov_X = settings.COLUMNAS / 2 + 1;
    limiteMov_Y = settings.FILAS / 2 + 1;

    int tercioColumnas = settings.COLUMNAS / 3;

    boxes = new Box * [FILAS];
    for (int i = 0; i < FILAS; ++i) {
        boxes[i] = new Box[COLUMNAS];

        for (int j = 0; j < COLUMNAS; ++j) {
            boxes[i][j] = Box::VACIO;

            if (i == 0 || j == 0 || i == FILAS - 1 || j == COLUMNAS - 1) {
                boxes[i][j] = Box::PARED;
            }
            else if (j == tercioColumnas || j == tercioColumnas*2) {
                boxes[i][j] = Box::SEPARADOR;
            }
        }
    }

    for (int i = 1; i < FILAS - 1; ++i) {
        for (int j = 1; j < tercioColumnas - 1; ++j) {
            boxes[i][j] = Box::VACIO;
        }
    }

    for (int i = 0; i < SANTOS_PEDESTRIANS_NUMBER; i++) {
        int newPedestrianX, newPedestrianY;
        do {
            newPedestrianX = rand() % (tercioColumnas - 1) + 1;
            newPedestrianY = rand() % (FILAS - 1) + 1;
        } while (boxes[newPedestrianY][newPedestrianX] != Box::VACIO);

        boxes[newPedestrianY][newPedestrianX] = Box::PEATÓN;
    }

    for (int i = 0; i < FIERRO_PEDESTRIANS_NUMBER; i++) {
        int newPedestrianX, newPedestrianY;
        do {
            newPedestrianX = rand() % (tercioColumnas - 1) + tercioColumnas + 1;
            newPedestrianY = rand() % (FILAS - 1) + 1;
        } while (boxes[newPedestrianY][newPedestrianX] != Box::VACIO);

        boxes[newPedestrianY][newPedestrianX] = Box::PEATÓN;
    }
}

Mapa::~Mapa() {
    for (int i = 0; i < FILAS; ++i) {
        delete[] boxes[i];
    }
    delete[] boxes;
}


void Mapa::PintarVista(Position playerPos) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(hConsole, &cursorInfo);

    int clampedViewMinX = std::max<int>(0, playerPos.x - RANGO_VISTA_JUGADOR_X);
    int clampedViewMaxX = std::min<int>(limiteMapa_x, playerPos.x + RANGO_VISTA_JUGADOR_X);
    int clampedViewMinY = std::max<int>(0, playerPos.y - RANGO_VISTA_JUGADOR_Y);
    int clampedViewMaxY = std::min<int>(limiteMapa_y, playerPos.y + RANGO_VISTA_JUGADOR_Y);

    for (int i = clampedViewMinY; i <= clampedViewMaxY; i++) {
        for (int j = clampedViewMinX; j <= clampedViewMaxX; j++) {
            switch (boxes[i][j]) {
            case Box::DIRECCION_IZQUIERDA:
            case Box::DIRECCION_DERECHA:
            case Box::DIRECCION_ABAJO:
            case Box::DIRECCION_ARRIBA:
                SetConsoleTextAttribute(hConsole, 12);
                break;
            case Box::PARED:
                // SetConsoleTextAttribute(hConsole, 8);
                break;
            case Box::SEPARADOR:
                SetConsoleTextAttribute(hConsole, 9);
                break;
            case Box::PEATÓN:
                SetConsoleTextAttribute(hConsole, 10);
                break;
            case Box::DINERO:
                SetConsoleTextAttribute(hConsole, 14);
                break;
            default:
                SetConsoleTextAttribute(hConsole, 15);
                break;
            }
            std::cout << static_cast<char>(boxes[i][j]);
            SetConsoleTextAttribute(hConsole, 15);
        }
        std::cout << std::endl;
    }
}


void Mapa::PintarTodo() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(hConsole, &cursorInfo);

    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            switch (boxes[i][j]) {
            case Box::DIRECCION_IZQUIERDA:
            case Box::DIRECCION_DERECHA:
            case Box::DIRECCION_ABAJO:
            case Box::DIRECCION_ARRIBA:
                SetConsoleTextAttribute(hConsole, 12);
                break;
            case Box::PARED:
                SetConsoleTextAttribute(hConsole, 8);
                break;
            case Box::SEPARADOR:
                SetConsoleTextAttribute(hConsole, 9);
                break;
            case Box::PEATÓN:
                SetConsoleTextAttribute(hConsole, 13);
                break;
            case Box::DINERO:
                SetConsoleTextAttribute(hConsole, 14);
                break;
            default:
                SetConsoleTextAttribute(hConsole, 15);
                break;
            }
            std::cout << static_cast<char>(boxes[i][j]);
            SetConsoleTextAttribute(hConsole, 15);
        }
        std::cout << std::endl;
    }
}



void Mapa::UnlockBosque() {
    limiteMapa_x = COLUMNAS - 1;
    limiteMov_X = COLUMNAS - 1;
    limiteMapa_y = FILAS - 1;

    for (int i = 1; i < FILAS / 2; ++i) {
        boxes[i][COLUMNAS / 2] = Box::VACIO;
    }
}

void Mapa::UnlockCueva() {
    limiteMapa_x = COLUMNAS - 1;
    limiteMov_X = COLUMNAS - 1;
    limiteMov_Y = FILAS - 1;
    limiteMapa_y = FILAS - 1;

    for (int i = COLUMNAS / 2; i < COLUMNAS - 1; ++i) {
        boxes[FILAS / 2][i] = Box::VACIO;
    }
}

Zones Mapa::GetZona(const Position& playerPos) const {
    int mitadFilas = FILAS / 2;
    int mitadColumnas = COLUMNAS / 2;

    if (playerPos.x < mitadColumnas && playerPos.y < mitadFilas) {
        return Zones::LOS_SANTOS;
    }
    else if (playerPos.x >= mitadColumnas && playerPos.y < mitadFilas) {
        return Zones::SAN_FIERRO;
    }
    else{
        return Zones::LAS_VENTURAS;
    }
}
