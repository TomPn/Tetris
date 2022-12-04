#include "level1.h"
#include "block.h"
#include <string>
#include <cstdlib>

void Level1::setL0File(std::string L0File) {}
void Level1::setNoRandom(bool noRandom, std::string noRandomFile) {}

std::unique_ptr<Block> Level1::CreateNextBlock()
{
    std::unique_ptr<Block> nextBlock;

    // random is a random int from 1 to 12
    int random = 1 + std::rand() / ((RAND_MAX + 1u) / 12);

    switch (random)
    {
    // SBlock and ZBlock has probability of 1/12
    case 1:
        nextBlock = Level::CreateBlock(1, 'S');
        break;
    case 2:
        nextBlock = Level::CreateBlock(1, 'Z');
        break;
    // other blocks has probability of 1/6
    case 3:
    case 4:
        nextBlock = Level::CreateBlock(1, 'I');
        break;
    case 5:
    case 6:
        nextBlock = Level::CreateBlock(1, 'J');
        break;
    case 7:
    case 8:
        nextBlock = Level::CreateBlock(1, 'T');
        break;
    case 9:
    case 10:
        nextBlock = Level::CreateBlock(1, 'O');
        break;
    case 11:
    case 12:
        nextBlock = Level::CreateBlock(1, 'L');
        break;
    } // switch

    return nextBlock;
}

Level1::~Level1() {}
