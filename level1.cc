#include "level1.h"
#include <string>
#include <cstdlib>

class Block;

Block *Level1::CreateNextBlock()
{
    Block *nextBlock;
    // set up the seed
    if (seedBool == true)
    {
        std::srand(seed);
    }
    // random is a random int from 1 to 12
    int random = 1 + std::rand() / ((RAND_MAX + 1u) / 12);
    // SBlock and ZBlock has probability of 1/12
    if (random == 1)
    {
        nextBlock = Level::CreateBlock(1, 'S');
    }
    else if (random == 2)
    {
        nextBlock = Level::CreateBlock(1, 'Z');
    }
    // other blocks has probability of 1/6
    else if (random == 3 || random == 4)
    {
        nextBlock = Level::CreateBlock(1, 'I');
    }
    else if (random == 5 || random == 6)
    {
        nextBlock = Level::CreateBlock(1, 'J');
    }
    else if (random == 7 || random == 8)
    {
        nextBlock = Level::CreateBlock(1, 'T');
    }
    else if (random == 9 || random == 10)
    {
        nextBlock = Level::CreateBlock(1, 'O');
    }
    else if (random == 11 || random == 12)
    {
        nextBlock = Level::CreateBlock(1, 'L');
    }
    return nextBlock;
}

Level1::~Level1() {}
