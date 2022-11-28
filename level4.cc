#include "level4.h"
#include <string>
#include <cstdlib>

class Block;

Block *Level4::CreateNextBlock()
{
    Block *nextBlock;
    // set up the seed
    if (seedBool == true)
    {
        std::srand(seed);
    }
    // random is a random int from 1 to 18
    int random = 1 + std::rand() / ((RAND_MAX + 1u) / 18);
    // SBlock and ZBlock has probability of 2/9 = 4/18
    if (random >= 1 && random <= 4)
    {
        nextBlock = Level::CreateBlock(3, 'S');
    }
    else if (random >= 5 && random <= 8)
    {
        nextBlock = Level::CreateBlock(3, 'Z');
    }
    // other blocks has probability of 1/6
    else if (random == 9 || random == 10)
    {
        nextBlock = Level::CreateBlock(3, 'I');
    }
    else if (random == 11 || random == 12)
    {
        nextBlock = Level::CreateBlock(3, 'J');
    }
    else if (random == 13 || random == 14)
    {
        nextBlock = Level::CreateBlock(3, 'T');
    }
    else if (random == 15 || random == 16)
    {
        nextBlock = Level::CreateBlock(3, 'O');
    }
    else if (random == 17 || random == 18)
    {
        nextBlock = Level::CreateBlock(3, 'L');
    }
    return nextBlock;
}

Level4::~Level4() {}
