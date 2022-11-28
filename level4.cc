#include "level4.h"
#include <string>
#include <cstdlib>

class Block;

Level4::Level4(std::string L0File, bool noRandomBool, std::string noRandomFile, bool seedBool, unsigned int seed, std::vector<std::vector<Cell *>> cells)
    : Level{L0File, noRandomFile, noRandomBool, seedBool, seed, cells}
{
    // if fileName isn't empty, call readFile to read the chars in the file and store them in a vector of char
    if (noRandomFile != "")
    {
        noRandomFileContent = Level::readFile(noRandomFile);
    }
}

Block *Level4::CreateNextBlock()
{
    Block *nextBlock;
    if (noRandomBool)
    {
        if (noRandomFileIndex == noRandomFileContent.size()) noRandomFileIndex = 0;
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
        
        switch ( random ) {
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
