#ifndef lBLOCK_H
#define lBLOCK_H 
#include "block.h"

class LBlock : public Block {
    public:
        LBlock(Cell *cell1, Cell *cell2, Cell *cell3, Cell *cell4, int alive): Block(cell1, cell2, cell3, cell4, alive) {};
        void rotate(bool clockwise);
};


#endif




