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
    void ShowMainMenu(GameScenes& currentScene);
    void PrintZone(int posX, const Settings& settings);
    void SplashScreen();
    void Game(CJ& cj, Map& m, Settings& settings, Walkers& w, Boss& b, Cars& c);
    void GameOver(CJ& cj, Settings& settings, Map& m, Walkers& w, Boss& b, Cars& c);
};