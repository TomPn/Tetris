#ifndef LEVEL4_H
#define LEVEL4_H
#include "level.h"

class Block;

class Level4 : public Level
{
public:
    Block *CreateNextBlock() override;
    ~Level4() override;
};

#endif
