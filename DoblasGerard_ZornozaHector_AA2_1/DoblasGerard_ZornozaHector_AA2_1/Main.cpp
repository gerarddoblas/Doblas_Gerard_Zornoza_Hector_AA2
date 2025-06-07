#include "FileReader.h"
#include "Map.h"
#include "Walker.h"
#include "Car.h"
#include <conio.h>

const int MAX_NUM_FPS = 15;

enum class GameScenes {
    MAIN_MENU, 
    SPLASH_SCREEN, 
    GAMEPLAY, 
    GAMEOVER
};

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
    Walkers p;
    Cars c;
    GameScenes currentScene = GameScenes::SPLASH_SCREEN;
 

    bool gameIsOver = false;
    float splashScreeenTimer = 0.0f;
    int inputMainMenu;

    while (!gameIsOver)
    {
        if (GetAsyncKeyState(VK_ESCAPE)) {
            gameIsOver = true;
            CloseConsole();
            break;
        }

        switch (currentScene)
        {
        case GameScenes::SPLASH_SCREEN:
            system("cls");
            std::cout << "========BIENVENIDO A GTA ENTI CITY========="<< std::endl;
            Sleep(3000);
            system("cls");
            currentScene = GameScenes::MAIN_MENU;
            break;

            case GameScenes::MAIN_MENU:
                std::cout << "========BIENVENIDO A GTA ENTI CITY=========" << std::endl;
                std::cout << std::endl;
                std::cout << std::endl;
                std::cout << std::endl;
                std::cout << std::endl;
                std::cout << std::endl;
                std::cout << std::endl;
                std::cout << "                   Play" << std::endl;
                std::cout << "                   Exit" << std::endl;
                std::cout << "Esc to exit " << std::endl;
                std::cout << "1 to play" << std::endl;

                std::cin >> inputMainMenu;

                if (inputMainMenu == 1) {
                    currentScene = GameScenes::GAMEPLAY;
                    std::cout << "Loading game";
                }
                break;
              
            case GameScenes::GAMEPLAY:
                cj.MoveCJ(m.limiteMov_X, m.limiteMov_Y, m, p, settings, c);
                m.box[cj.prevPos.y][cj.prevPos.x] = static_cast<Boxes>(Boxes::VACIO);
                m.box[cj.pos.y][cj.pos.x] = static_cast<Boxes>(cj.CJLook);

                p.WalkerManagment(cj.pos.x, cj.pos.y, m, settings);
                c.CarsManagment(m, settings);

                if (cj.money >= 150)
                    m.UnlockFierro();

                if(cj.money >= 350)
                    m.UnlockVenturas();

                m.PintarVista(cj.pos);
                gotoxy(0, 60);
                std::cout << "Money: " << cj.money;

                Sleep(1000 / MAX_NUM_FPS);
                system("cls");
                break;
        }
    }
}



