#ifndef LEVEL1_H
#define LEVEL1_H
#include "level.h"

class Block;

class Level1:public Level{
    public:
    Block CreateNextBlock() override;
    ~Level1() override;

};

#endif


