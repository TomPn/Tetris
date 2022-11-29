#include <fstream>
#include "level0.h"
#include <string>

class Block;

Level0::Level0(std::string L0File, bool noRandomBool, std::string noRandomFile, bool seedBool, unsigned int seed, std::vector<std::vector<Cell *>> cells)
    : Level{L0File, noRandomFile, noRandomBool, seedBool, seed, cells}
{

    L0FileContent = Level::readFile(L0File);
}

Block *Level0::CreateNextBlock()
{
    // if the index exceeds the length of content, set the index to 0 so that the program will read it again from the beginning
    if (L0FileIndex == L0FileContent.size())
    {
        L0FileIndex = 0;
    }
    Block *nextBlock = Level::CreateNextFromFile(L0FileContent, L0FileIndex);
    // increment index
    ++L0FileIndex;
    return nextBlock;
}

Level0::~Level0() {}