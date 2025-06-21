#include "Walker.h"

Walkers::Walkers(Settings& settings)
{

    healthSantos = settings.SANTOS_HP;
    healthFierro = settings.FIERRO_HP;
    healthVenturas = settings.VENTURAS_HP;
}

Walkers::~Walkers() {}

void Walkers::WalkerManagment(int cJX, int cJY, Map& map, const Settings& settings)
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

    WalkersInVenturas = 0;
    for (int i = 0; i < settings.ROWS; ++i) {
        for (int j = settings.COLUMNS / 3 * 2; j < settings.COLUMNS; ++j) {
            if (map.box[i][j] == Boxes::PEATÓN) {
                WalkersInVenturas++;
            }
        }
    }

    if (WalkersInVenturas < settings.VENTURAS_PEDESTRIANS_NUMBER) {
        newWalkerX, newWalkerY;
        do {
            newWalkerX = rand() % (settings.COLUMNS / 3 - 1) + ((settings.COLUMNS / 3) * 2) - 1;
            newWalkerY = rand() % (settings.ROWS - 1) + 1;
        } while (map.box[newWalkerY][newWalkerX] != Boxes::VACIO);

        map.box[newWalkerY][newWalkerX] = Boxes::PEATÓN;
    }

    WalkerMove(cJX, cJY, map, settings);
}

void Walkers::WalkerMove(int cJX, int cJY, Map& map, const Settings& settings)
{
    constexpr double frameLimit = 1000.0 / 4.0 / 1000.0;
    auto now = chrono::system_clock::now();
    chrono::duration<double> elapsed_seconds = now - lastMoveTime;

    if (elapsed_seconds.count() >= frameLimit) {
        lastMoveTime = now;

        for (int i = 0; i < settings.ROWS; ++i) {
            for (int j = 0; j < settings.COLUMNS; ++j) {
                if (map.box[i][j] == Boxes::PEATÓN) {

                    if (WalkerStop(cJX, cJY, j, i)) continue;
                    int direction = rand() % 4;
                    int newX = j, newY = i;

                    switch (direction) {
                    case 0: newY -= 1; break;
                    case 1: newY += 1; break;
                    case 2: newX -= 1; break;
                    case 3: newX += 1; break;
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
    }

}

bool Walkers::WalkerFound(int posX, int posY, Map& map)
{
    if (map.box[posY - 1][posX] == Boxes::PEATÓN)
        return true;
    else if (map.box[posY + 1][posX] == Boxes::PEATÓN)
        return true;
    else if (map.box[posY][posX + 1] == Boxes::PEATÓN)
        return true;
    else if (map.box[posY][posX - 1] == Boxes::PEATÓN)
        return true;
    else
        return false;
}

void Walkers::WalkerReward(int posX, int posY, Map& map)
{
    if (map.box[posY - 1][posX] == Boxes::PEATÓN)
        map.box[posY - 1][posX] = Boxes::DINERO;
    else if (map.box[posY + 1][posX] == Boxes::PEATÓN)
        map.box[posY + 1][posX] = Boxes::DINERO;
    else if (map.box[posY][posX + 1] == Boxes::PEATÓN)
        map.box[posY][posX + 1] = Boxes::DINERO;
    else if (map.box[posY][posX - 1] == Boxes::PEATÓN)
        map.box[posY][posX - 1] = Boxes::DINERO;
}

void Walkers::WalkerAttack(int posX, int posY, int& CJ_HP, Map& map, const Settings& settings)
{
    if (WalkerFound(posX, posY, map))
    {
        now = chrono::system_clock::now();
        elapsed_seconds = now - lastAttackTime;

        if (elapsed_seconds.count() >= 1.0 && posX < settings.COLUMNS / 3)
        {
            lastAttackTime = now;
            CJ_HP = CJ_HP - settings.SANTOS_DM;
        }
        else if (elapsed_seconds.count() >= 1.0 && posX < (settings.COLUMNS / 3) * 2)
        {
            lastAttackTime = now;
            CJ_HP = CJ_HP - settings.FIERRO_DM;
        }
        else if (elapsed_seconds.count() >= 1.0 && posX > (settings.COLUMNS / 3) * 2)
        {
            lastAttackTime = now;
            CJ_HP = CJ_HP - settings.VENTURAS_DM;
        }
    }
}

bool Walkers::WalkerStop(int cJX, int cJY, int pedestrianX, int pedestrianY)
{
    return abs(cJX - pedestrianX) + abs(cJY - pedestrianY) == 1;
}