#include "GameManager.h"

void GameManager::PrintZone(int posX, const Settings& settings)
{
    if (posX < settings.COLUMNS / 3)
    {
        std::cout << "   " << "---- SANTOS ----";
    }
    else if (posX < (settings.COLUMNS / 3) * 2)
    {
        std::cout << "   " << "---- FIERRO ----";
    }
    else if (posX > (settings.COLUMNS / 3) * 2)
    {
        std::cout << "   " << "---- VENTURAS ----";
    }
}


void GameManager::ShowMainMenu(GameScenes& currentScene)
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

void GameManager::SplashScreen()
{
    std::cout << "\033[38;5;208m";
    std::cout << R"(
   ____ _____  _      _____ _   _ _____ ___       ____ ___ _______   __
  / ___|_   _|/ \    | ____| \ | |_   _|_ _|     / ___|_ _|_   _\ \ / /
 | |  _  | | / _ \   |  _| |  \| | | |  | |_____| |    | |  | |  \ V / 
 | |_| | | |/ ___ \  | |___| |\  | | |  | |_____| |___ | |  | |   | |  
  \____| |_/_/   \_\ |_____|_| \_| |_| |___|     \____|___| |_|   |_|  
                                                                       
)";
    std::cout << "\033[0m";
    std::cout << R"()";
}

void GameManager::Game(CJ& cj, Map& m, Settings& settings, Walkers& w, Boss& b, Cars& c)
{
    if (cj.chance < 50 && cj.walkerHurt)
        w.WalkerAttack(cj.pos.x, cj.pos.y, cj.health, m, settings);
    if (b.BossFound(cj.pos.x, cj.pos.y, m) && cj.bossHurt)
    {
        b.BossAttack(cj.pos.x, cj.pos.y, m, settings, cj.health);
    }
    m.box[cj.prevPos.y][cj.prevPos.x] = static_cast<Boxes>(Boxes::VACIO);
    m.box[cj.pos.y][cj.pos.x] = static_cast<Boxes>(cj.CJLook);

    w.WalkerManagment(cj.pos.x, cj.pos.y, m, settings);
    c.CarsManagment(m, settings);
    //Aqui va la funcion management del boss


    m.PintarVista(cj.pos);
    std::cout << "---- Dinero: " << cj.money << " ----" << std::endl;
    std::cout << std::endl;
    std::cout << "---- HP:     " << cj.health << " ----" << std::endl;
    std::cout << std::endl;
    PrintZone(cj.pos.x, settings);
    
}

void GameManager::GameOver(CJ& cj, Settings& settings, Map& m, Walkers& w, Boss& b, Cars& c)
{
   
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
}