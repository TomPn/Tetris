#ifndef LEVEL3_H
#define LEVEL3_H
#include "level.h"

class Block;

class Level3 : public Level
{
public:
    Level3(std::string L0File, bool noRandomBool, std::string noRandomFile, bool seedBool, unsigned int seed, std::vector<std::vector<Cell *>> cells);
    Block *CreateNextBlock() override;
    ~Level3() override;
};

#endif
