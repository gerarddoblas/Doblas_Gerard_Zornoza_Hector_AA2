#include "Map.h"


Map::Map(const Settings& settings) {
    srand(time(0));

    ROWS = settings.ROWS;
    COLUMNS = settings.COLUMNS;
    SANTOS_PEDESTRIANS_NUMBER = settings.SANTOS_PEDESTRIANS_NUMBER;
    SANTOS_MONEY_REQUIRED = settings.SANTOS_MONEY_REQUIRED;
    FIERRO_PEDESTRIANS_NUMBER = settings.FIERRO_PEDESTRIANS_NUMBER;
    FIERRO_MONEY_REQUIRED = settings.FIERRO_MONEY_REQUIRED;

    mapBoundary_x = settings.COLUMNS;
    mapBoundary_y = settings.ROWS;
    limiteMov_X = settings.COLUMNS;
    limiteMov_Y = settings.ROWS;

    int tercioColumnas = settings.COLUMNS / 3;

    box = new Boxes * [ROWS];
    for (int i = 0; i < ROWS; ++i) {
        box[i] = new Boxes[COLUMNS];

        for (int j = 0; j < COLUMNS; ++j) {
            box[i][j] = Boxes::VACIO;

            if (i == 0 || j == 0 || i == ROWS - 1 || j == COLUMNS - 1) {
                box[i][j] = Boxes::PARED;
            }
            //Codigo con el que identificar los tercios del mapa
           /* else if (j == tercioColumnas || j == tercioColumnas * 2) {
                box[i][j] = Boxes::SEPARADOR;
            }*/
        }
    }

    for (int i = 1; i < ROWS - 1; ++i) {
        for (int j = 1; j < tercioColumnas - 1; ++j) {
            box[i][j] = Boxes::VACIO;
        }
    }

    for (int i = 0; i < SANTOS_PEDESTRIANS_NUMBER; i++) {
        int newPedestrianX, newPedestrianY;
        do {
            newPedestrianX = rand() % (tercioColumnas - 1) + 1;
            newPedestrianY = rand() % (ROWS - 1) + 1;
        } while (box[newPedestrianY][newPedestrianX] != Boxes::VACIO);

        box[newPedestrianY][newPedestrianX] = Boxes::PEATÓN;
    }

    for (int i = 0; i < FIERRO_PEDESTRIANS_NUMBER; i++) {
        int newPedestrianX, newPedestrianY;
        do {
            newPedestrianX = rand() % (tercioColumnas - 1) + tercioColumnas + 1;
            newPedestrianY = rand() % (ROWS - 1) + 1;
        } while (box[newPedestrianY][newPedestrianX] != Boxes::VACIO);

        box[newPedestrianY][newPedestrianX] = Boxes::PEATÓN;
    }
}

Map::~Map() {
    for (int i = 0; i < ROWS; ++i) {
        delete[] box[i];
    }
    delete[] box;
}


void Map::PintarVista(Position playerPos) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(hConsole, &cursorInfo);

    int clampedViewMinX = std::max<int>(0, playerPos.x - PLAYER_VIEW_RANGE_X);
    int clampedViewMaxX = std::min<int>(mapBoundary_x, playerPos.x + PLAYER_VIEW_RANGE_X);
    int clampedViewMinY = std::max<int>(0, playerPos.y - PLAYER_VIEW_RANGE_Y);
    int clampedViewMaxY = std::min<int>(mapBoundary_y, playerPos.y + PLAYER_VIEW_RANGE_Y);

    for (int i = clampedViewMinY; i < clampedViewMaxY; i++) {
        for (int j = clampedViewMinX; j < clampedViewMaxX; j++) {
            switch (box[i][j]) {
            case Boxes::DIRECCION_IZQUIERDA:
            case Boxes::DIRECCION_DERECHA:
            case Boxes::DIRECCION_ABAJO:
            case Boxes::DIRECCION_ARRIBA:
                SetConsoleTextAttribute(hConsole, 12);
                break;
            case Boxes::PARED:
                SetConsoleTextAttribute(hConsole, 8);
                break;
            case Boxes::SEPARADOR:
                SetConsoleTextAttribute(hConsole, 9);
                break;
            case Boxes::PEATÓN:
                SetConsoleTextAttribute(hConsole, 10);
                break;
            case Boxes::DINERO:
                SetConsoleTextAttribute(hConsole, 14);
                break;
            default:
                SetConsoleTextAttribute(hConsole, 15);
                break;
            }
            std::cout << static_cast<char>(box[i][j]);
            SetConsoleTextAttribute(hConsole, 15);
        }
        std::cout << std::endl;
    }
}


void Map::PintarTodo() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(hConsole, &cursorInfo);

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLUMNS; j++) {
            switch (box[i][j]) {
            case Boxes::DIRECCION_IZQUIERDA:
            case Boxes::DIRECCION_DERECHA:
            case Boxes::DIRECCION_ABAJO:
            case Boxes::DIRECCION_ARRIBA:
                SetConsoleTextAttribute(hConsole, 12);
                break;
            case Boxes::PARED:
                SetConsoleTextAttribute(hConsole, 8);
                break;
            case Boxes::SEPARADOR:
                SetConsoleTextAttribute(hConsole, 9);
                break;
            case Boxes::PEATÓN:
                SetConsoleTextAttribute(hConsole, 13);
                break;
            case Boxes::DINERO:
                SetConsoleTextAttribute(hConsole, 14);
                break;
            default:
                SetConsoleTextAttribute(hConsole, 15);
                break;
            }
            std::cout << static_cast<char>(box[i][j]);
            SetConsoleTextAttribute(hConsole, 15);
        }
        std::cout << std::endl;
    }
}
