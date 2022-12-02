#include "block.h"
#include "cell.h"
#include <iostream>

const int cellNum = 4;

// Block constructor
Block::Block(Cell *cell1, Cell *cell2, Cell *cell3, Cell *cell4, int alive, int level, char blockType) : level{level}, alive{alive}, blockType{blockType}, horizontal{true}
{
    components.emplace_back(cell1);
    components.emplace_back(cell2);
    components.emplace_back(cell3);
    components.emplace_back(cell4);

    int tlRow = components[0]->getY();
    int tlCol = components[0]->getX();
    for (int i = 0; i < 4; ++i)
    {
        if (blockType != '*')
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
    }

    topLeftCol = tlCol;
    topLeftRow = tlRow;
}

Block::~Block() {
    for (int i = 0; i < 4; ++i) {
        components[i]->setChar(' ');
        components[i]->setBlock(nullptr);
    }
}

// move the block to the desired direction
bool Block::move(char dir)
{
    // check if it can move to the required direction
    for (int i = 3; i >= 0; i--)
    {
        if (!components[i]->check(dir))
        {
            return false;
        }
    }
    // move the block to the desired direction
    switch (dir)
    {
    case ('d'):
    {
        std::vector<Cell *> orderedComponents;
        int downmostRow = components[0]->getY();
        // loop to find the downmost row
        for (int i = 0; i < 4; ++i)
        {
            if (components[i]->getY() > downmostRow)
            {
                downmostRow = components[i]->getY();
            }
        }
        //  insert components to orderedComponents according to their distance to the downmost row
        for (int i = 0; i < 4; ++i)
        {
            for (int j = 0; j < 4; ++j) // for every component
            {
                if (components[j]->getY() == downmostRow)
                {
                    orderedComponents.emplace_back(components[j]);
                }
            }
            --downmostRow;
        }
        for (int i = 0; i < 4; ++i)
        {
            Cell *neighbour = orderedComponents[i]->getCell(dir);
            neighbour->setChar(orderedComponents[i]->getChar(false));
            neighbour->setBlock(orderedComponents[i]->getBlock());
            orderedComponents[i]->setChar(' ');
            orderedComponents[i]->setBlock(nullptr);
            orderedComponents[i] = neighbour;
        }
        components = orderedComponents;
        ++topLeftRow;
        break;
    }
    case ('l'):
    {
        std::vector<Cell *> orderedComponents;
        int leftMostCol = components[0]->getX();
        // loop to find the downmost row
        for (int i = 0; i < 4; ++i)
        {
            if (components[i]->getX() < leftMostCol)
            {
                leftMostCol = components[i]->getX();
            }
        }
        // insert components to orderedComponents according to their distance to the downmost row
        for (int i = 0; i < 4; ++i)
        {
            for (int j = 0; j < 4; ++j) // for every component
            {
                if (components[j]->getX() == leftMostCol)
                {
                    // std::cerr << "count:  ";
                    // std::cerr << components[j]->getY() << "    " << components[j]->getX() << std::endl;
                    orderedComponents.emplace_back(components[j]);
                }
            }
            ++leftMostCol;
        }
        for (int i = 0; i < cellNum; i++)
        {
            Cell *neighbour = orderedComponents[i]->getCell(dir);
            neighbour->setChar(orderedComponents[i]->getChar(false));
            neighbour->setBlock(orderedComponents[i]->getBlock());
            orderedComponents[i]->setChar(' ');
            orderedComponents[i]->setBlock(nullptr);
            orderedComponents[i] = neighbour;
        }
        components = orderedComponents;
        --topLeftCol;
        break;
    }
    case ('r'):
    {
        std::vector<Cell *> orderedComponents;
        int rightMostCol = components[0]->getX();
        // loop to find the downmost row
        for (int i = 0; i < 4; ++i)
        {
            if (components[i]->getX() > rightMostCol)
            {
                rightMostCol = components[i]->getX();
            }
        }
        for (int i = 0; i < 4; ++i)
        {
            for (int j = 0; j < 4; ++j) // for every component
            {
                if (components[j]->getX() == rightMostCol)
                {
                    // std::cerr << "count:  ";
                    // std::cerr << components[j]->getY() << "    " << components[j]->getX() << std::endl;
                    orderedComponents.emplace_back(components[j]);
                }
            }
            --rightMostCol;
        }
        for (int i = 0; i < 4; ++i)
        {
            Cell *neighbour = orderedComponents[i]->getCell(dir);
            neighbour->setChar(orderedComponents[i]->getChar(false));
            neighbour->setBlock(orderedComponents[i]->getBlock());
            orderedComponents[i]->setChar(' ');
            orderedComponents[i]->setBlock(nullptr);
            orderedComponents[i] = neighbour;
        }
        components = orderedComponents;
        ++topLeftCol;
        ;
        break;
    }
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
    return this->alive = alive;
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

void Block::setComponents(std::vector<Cell *> components)
{
    this->components = components;
}

std::vector<Cell *> Block::getComponents()
{
    return components;
}


