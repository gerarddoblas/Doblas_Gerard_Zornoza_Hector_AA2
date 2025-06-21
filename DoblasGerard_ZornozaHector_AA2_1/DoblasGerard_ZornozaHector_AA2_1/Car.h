#pragma once
#include "FileReader.h"
#include "Map.h"
#include "Player.h"

class Map;
class CJ;
class Cars {
public:

    void CarsManagment(Map& map, const Settings& settings);
    void GetCar(int posX, int posY, Map& map, CJ& cj);
    void OutCar(Map& map, CJ& cj);

private:

    int CarInSantos;
    int CarInFierro;
    int newCarX;
    int newCarY;

};

