#include "cell.h"
#include "block.h"

// get the neighbour cell of current cell based on direction
Cell *Cell::getCell(char dir)
{
    if (dir == 't')
    {
        return top;
    }
    else if (dir == 'b')
    {
        return bottom;
    }
    else if (dir == 'l')
    {
        return left;
    }
    else if (dir == 'r')
    {
        return right;
    }
}

// get the block that the cell belongs to
Block *Cell::getBlock()
{
    return myBlock;
}

// get x coordinate of current cell
int Cell::getX()
{
    return x;
}

// get y coordinate of current cell
int Cell::getY()
{
    return y;
}

void Cell::setBlock(Block *block)
{
    myBlock = block;
}

char Cell::getChar(bool isDisplay)
{
    if (isDisplay && isBlind)
    {
        return '?';
    }
    else
    {
        return c;
    }
}

void Cell::setChar(char c)
{
    this->c = c;
}

void Cell::setCharNeighbour(char dir, char c)
{
    if (dir == 't')
    {
        top->setChar(c);
    }
    else if (dir == 'b')
    {
        bottom->setChar(c);
    }
    else if (dir == 'l')
    {
        left->setChar(c);
    }
    else
    {
        right->setChar(c);
    }
}

void Cell::setNeighbour(char dir, Cell *cellPtr)
{
    if (dir == 't')
    {
        top = cellPtr;
    }
    else if (dir == 'b')
    {
        bottom = cellPtr;
    }
    else if (dir == 'l')
    {
        left = cellPtr;
    }
    else if (dir == 'r')
    {
        right = cellPtr;
    }
}

bool Cell::check(char dir)
{
    if (dir == 'l')
    {
        // check if it's the first in a row
        if (x == 0)
        {
            return false;
        }
        else if (left->getBlock() != myBlock)
        {
            return false;
        }
    }
    else if (dir == 'r')
    {
        if (x == 10)
        {
            return false;
        }
        else if (right->getBlock() != myBlock)
        {
            return false;
        }
    }
    else if (dir == 't')
    {
        if (y == 0)
        {
            return false;
        }
        else if (top->getBlock() != myBlock)
        {
            return false;
        }
    }
    else
    {
        if (y == 17)
        {
            return false;
        }
        else if (bottom->getBlock() != myBlock)
        {
            return false;
        }
    }
}

Cell::~Cell() {}
