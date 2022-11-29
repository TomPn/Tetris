#include "level2.h"
#include <string>
#include <cstdlib>

class Block;

Block *Level2::CreateNextBlock()
{
    Block *nextBlock;
    // set up the seed
    if (seedBool == true)
    {
        std::srand(seed);
    }
    // random is a random int from 1 to 7
    int random = 1 + std::rand() / ((RAND_MAX + 1u) / 7);
    if (random == 1)
    {
        nextBlock = Level::CreateBlock(2, 'S');
    }
    else if (random == 2)
    {
        nextBlock = Level::CreateBlock(2, 'Z');
    }
    else if (random == 3)
    {
        nextBlock = Level::CreateBlock(2, 'I');
    }
    else if (random == 4)
    {
        nextBlock = Level::CreateBlock(2, 'J');
    }
    else if (random == 5)
    {
        nextBlock = Level::CreateBlock(2, 'T');
    }
    else if (random == 6)
    {
        nextBlock = Level::CreateBlock(2, 'O');
    }
    else if (random == 7)
    {
        nextBlock = Level::CreateBlock(2, 'L');
    }
    return nextBlock;
}

Level2::~Level2() {}
