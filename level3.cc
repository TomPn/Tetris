#include "level3.h"
#include <string>
#include <cstdlib>

class Block;

Level3::Level3(std::string L0File, bool noRandomBool, std::string noRandomFile, bool seedBool, unsigned int seed, std::vector<std::vector<Cell *>> cells)
    : Level{L0File, noRandomFile, noRandomBool, seedBool, seed, cells}
{
    // if fileName isn't empty, call readFile to read the strings in the file and store them in a vector of string
    if (noRandomFile != "")
    {
        noRandomFileContent = Level::readFile(noRandomFile);
    }
}

Block *Level3::CreateNextBlock()
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
                nextBlock = Level::CreateBlock(3, 'S');
                break;
            case 3:
            case 4:
                nextBlock = Level::CreateBlock(3, 'Z');
                break;
            // other blocks have probability of 1/9
            case 5:
                nextBlock = Level::CreateBlock(3, 'I');
                break;
            case 6:
                nextBlock = Level::CreateBlock(3, 'J');
                break;
            case 7:
                nextBlock = Level::CreateBlock(3, 'T');
                break;
            case 8:
                nextBlock = Level::CreateBlock(3, 'O');
                break;
            case 9:
                nextBlock = Level::CreateBlock(3, 'L');
                break;
        } // switch

        // // random is a random int from 1 to 18
        // int random = 1 + std::rand() / ((RAND_MAX + 1u) / 18);
        // // SBlock and ZBlock has probability of 2/9 = 4/18
        // if (random >= 1 && random <= 4)
        // {
        //     nextBlock = Level::CreateBlock(3, 'S');
        // }
        // else if (random >= 5 && random <= 8)
        // {
        //     nextBlock = Level::CreateBlock(3, 'Z');
        // }
        // // other blocks has probability of 1/6
        // else if (random == 9 || random == 10)
        // {
        //     nextBlock = Level::CreateBlock(3, 'I');
        // }
        // else if (random == 11 || random == 12)
        // {
        //     nextBlock = Level::CreateBlock(3, 'J');
        // }
        // else if (random == 13 || random == 14)
        // {
        //     nextBlock = Level::CreateBlock(3, 'T');
        // }
        // else if (random == 15 || random == 16)
        // {
        //     nextBlock = Level::CreateBlock(3, 'O');
        // }
        // else if (random == 17 || random == 18)
        // {
        //     nextBlock = Level::CreateBlock(3, 'L');
        // }
    }

    return nextBlock;
}

Level3::~Level3() {}
