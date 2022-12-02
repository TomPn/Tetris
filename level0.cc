#include "level0.h"
#include "block.h"
#include <fstream>
#include <string>
#include <iostream>
using std::cout;
using std::endl;


void Level0::setL0File(std::string L0File)
{
    this->L0File = L0File;
    L0FileContent = Level::readFile(L0File);
}

void Level0::setNoRandom(bool noRandom, std::string noRandomFile) {}

std::unique_ptr<Block> Level0::CreateNextBlock()
{
    // if the index exceeds the length of content, set the index to 0 so that the program will read it again from the beginning
    int fileSize = L0FileContent.size();
    if (L0FileIndex == fileSize)
    {
        L0FileIndex = 0;
    }
    auto nextBlock = Level::CreateNextFromFile(L0FileContent, L0FileIndex);
    // increment index
    ++L0FileIndex;
    return nextBlock;
}

Level0::~Level0() {}
