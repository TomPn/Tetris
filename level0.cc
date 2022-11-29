#include <fstream>
#include "level0.h"
#include <string>

class Block;

void Level0::setL0File(std::string L0File = "")
{
    this->L0File = L0File;
    L0FileContent = Level::readFile(L0File);
}

void Level0::setNoRandom(bool noRandom, std::string noRandomFile = "") {}

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
