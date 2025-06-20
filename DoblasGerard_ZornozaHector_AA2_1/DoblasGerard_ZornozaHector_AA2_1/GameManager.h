#pragma once
#include "Map.h"
const int MAX_NUM_FPS = 15;

enum class GameScenes {
    MAIN_MENU,
    SPLASH_SCREEN,
    GAMEPLAY,
    GAMEOVER
};

class GameManager
{
private:
    int x;
    int y;
    GameScenes currentScene;
public:
    void gotoxy(int x, int y);
    void ShowMainMenu(GameScenes& currentScene);
    void CloseConsole();
};