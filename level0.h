#ifndef LEVEL0_H
#define LEVEL0_H
#include "level.h"

class Block;

class Level0 : public Level
{
public:
    Level0(std::string L0File, bool noRandomBool, std::string noRandomFile,
           bool seedBool, unsigned int seed, std::vector<std::vector<Cell *>> cells);
    Block *CreateNextBlock() override;
    ~Level0() override;
};

#endif
