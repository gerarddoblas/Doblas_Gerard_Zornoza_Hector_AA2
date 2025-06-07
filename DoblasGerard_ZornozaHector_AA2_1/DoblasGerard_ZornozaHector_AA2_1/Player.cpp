#include "Player.h"


CJ::CJ() {
    money = 0;
    pos.x = this->prevPos.x = 11;
    pos.y = this->prevPos.y = 37;
    CJLook = '^';
    currentMove = CJMovement::NONE;
    driving = CJDrive::WALK;
}

void CJ::SetCJPos(int mapBorderX, int mapBorderY) {
    prevPos = pos;
    switch (currentMove) {
    case CJMovement::UP: {
        CJLook = '^';
        if (driving == CJDrive::CAR)
            CJLook = 'C';
        if (pos.y - 1 <= 0) {
            currentMove = CJMovement::NONE;
            return;
        }
        pos.y--;
    } break;
    case CJMovement::DOWN: {
        CJLook = 'v';
        if (driving == CJDrive::CAR)
            CJLook = 'C';
        if (pos.y + 1 > mapBorderY - 2) {
            currentMove = CJMovement::NONE;
            return;
        }
        pos.y++;
    } break;
    case CJMovement::LEFT: {
        CJLook = '<';
        if (driving == CJDrive::CAR)
            CJLook = 'C';
        if (pos.x - 1 <= 0) {
            currentMove = CJMovement::NONE;
            return;
        }
        pos.x--;
    } break;
    case CJMovement::RIGHT: {
        CJLook = '>';
        if (driving == CJDrive::CAR)
            CJLook = 'C';
        if (pos.x + 1 > mapBorderX - 2) {
            currentMove = CJMovement::NONE;
            return;
        }
        pos.x++;
    } break;
    default:
        break;
    }
    currentMove = CJMovement::NONE;
}

void CJ::GetMoney(Map& map, Settings& settings)
{
    if (pos.x < settings.COLUMNS / 3 && map.box[pos.y][pos.x] == Boxes::DINERO)
    {
        money = money + rand() % (settings.SANTOS_MAX_MONEY) + 1;
    }
    else if (pos.x < settings.COLUMNS / 3 * 2 && map.box[pos.y][pos.x] == Boxes::DINERO)
    {
        money = money + rand() % (settings.FIERRO_MAX_MONEY) + 1;
    }
}

void CJ::WalkersMoneyCars(Map& map, Settings& settings)
{
    if (map.box[pos.y][pos.x] == Boxes::PEATÓN)
    {
        for (int i = 0; i < 4; ++i)
        {
            int x = pos.x;
            int y = pos.y;
            switch (i)
            {
            case 0:
                y = pos.y - 1;
                break;
            case 1:
                y = pos.y + 1;
                break;
            case 2:
                x = pos.x - 1;
                break;
            case 3:
                x = pos.x + 1;
                break;
            }

            if (x >= 0 && x < settings.COLUMNS && y >= 0 && y < settings.ROWS)
            {
                if (map.box[y][x] == Boxes::VACIO)
                {
                    map.box[y][x] = Boxes::DINERO;
                    break;
                }
            }
        }
    }
}

void CJ::MoveCJ(int mapBorderX, int mapBorderY, Map& map, Walkers& pedestrians, Settings& settings, Cars& cars) {
    if (driving == CJDrive::WALK)
    {
        if (GetAsyncKeyState(VK_E) & 0x8000)
        {
            map.box[prevPos.y][prevPos.x] = Boxes::VACIO;
            prevPos = pos;
            cars.GetCar(pos.x, pos.y, map, *this);
        }
        else if (GetAsyncKeyState(VK_SPACE))
            pedestrians.WalkerHunting(pos.x, pos.y, map, settings);
        else if (GetAsyncKeyState(VK_ESCAPE));
        else if (GetAsyncKeyState(VK_UP) && (map.box[pos.y - 1][pos.x] != Boxes::PEATÓN) && (map.box[pos.y - 1][pos.x] != Boxes::COCHE))
            currentMove = CJMovement::UP;
        else if (GetAsyncKeyState(VK_DOWN) && (map.box[pos.y + 1][pos.x] != Boxes::PEATÓN) && (map.box[pos.y + 1][pos.x] != Boxes::COCHE))
            currentMove = CJMovement::DOWN;
        else if (GetAsyncKeyState(VK_LEFT) && (map.box[pos.y][pos.x - 1] != Boxes::PEATÓN) && (map.box[pos.y][pos.x - 1] != Boxes::COCHE))
            currentMove = CJMovement::LEFT;
        else if (GetAsyncKeyState(VK_RIGHT) && (map.box[pos.y][pos.x + 1] != Boxes::PEATÓN) && (map.box[pos.y][pos.x + 1] != Boxes::COCHE))
            currentMove = CJMovement::RIGHT;
    }
    else
    {
        if (GetAsyncKeyState(VK_E) & 0x8000)
        {
            map.box[prevPos.y][prevPos.x] = Boxes::VACIO;
            prevPos = pos;
            cars.OutCar(map, *this);
        }
        else if (GetAsyncKeyState(VK_ESCAPE));
        else if (GetAsyncKeyState(VK_UP) && (map.box[pos.y - 1][pos.x] != Boxes::DINERO))
            currentMove = CJMovement::UP;
        else if (GetAsyncKeyState(VK_DOWN) && (map.box[pos.y + 1][pos.x] != Boxes::DINERO))
            currentMove = CJMovement::DOWN;
        else if (GetAsyncKeyState(VK_LEFT) && (map.box[pos.y][pos.x - 1] != Boxes::DINERO))
            currentMove = CJMovement::LEFT;
        else if (GetAsyncKeyState(VK_RIGHT) && (map.box[pos.y][pos.x + 1] != Boxes::DINERO))
            currentMove = CJMovement::RIGHT;
    }


    SetCJPos(mapBorderX, mapBorderY);
    WalkersMoneyCars(map, settings);
    GetMoney(map, settings);
}
