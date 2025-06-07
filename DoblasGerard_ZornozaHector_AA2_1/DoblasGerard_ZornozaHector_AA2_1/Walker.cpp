#include "Walker.h"

void Walkers::WalkerManagment(int cJX, int cJY, Map& map, Settings& settings)
{
    WalkersInSantos = 0;
    for (int i = 0; i < settings.ROWS; ++i) {
        for (int j = 0; j < settings.COLUMNS / 3; ++j) {
            if (map.box[i][j] == Boxes::PEATÓN) {
                WalkersInSantos++;
            }
        }
    }

    if (WalkersInSantos < settings.SANTOS_PEDESTRIANS_NUMBER) {
        newWalkerX, newWalkerY;
        do {
            newWalkerX = rand() % (settings.COLUMNS / 3 - 1) + 1;
            newWalkerY = rand() % (settings.ROWS - 1) + 1;
        } while (map.box[newWalkerY][newWalkerX] != Boxes::VACIO);

        map.box[newWalkerY][newWalkerX] = Boxes::PEATÓN;
    }

    WalkersInFierro = 0;
    for (int i = 0; i < settings.ROWS; ++i) {
        for (int j = settings.COLUMNS / 3; j < settings.COLUMNS / 3 * 2; ++j) {
            if (map.box[i][j] == Boxes::PEATÓN) {
                WalkersInFierro++;
            }
        }
    }

    if (WalkersInFierro < settings.FIERRO_PEDESTRIANS_NUMBER) {
        newWalkerX, newWalkerY;
        do {
            newWalkerX = rand() % (settings.COLUMNS / 3 - 1) + settings.COLUMNS / 3 - 1;
            newWalkerY = rand() % (settings.ROWS - 1) + 1;
        } while (map.box[newWalkerY][newWalkerX] != Boxes::VACIO);

        map.box[newWalkerY][newWalkerX] = Boxes::PEATÓN;
    }
    WalkerMove(cJX, cJY, map, settings);
}

void Walkers::WalkerMove(int cJX, int cJY, Map& map, Settings& settings)
{
    auto now = chrono::system_clock::now();
    chrono::duration<double> elapsed_seconds = now - lastMoveTime;

    int minTime = 2;
    int maxTime = 5;
    int waitTime = rand() % (maxTime - minTime + 1) + minTime;

    if (elapsed_seconds.count() >= waitTime) {
        for (int i = 0; i < settings.ROWS; ++i) {
            for (int j = 0; j < settings.COLUMNS; ++j) {
                if (map.box[i][j] == Boxes::PEATÓN) {

                    if (WalkerStop(cJX, cJY, j, i)) continue;
                    int direction = rand() % 4;
                    int newX = j, newY = i;

                    switch (direction) {
                    case 0:
                        newY -= 1;
                        break;
                    case 1:
                        newY += 1;
                        break;
                    case 2:
                        newX -= 1;
                        break;
                    case 3:
                        newX += 1;
                        break;
                    }

                    int santosZone = (j / (settings.COLUMNS / 3)) * settings.COLUMNS / 3;
                    int fierroZone = santosZone + (settings.COLUMNS / 3);

                    if (newX >= santosZone && newX < fierroZone && newY >= 0 && newY < settings.ROWS && map.box[newY][newX] == Boxes::VACIO) {

                        map.box[newY][newX] = Boxes::PEATÓN;
                        map.box[i][j] = Boxes::VACIO;
                    }
                }
            }
        }
        lastMoveTime = chrono::system_clock::now();
    }
}

void Walkers::WalkerFound(int posX, int posY, Map& map)
{
    if (GetAsyncKeyState(VK_SPACE) && map.box[posY - 1][posX] == Boxes::PEATÓN)
        map.box[posY - 1][posX] = Boxes::DINERO;
    else if (GetAsyncKeyState(VK_SPACE) && map.box[posY + 1][posX] == Boxes::PEATÓN)
        map.box[posY + 1][posX] = Boxes::DINERO;
    else if (GetAsyncKeyState(VK_SPACE) && map.box[posY][posX + 1] == Boxes::PEATÓN)
        map.box[posY][posX + 1] = Boxes::DINERO;
    else if (GetAsyncKeyState(VK_SPACE) && map.box[posY][posX - 1] == Boxes::PEATÓN)
        map.box[posY][posX - 1] = Boxes::DINERO;

}

void Walkers::WalkerHunting(int pedestrianX, int pedestrianY, Map& map, Settings& settings)
{
    if (map.box[pedestrianY - 1][pedestrianX] == Boxes::PEATÓN || map.box[pedestrianY][pedestrianX + 1] == Boxes::PEATÓN ||
        map.box[pedestrianY + 1][pedestrianX] == Boxes::PEATÓN || map.box[pedestrianY][pedestrianX - 1] == Boxes::PEATÓN)
    {
        if (map.pedestrianHealth[pedestrianY][pedestrianX] == 0)
        {
            if (pedestrianX < settings.COLUMNS / 3)
                map.pedestrianHealth[pedestrianY][pedestrianX] = settings.SANTOS_HP;
            else if (pedestrianX < (settings.COLUMNS / 3) * 2)
                map.pedestrianHealth[pedestrianY][pedestrianX] = settings.FIERRO_HP;
            else
                map.pedestrianHealth[pedestrianY][pedestrianX] = settings.VENTURAS_HP;
        }

        map.pedestrianHealth[pedestrianY][pedestrianX] -= settings.PLAYER_DM;

        if (map.pedestrianHealth[pedestrianY][pedestrianX] <= 0)
        {
            if (map.box[pedestrianY - 1][pedestrianX] == Boxes::PEATÓN)
            {
                map.box[pedestrianY - 1][pedestrianX] = Boxes::DINERO;
            }
            else if (map.box[pedestrianY][pedestrianX + 1] == Boxes::PEATÓN)
            {
                map.box[pedestrianY][pedestrianX + 1] = Boxes::DINERO;
            }
            else if (map.box[pedestrianY + 1][pedestrianX] == Boxes::PEATÓN)
            {
                map.box[pedestrianY + 1][pedestrianX] = Boxes::DINERO;
            }
            else if (map.box[pedestrianY][pedestrianX - 1] == Boxes::PEATÓN)
            {
                map.box[pedestrianY][pedestrianX - 1] = Boxes::DINERO;
            }
            map.pedestrianHealth[pedestrianY][pedestrianX] = 0;
        }
    }
}


void Walkers::WalkerAttack(int cJX, int cJY, Map& map, Settings& settings, int& playerHealth)
{
    auto now = chrono::system_clock::now();
    chrono::duration<double> elapsed_seconds = now - lastAttackTime;

    if (elapsed_seconds.count() >= 1.0) {

        auto applyDamage = [&](int x, int y) {
            if (map.box[y][x] == Boxes::PEATÓN) {

                int damage = 0;

                if (x < settings.COLUMNS / 3)
                    damage = settings.SANTOS_DM;
                else if (x < 2 * settings.COLUMNS / 3)
                    damage = settings.FIERRO_DM;
                else
                    damage = settings.VENTURAS_DM;

                playerHealth -= damage;
            }
            };

        if (cJY > 0) applyDamage(cJX, cJY - 1);
        if (cJY < settings.ROWS - 1) applyDamage(cJX, cJY + 1);
        if (cJX > 0) applyDamage(cJX - 1, cJY);
        if (cJX < settings.COLUMNS - 1) applyDamage(cJX + 1, cJY);

        lastAttackTime = now;
    }
}

bool Walkers::WalkerStop(int cJX, int cJY, int pedestrianX, int pedestrianY)
{
    return abs(cJX - pedestrianX) + abs(cJY - pedestrianY) == 1;
}
