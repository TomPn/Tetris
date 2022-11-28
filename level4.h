#ifndef LEVEL4_H
#define LEVEL4_H
#include "level.h"

class Block;

class Level4 : public Level
{
public:
    Level4(std::string L0File, bool noRandomBool, std::string noRandomFile, bool seedBool, unsigned int seed, std::vector<std::vector<Cell *>> cells);
    Block *CreateNextBlock() override;
    ~Level4() override;
};

#endif
