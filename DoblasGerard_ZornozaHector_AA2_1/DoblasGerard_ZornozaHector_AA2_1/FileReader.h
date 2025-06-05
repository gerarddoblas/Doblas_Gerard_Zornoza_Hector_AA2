#pragma once
#include <iostream>
#include <fstream>

using namespace std;
struct Settings
{
public:
	int ROWS;
	int COLUMNS;
	int PLAYER_HP;
	int PLAYER_DM;
	int SANTOS_MONEY_REQUIRED;
	int FIERRO_MONEY_REQUIRED;
	int SANTOS_PEDESTRIANS_NUMBER;
	int SANTOS_MAX_MONEY;
	int SANTOS_HP;
	int SANTOS_DM;
	int SANTOS_CAR;
	int FIERRO_PEDESTRIANS_NUMBER;
	int FIERRO_MAX_MONEY;
	int FIERRO_HP;
	int FIERRO_DM;
	int FIERRO_CAR;
	int VENTURAS_PEDESTRIANS_NUMBER;
	int VENTURAS_MAX_MONEY;
	int VENTURAS_HP;
	int VENTURAS_DM;
	int VENTURAS_CAR;
};

class FileReader
{
public:
	bool ReadSettings(const string& filename, Settings& settings);
private:
	void CheckFiles();
};

