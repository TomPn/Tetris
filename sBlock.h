#ifndef SBLOCK_H
#define SBLOCK_H 
#include "block.h"

class SBlock : public Block {
    public:
        SBlock(Cell *cell1, Cell *cell2, Cell *cell3, Cell *cell4, int alive): Block{cell1, cell2, cell3, cell4, alive} {};
        void rotate(bool clockwise);
};


#endif





