#ifndef LEVEL2_H
#define LEVEL2_H
#include "level.h"

class Block;

class Level2 : public Level
{
public:
    Block *CreateNextBlock() override;
    ~Level2() override;
};

#endif
