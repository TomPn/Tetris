#ifndef lBLOCK_H
#define lBLOCK_H
#include "block.h"

class LBlock : public Block
{
public:
    LBlock(Cell *cell1, Cell *cell2, Cell *cell3, Cell *cell4, int alive, int level, char blockType) : Block(cell1, cell2, cell3, cell4, alive, level, blockType){};
    char getBlockType() const override;
};

#endif
