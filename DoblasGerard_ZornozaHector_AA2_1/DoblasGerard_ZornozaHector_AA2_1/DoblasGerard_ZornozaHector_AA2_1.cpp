#include "FileReader.h"
#include "Map.h"
#include "Pedestrian.h"
#include <conio.h>

const int MAX_NUM_FPS = 15;

int main()
{
    FileReader file;
    Settings settings;
    file.ReadSettings("config.txt", settings);
    Map m(settings);
    CJ cj;
    Pedestrians p;

    bool gameIsOver = false;

    while(!gameIsOver)
    {
        cj.MoveCJ(m.limiteMov_X, m.limiteMov_Y, m, p);
        m.box[cj.prevPos.y][cj.prevPos.x] = static_cast<Boxes>(Boxes::VACIO);
        m.box[cj.pos.y][cj.pos.x] = static_cast<Boxes>(cj.CJLook);
        //m.PintarTodo();
        m.PintarVista(cj.pos);

        Sleep(1000 / MAX_NUM_FPS);
        system("cls");

    }
 

}
