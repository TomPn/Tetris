#ifndef LEVEL2_H
#define LEVEL2_H
#include "level.h"

class Block;

class Level2 : public Level
{
public:
    Level2(bool seedBool, unsigned int seed, std::vector<std::vector<Cell *>> cells)
        : Level{seedBool, seed, cells} {}
    Block *CreateNextBlock() override;
    ~Level2() override;
};

#endif
