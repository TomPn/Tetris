#ifndef LEVEL1_H
#define LEVEL1_H
#include "level.h"

class Block;

class Level1 : public Level
{
public:
    Level1(std::string L0File, bool noRandomBool, std::string noRandomFile, bool seedBool, unsigned int seed, std::vector<std::vector<Cell *>> cells)
        : Level{L0File, noRandomFile, noRandomBool, seedBool, seed, cells} {}
    Block *CreateNextBlock() override;
    ~Level1() override;
};

#endif
