#pragma once
#include <iostream>
#include <fstream>

using namespace std;
struct Settings
{
public:
	int ROWS;
	int COLUMNS;
	int SANTOS_PEDESTRIANS_NUMBER;
	int SANTOS_MONEY_REQUIRED;
	int SANTOS_MAX_MONEY;
	int FIERRO_PEDESTRIANS_NUMBER;
	int FIERRO_MONEY_REQUIRED;
	int FIERRO_MAX_MONEY;
};

class FileReader
{
public:
	bool ReadSettings(const string& filename, Settings& settings);
private:
	void CheckFiles();
};