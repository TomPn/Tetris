#include "level4.h"
#include <string>
#include <cstdlib>

class Block;

void Level4::setL0File(std::string L0File) {}

// mutate randomBool
void Level4::setNoRandom(bool noRandom, std::string noRandomFile)
{
    noRandomBool = noRandom;
    if (noRandom == true)
    {
        this->noRandomFile = noRandomFile;
        noRandomFileContent = Level::readFile(noRandomFile);
        noRandomFileIndex = 0;
    }
}

Block *Level4::CreateNextBlock()
{
    Block *nextBlock;
    if (noRandomBool)
    {
        if (noRandomFileIndex == noRandomFileContent.size())
            noRandomFileIndex = 0;
        nextBlock = Level::CreateNextFromFile(noRandomFileContent, noRandomFileIndex);
        ++noRandomFileIndex;
    }
    else
    {
        // set up the seed
        if (seedBool == true)
        {
            std::srand(seed);
        }
        // random is a random int from 1 to 9
        int random = 1 + std::rand() / ((RAND_MAX + 1u) / 9);

        switch (random)
        {
        // SBlock and ZBlock has probability of 2/9
        case 1:
        case 2:
            nextBlock = Level::CreateBlock(4, 'S');
            break;
        case 3:
        case 4:
            nextBlock = Level::CreateBlock(4, 'Z');
            break;
        // other blocks have probability of 1/9
        case 5:
            nextBlock = Level::CreateBlock(4, 'I');
            break;
        case 6:
            nextBlock = Level::CreateBlock(4, 'J');
            break;
        case 7:
            nextBlock = Level::CreateBlock(4, 'T');
            break;
        case 8:
            nextBlock = Level::CreateBlock(4, 'O');
            break;
        case 9:
            nextBlock = Level::CreateBlock(4, 'L');
            break;
        } // switch
    }

    return nextBlock;
}

Level4::~Level4() {}
