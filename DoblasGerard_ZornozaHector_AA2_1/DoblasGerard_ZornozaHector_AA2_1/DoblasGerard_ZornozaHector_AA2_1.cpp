#include "FileReader.h"
#include "Map.h"

int main()
{
    FileReader file;
    Settings settings;
    file.ReadSettings("config.txt", settings);
    Mapa m(settings);
    m.PintarTodo();

}
