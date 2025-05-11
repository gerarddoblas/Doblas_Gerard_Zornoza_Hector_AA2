#include "FileReader.h"

bool FileReader::ReadSettings(const string& filename, Settings& settings) 
{
	fstream myFile(filename);
    if (!myFile.is_open()) {
        CheckFiles();
        exit(1);
    }

    char aux;
    myFile >> settings.ROWS >> aux >> settings.COLUMNS >> aux
        >> settings.SANTOS_PEDESTRIANS_NUMBER >> aux >> settings.SANTOS_MONEY_REQUIRED >> aux >> settings.SANTOS_MAX_MONEY >> aux
        >> settings.FIERRO_PEDESTRIANS_NUMBER >> aux >> settings.FIERRO_MONEY_REQUIRED >> aux >> settings.FIERRO_MAX_MONEY >> aux;

    myFile.close();
    return true;
}

void FileReader::CheckFiles() {
    std::cout << "Lamentablemente, ha surgido un inconveniente al intentar abrir el archivo 'config.txt'.\n"
        << "Por favor, tómese un momento para verificar que el archivo exista y contenga los datos necesarios.\n"
        << "Si el problema persiste, no dude en comunicarse con el administrador del sistema para recibir asistencia adicional.\n"
        << "¡Gracias por su comprensión y colaboración!\n";
}