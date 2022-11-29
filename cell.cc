#include "cell.h"
#include "block.h"

// get the neighbour cell of current cell based on direction
Cell *Cell::getCell(char dir)
{
    switch (dir)
    {
    case 't':
        return top;
    case 'b':
        return bottom;
    case 'l':
        return left;
    case 'r':
        return right;
    default:
        return nullptr;
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
    if (this->c == c)
    {
        change = false;
    }
    else
    {
        change = true;
        this->c = c;
    }
}

void Cell::setCharNeighbour(char dir, char c)
{
    switch (dir)
    {
    case 't':
        top->setChar(c);
        break;
    case 'b':
        bottom->setChar(c);
        break;
    case 'l':
        left->setChar(c);
        break;
    case 'r':
        right->setChar(c);
        break;
    } // switch
}

void Cell::setNeighbour(char dir, Cell *cellPtr)
{
    switch (dir)
    {
    case 't':
        top = cellPtr;
        break;
    case 'b':
        bottom = cellPtr;
        break;
    case 'l':
        left = cellPtr;
        break;
    case 'r':
        right = cellPtr;
        break;
    } // switch
}

bool Cell::check(char dir)
{
    switch (dir)
    {
    case 'l':
        // check if it's the first in a row
        if (x == 0)
        {
            return false;
        }
        else if (left->getBlock() != myBlock && left->getBlock() != nullptr)
        {
            return false;
        }
        return true;
    case 'r':
        // check if it's the last in a row
        if (x == 10)
        {
            return false;
        }
        else if (right->getBlock() != myBlock && right->getBlock() != nullptr)
        {
            return false;
        }
        return true;
    case 't':
        // check if it's the first row
        if (y == 0)
        {
            return false;
        }
        else if (top->getBlock() != myBlock && top->getBlock() != nullptr)
        {
            return false;
        }
        return true;
    case 'b':
        // check if it's the last row
        if (y == 17)
        {
            return false;
        }
        else if (bottom->getBlock() != myBlock && bottom->getBlock() != nullptr)
        {
            return false;
        }
        return true;
    default:
        return false;
    }
}

void Cell::setIsBlind(bool isBlind)
{
    this->isBlind = isBlind;
}

bool Cell::getChange()
{
    return change;
}

void Cell::setChange(bool change)
{
    this->change = change;
}

Cell::~Cell() {}
