// Write array of unigned short byte to a file
// Author: David Sin
// setupModeScreen, MinerScreen, initScreen, globalHashScreen

#include "images.h"
#include <iostream>
#include <cstring>
#include <fstream>

const int size = 320*170;

void writeArrayToFile(const unsigned short *array, const char *filename)
{
    std::ofstream outfile;
    outfile.open(filename, std::ios::out | std::ios::binary);
    outfile.write(reinterpret_cast<const char*>(array), size * sizeof(unsigned short));
    outfile.close();
}

int main()
{
    writeArrayToFile(setupModeScreen, "setupModeScreen.bin");
    writeArrayToFile(MinerScreen, "MinerScreen.bin");
    writeArrayToFile(initScreen, "initScreen.bin");
    writeArrayToFile(minerClockScreen, "minerClockScreen.bin");
    writeArrayToFile(globalHashScreen, "globalHashScreen.bin");
    return 0;
}