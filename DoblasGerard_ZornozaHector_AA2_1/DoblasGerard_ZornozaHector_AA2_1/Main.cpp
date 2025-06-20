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

void ShowMainMenu(GameScenes& currentScene)
{
    int selectOption = 0;
    bool selectionMade = false;

    while (!selectionMade)
    {
        system("cls");
        std::cout << R"( 
___  ___      _        ___  ___                 
|  \/  |     (_)       |  \/  |                 
| .  . | __ _ _ _ __   | .  . | ___ _ __  _   _ 
| |\/| |/ _` | | '_ \  | |\/| |/ _ \ '_ \| | | |
| |  | | (_| | | | | | | |  | |  __/ | | | |_| |
\_|  |_/\__,_|_|_| |_| \_|  |_/\___|_| |_|\__,_|

)";
        std::cout << (selectOption == 0 ? "> " : "  ") << "1. Play\n";
        std::cout << (selectOption == 1 ? "> " : "  ") << "2. Exit\n";
        std::cout << "\033[36m";


        switch (_getch()) {
        case 72:
            selectOption = (selectOption - 1 + 2) % 2;
            break;
        case 80:
            selectOption = (selectOption + 1) % 2;
            break;
        case 13:
            if (selectOption == 0) {
                currentScene = GameScenes::GAMEPLAY;
            }
            else {
                exit(0);
            }

            selectionMade = true;

            break;
        }

    }
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
        {
            system("cls");
            std::cout << "\033[38;5;208m";
            std::cout << R"()";
            std::cout << "\033[0m";
            std::cout << R"()";


            Sleep(3000);
            system("cls");
            currentScene = GameScenes::MAIN_MENU;
        }
        break;

        case GameScenes::MAIN_MENU:
        {
            ShowMainMenu(currentScene);
            system("cls");
        }
        break;
        case GameScenes::GAMEPLAY:
        {
            cj.MoveCJ(m.limiteMov_X, m.limiteMov_Y, m, p, settings, c);
            if (cj.money >= settings.FIERRO_MONEY_REQUIRED && m.box[cj.pos.y][cj.pos.x] == Boxes::PEAJE)
            {
                m.UnlockFierro();

            }
            else if (m.box[cj.pos.y][cj.pos.x] == Boxes::PEAJE)
            {
                exit(0);
            }
            m.box[cj.prevPos.y][cj.prevPos.x] = static_cast<Boxes>(Boxes::VACIO);
            m.box[cj.pos.y][cj.pos.x] = static_cast<Boxes>(cj.CJLook);

            p.WalkerManagment(cj.pos.x, cj.pos.y, m, settings);
            c.CarsManagment(m, settings);
            //Aqui va la funcion management del boss
            

            m.PintarVista(cj.pos);
            Sleep(1000 / MAX_NUM_FPS);
            system("cls");

            
        }
        break;

        case GameScenes::GAMEOVER:
        {
            system("cls");
            std::cout << "\033[38;5;153m";
            std::cout << R"()";
            std::cout << "\033[0m";
            std::cout << R"(
   _____                       ____                 
  / ____|                     / __ \                
 | |  __  __ _ _ __ ___   ___| |  | |_   _____ _ __ 
 | | |_ |/ _` | '_ ` _ \ / _ \ |  | \ \ / / _ \ '__|
 | |__| | (_| | | | | | |  __/ |__| |\ V /  __/ |   
  \_____|\__,_|_| |_| |_|\___|\____/  \_/ \___|_| 
            
)";
            Sleep(5000);
            currentScene = GameScenes::MAIN_MENU;
        }
            break;
        default:

            break;
        }
    }

    return 0;
}