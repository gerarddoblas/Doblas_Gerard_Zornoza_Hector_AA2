#include "Map.h"
#include "Walker.h"
#include "Car.h"
#include "GameManager.h"

int main()
{
    srand(time(NULL));

    GameManager game;
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
            game.CloseConsole();
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
            game.ShowMainMenu(currentScene);
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