#include "Car.h"

void Cars::CarsManagment(Map& map, Settings& settings)
{
    CarInSantos = 0;
    for (int i = 0; i < settings.ROWS; ++i) {
        for (int j = 0; j < settings.COLUMNS / 3; ++j) {
            if (map.box[i][j] == Boxes::COCHE) {
                CarInSantos++;
            }
        }
    }

    if (CarInSantos < settings.SANTOS_CAR) {
        newCarX, newCarY;
        do {
            newCarX = rand() % (settings.COLUMNS / 3 - 1) + 1;
            newCarY = rand() % (settings.ROWS - 1) + 1;
        } while (map.box[newCarY][newCarX] != Boxes::VACIO);

        map.box[newCarY][newCarX] = Boxes::COCHE;
    }

    CarInFierro = 0;
    for (int i = 0; i < settings.ROWS; ++i) {
        for (int j = settings.COLUMNS / 3; j < settings.COLUMNS / 3 * 2; ++j) {
            if (map.box[i][j] == Boxes::COCHE) {
                CarInFierro++;
            }
        }
    }

    if (CarInFierro < settings.FIERRO_CAR) {
        newCarX, newCarY;
        do {
            newCarX = rand() % (settings.COLUMNS / 3 - 1) + settings.COLUMNS / 3 - 1;
            newCarY = rand() % (settings.ROWS - 1) + 1;
        } while (map.box[newCarY][newCarX] != Boxes::VACIO);

        map.box[newCarY][newCarX] = Boxes::COCHE;
    }
}
void Cars::GetCar(int posX, int posY, Map& map, CJ& cj)
{
    int Cars = 0;
    if (map.box[posY - 1][posX] == Boxes::COCHE) Cars++;
    else if (map.box[posY + 1][posX] == Boxes::COCHE) Cars++;
    else if (map.box[posY][posX - 1] == Boxes::COCHE) Cars++;
    else if (map.box[posY][posX + 1] == Boxes::COCHE) Cars++;
    else if (Cars == 0) return;

    int randomCar = rand() % Cars;
    int contador = 0;

    if (map.box[posY - 1][posX] == Boxes::COCHE) {
        if (contador == randomCar) {
            map.box[posY - 1][posX] = Boxes::VACIO;
            cj.pos.y -= 1;
            cj.driving = CJDrive::CAR;
            cj.CJLook = 'C';
            return;
        }
        contador++;
    }
    if (map.box[posY + 1][posX] == Boxes::COCHE) {
        if (contador == randomCar) {
            map.box[posY + 1][posX] = Boxes::VACIO;
            cj.pos.y += 1;
            cj.driving = CJDrive::CAR;
            cj.CJLook = 'C';
            return;
        }
        contador++;
    }
    if (map.box[posY][posX - 1] == Boxes::COCHE) {
        if (contador == randomCar) {
            map.box[posY][posX - 1] = Boxes::VACIO;
            cj.pos.x -= 1;
            cj.driving = CJDrive::CAR;
            cj.CJLook = 'C';
            return;
        }
        contador++;
    }
    if (map.box[posY][posX + 1] == Boxes::COCHE) {
        if (contador == randomCar) {
            map.box[posY][posX + 1] = Boxes::VACIO;
            cj.pos.x += 1;
            cj.driving = CJDrive::CAR;
            cj.CJLook = 'C';
            return;
        }
    }
}

void Cars::OutCar(Map& map, CJ& cj) {
    if (map.box[cj.pos.y - 1][cj.pos.x] == Boxes::VACIO) {
        map.box[cj.pos.y][cj.pos.x] = Boxes::COCHE;
        cj.prevPos = cj.pos;
        cj.pos.y -= 1;
    }
    else if (map.box[cj.pos.y + 1][cj.pos.x] == Boxes::VACIO) {
        map.box[cj.pos.y][cj.pos.x] = Boxes::COCHE;
        cj.prevPos = cj.pos;
        cj.pos.y += 1;
    }
    else if (map.box[cj.pos.y][cj.pos.x + 1] == Boxes::VACIO) {
        map.box[cj.pos.y][cj.pos.x] = Boxes::COCHE;
        cj.prevPos = cj.pos;
        cj.pos.x += 1;
    }
    else if (map.box[cj.pos.y][cj.pos.x - 1] == Boxes::VACIO) {
        map.box[cj.pos.y][cj.pos.x] = Boxes::COCHE;
        cj.prevPos = cj.pos;
        cj.pos.x -= 1;
    }
    else {
        return;
    }

    cj.driving = CJDrive::WALK;
    cj.CJLook = '^';
}

