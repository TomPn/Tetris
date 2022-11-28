#ifndef IBLOCK_H
#define IBLOCK_H
#include "block.h"

class IBlock : public Block
{
public:
    IBlock(Cell *cell1, Cell *cell2, Cell *cell3, Cell *cell4, int alive, int level, char blockType) : Block(cell1, cell2, cell3, cell4, alive, level, blockType){};
    void rotate(bool clockwise);
};

#endif
