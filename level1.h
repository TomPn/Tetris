#ifndef LEVEL1_H
#define LEVEL1_H
#include "level.h"

class Block;

class Level1 : public Level
{
public:
    Level1(bool seedBool, unsigned int seed, std::vector<std::vector<Cell *>> cells)
        : Level{seedBool, seed, cells} {}
    Block *CreateNextBlock() override;
    ~Level1() override;
};

#endif
