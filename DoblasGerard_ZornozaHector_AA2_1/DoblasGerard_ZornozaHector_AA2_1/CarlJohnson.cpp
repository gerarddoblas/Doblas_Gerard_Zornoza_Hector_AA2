#include "CarlJohnson.h"


CJ::CJ() {
    money = 0;
    pos.x = this->prevPos.x = 11;
    pos.y = this->prevPos.y = 37;
    CJLook = '^';
    currentMove = CJMovement::NONE;
}

void CJ::SetCJPos(int mapBorderX, int mapBorderY) {
    prevPos = pos;
    switch (currentMove) {
    case CJMovement::UP: {
        CJLook = '^';
        if (pos.y - 1 <= 0) {
            currentMove = CJMovement::NONE;
            return;
        }
        pos.y--;
    } break;
    case CJMovement::DOWN: {
        CJLook = 'v';
        if (pos.y + 1 > mapBorderY - 2) {
            currentMove = CJMovement::NONE;
            return;
        }
        pos.y++;
    } break;
    case CJMovement::LEFT: {
        CJLook = '<';
        if (pos.x - 1 <= 0) {
            currentMove = CJMovement::NONE;
            return;
        }
        pos.x--;
    } break;
    case CJMovement::RIGHT: {
        CJLook = '>';
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

void CJ::MoveCJ(int mapBorderX, int mapBorderY, Map& map, Pedestrians& pedestrians) {
    if (GetAsyncKeyState(VK_SPACE))
        pedestrians.PedestrianHunting();
    else if (GetAsyncKeyState(VK_ESCAPE));
    else if (GetAsyncKeyState(VK_UP) && (map.box[pos.y - 1][pos.x] != Boxes::PEATÓN))
        currentMove = CJMovement::UP;
    else if (GetAsyncKeyState(VK_DOWN) && (map.box[pos.y + 1][pos.x] != Boxes::PEATÓN))
        currentMove = CJMovement::DOWN;
    else if (GetAsyncKeyState(VK_LEFT) && (map.box[pos.y][pos.x - 1] != Boxes::PEATÓN))
        currentMove = CJMovement::LEFT;
    else if (GetAsyncKeyState(VK_RIGHT) && (map.box[pos.y][pos.x + 1] != Boxes::PEATÓN))
        currentMove = CJMovement::RIGHT;

    SetCJPos(mapBorderX, mapBorderY);
}




