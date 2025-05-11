#pragma once
#include "FileReader.h"
#include "Map.h"
#include <ctime>
#include <chrono>

class Map;

class Pedestrians {
public:

    void PedestrianManagment(int cJX, int cJY, Map& map,Settings& settings);
    void PedestrianHunting(int posX, int posY, Map& map);

private:

    int pedestriansInSantos;
    int pedestriansInFierro;
    int newPedestrianX;
    int newPedestrianY;

    int minTime;
    int maxTime;
    int waitTime;

    chrono::time_point<chrono::system_clock> now;
    chrono::duration<double> elapsed_seconds;
    chrono::time_point<chrono::system_clock> lastMoveTime;

    void PedestrianMove(int cJX, int cJY, Map& map, Settings& settings);
    bool PedestrianStop(int cJX, int cJY, int pedestrianX, int pedestrianY);
};

