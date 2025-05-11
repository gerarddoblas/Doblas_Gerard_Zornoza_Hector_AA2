#include "Pedestrian.h"

void Pedestrians::PedestrianManagment(int cJX, int cJY, Map& map, Settings& settings)
{
    pedestriansInSantos = 0;
    for (int i = 0; i < settings.ROWS; ++i) {
        for (int j = 0; j < settings.COLUMNS / 3; ++j) {
            if (map.box[i][j] == Boxes::PEATÓN) {
                pedestriansInSantos++;
            }
        }
    }

    if (pedestriansInSantos < settings.SANTOS_PEDESTRIANS_NUMBER) {
        newPedestrianX, newPedestrianY;
        do {
            newPedestrianX = rand() % (settings.COLUMNS / 3 - 1) + 1;
            newPedestrianY = rand() % (settings.ROWS - 1) + 1;
        } while (map.box[newPedestrianY][newPedestrianX] != Boxes::VACIO);

        map.box[newPedestrianY][newPedestrianX] = Boxes::PEATÓN;
    }

    pedestriansInFierro = 0;
    for (int i = 0; i < settings.ROWS; ++i) {
        for (int j = settings.COLUMNS / 3; j < settings.COLUMNS / 3 * 2; ++j) {
            if (map.box[i][j] == Boxes::PEATÓN) {
                pedestriansInFierro++;
            }
        }
    }

    if (pedestriansInFierro < settings.FIERRO_PEDESTRIANS_NUMBER) {
        newPedestrianX, newPedestrianY;
        do {
            newPedestrianX = rand() % (settings.COLUMNS / 3 - 1) + settings.COLUMNS / 3 - 1;
            newPedestrianY = rand() % (settings.ROWS - 1) + 1;
        } while (map.box[newPedestrianY][newPedestrianX] != Boxes::VACIO);

        map.box[newPedestrianY][newPedestrianX] = Boxes::PEATÓN;
    }
    PedestrianMove(cJX, cJY, map, settings);
}

void Pedestrians::PedestrianMove(int cJX, int cJY, Map& map, Settings& settings)
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

                    if (PedestrianStop(cJX, cJY, j, i)) continue;
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
void Pedestrians::PedestrianHunting(int posX, int posY, Map& map )
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

bool Pedestrians::PedestrianStop(int cJX, int cJY,int pedestrianX, int pedestrianY)
{
    return abs(cJX - pedestrianX) + abs(cJY - pedestrianY) == 1;
}

