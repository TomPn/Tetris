#ifndef LEVEL0_H
#define LEVEL0_H
#include "level.h"

class Block;

class Level0:public Level{
    public:
    Block CreateNextBlock() override;
    ~Level0() override;

};



#endif


