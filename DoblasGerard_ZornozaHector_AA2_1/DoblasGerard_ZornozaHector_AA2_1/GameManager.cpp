#include "GameManager.h"

void GameManager::gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
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

void GameManager::CloseConsole() {
    HWND hwnd = GetConsoleWindow();
    if (hwnd != NULL) {
        PostMessage(hwnd, WM_CLOSE, 0, 0);
    }
}