#include "block.h"
#include "cell.h"

const int cellNum = 4;

// Block constructor
Block::Block(Cell *cell1, Cell *cell2, Cell *cell3, Cell *cell4, int alive, int level, char blockType) : alive{alive}, level{level}, blockType{blockType}
{
    components.emplace_back(cell1);
    components.emplace_back(cell2);
    components.emplace_back(cell3);
    components.emplace_back(cell4);

    int tlRow = 19;
    int tlCol = 10;
    for (int i = 0; i < 4; ++i)
    {
        if (components[i]->getX() < tlCol)
        {
            tlCol = components[i]->getX();
        }
        if (components[i]->getY() < tlRow)
        {
            tlRow = components[i]->getY();
        }
    }

    topLeftCol = tlCol;
    topLeftRow = tlRow;
}

// move the block to the desired direction
bool Block::move(char dir)
{
    // check if it can move to the required direction
    for (int i = 0; i < cellNum; i++)
    {
        if (!components[i]->check(dir))
        {
            return false;
        }
    }

    // move the block to the desired direction
    for (int i = 0; i < cellNum; i++)
    {
        Cell *neighbour = components[i]->getCell(dir);
        neighbour->setChar(components[i]->getChar(false));
        neighbour->setBlock(components[i]->getBlock());
        components[i]->setChar(' ');
        components[i]->setBlock(nullptr);
    }
    if (dir == 't')
    {
        --topLeftRow;
    }
    else if (dir == 'd')
    {
        ++topLeftRow;
    }
    else if (dir == 'l')
    {
        --topLeftCol;
    }
    else if (dir == 'r')
    {
        ++topLeftCol;
    }
    return true;
}

// move the block to the left
bool Block::left()
{
    if (move('l'))
    {
        return true;
    }
    else
    {
        return false;
    }
}

// move the block to the right
bool Block::right()
{
    if (move('r'))
    {
        return true;
    }
    else
    {
        return false;
    }
}

// move the block down
bool Block::down()
{
    if (move('d'))
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Block::drop() {}

int Block::getLevel()
{
    return level;
}

int Block::getAlive()
{
    return alive;
}

int Block::setAlive(int alive)
{
    this->alive = alive;
}

char Block::getBlockType()
{
    return blockType;
}

bool Block::getHorizontal()
{
    return horizontal;
}

void Block::setHorizontal(bool horizontal)
{
    this->horizontal = horizontal;
}

bool Block::member(Cell *cellPtr)
{
    for (int i = 0; i < 4; ++i)
    {
        if (components[i] == cellPtr)
        {
            return true;
        }
    }
    return false;
}
int Block::getTopLeftRow()
{
    return topLeftRow;
}
int Block::getTopLeftCol()
{
    return topLeftCol;
}
void Block::setTopLeftRow(int row)
{
    topLeftRow = row;
}
void Block::setTopLeftCol(int col)
{
    topLeftCol = col;
}