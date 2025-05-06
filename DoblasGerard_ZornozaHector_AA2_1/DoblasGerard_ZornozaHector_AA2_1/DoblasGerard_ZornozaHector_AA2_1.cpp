#include "FileReader.h"

int main()
{
    FileReader file;
    Settings settings;
    file.ReadSettings("config.txt", settings);
}
