#include "FileReader.h"
#include "Map.h"
#include "Pedestrian.h"
#include <conio.h>

const int MAX_NUM_FPS = 15;

void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void CloseConsole() {
    HWND hwnd = GetConsoleWindow();
    if (hwnd != NULL) {
        PostMessage(hwnd, WM_CLOSE, 0, 0);
    }
}

int main()
{
    srand(time(NULL));

    FileReader file;
    Settings settings;
    file.ReadSettings("config.txt", settings);
    Map m(settings);
    CJ cj;
    Pedestrians p;

    bool gameIsOver = false;

    while(!gameIsOver)
    {
        if (GetAsyncKeyState(VK_ESCAPE)) {
            gameIsOver = true;
            CloseConsole();
            break;
        }
        cj.MoveCJ(m.limiteMov_X, m.limiteMov_Y, m, p, settings);
        m.box[cj.prevPos.y][cj.prevPos.x] = static_cast<Boxes>(Boxes::VACIO);
        m.box[cj.pos.y][cj.pos.x] = static_cast<Boxes>(cj.CJLook);

        p.PedestrianManagment(cj.pos.x,cj.pos.y, m, settings);

        m.PintarVista(cj.pos);
        gotoxy(0,60);
        cout << "Money: " << cj.money;

        Sleep(1000 / MAX_NUM_FPS);
        system("cls");

    }
}
