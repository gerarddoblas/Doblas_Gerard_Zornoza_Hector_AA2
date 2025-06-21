#include "Map.h"
#include "Walker.h"
#include "Car.h"
#include "ConsolUtils.h"
#include "GameManager.h"
#include "Boss.h"
#include "Player.h"

int main()
{
    srand(time(NULL));

    GameManager game;
    FileReader file;
    Settings settings;
    file.ReadSettings("config.txt", settings);
    Map m(settings);
    CJ cj(settings);
    Walkers w(settings);
    Cars c;
    Boss b(settings, m);
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
            game.SplashScreen();
            Sleep(3000);
            system("cls");
            currentScene = GameScenes::MAIN_MENU;
        }
        break;

        case GameScenes::MAIN_MENU:
        {
            system("cls");
            game.ShowMainMenu(currentScene);
            if (currentScene == GameScenes::GAMEPLAY) {
                
                m.~Map();                  
                new(&m) Map(settings);      
                cj.~CJ();
                new(&cj) CJ(settings);
                w.~Walkers();
                new(&w) Walkers(settings);
                b.~Boss();
                new(&b) Boss(settings, m);
            }
            system("cls");
        }
        break;
        case GameScenes::GAMEPLAY:
        {
            cj.MoveCJ(m.limiteMov_X, m.limiteMov_Y, m, w, settings, c, b);
            if (cj.health <= 0)
                currentScene = GameScenes::GAMEOVER;
            if (b.health <= 0)
                currentScene = GameScenes::GAMEOVER;
            if (cj.money < settings.SANTOS_MONEY_REQUIRED && m.box[cj.pos.y][cj.pos.x] == Boxes::PEAJE && m.limiteMov_X == (settings.COLUMNS / 3) + 2)
            {
                currentScene = GameScenes::GAMEOVER;
            }
            else if (m.limiteMov_X == (settings.COLUMNS / 3) + 2 && m.box[cj.pos.y][cj.pos.x] == Boxes::PEAJE && m.limiteMov_X == (settings.COLUMNS / 3) + 2)
            {
                m.UnlockFierro();
                cj.money = cj.money -= settings.SANTOS_MONEY_REQUIRED;
            }
            if (cj.money < settings.FIERRO_MONEY_REQUIRED && m.box[cj.pos.y][cj.pos.x] == Boxes::PEAJE && cj.pos.x > settings.COLUMNS / 3 + 3 && m.limiteMov_X == ((settings.COLUMNS / 3) * 2) + 2)
            {
                currentScene = GameScenes::GAMEOVER;
            }
            else if (m.box[cj.pos.y][cj.pos.x] == Boxes::PEAJE && m.limiteMov_X == ((settings.COLUMNS / 3) * 2) + 2 && cj.pos.x > settings.COLUMNS / 3 + 3)
            {
                m.UnlockVenturas();
                cj.money = cj.money -= settings.FIERRO_MONEY_REQUIRED;
            }
            game.Game(cj, m, settings, w, b, c);
            Sleep(1000 / MAX_NUM_FPS);
            system("cls");

        }
        break;

        case GameScenes::GAMEOVER:
        {
            system("cls");
            game.GameOver(cj, settings, m, w, b, c);
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