#ifndef BLOCK_H
#define BLOCK_H

#include <vector>

class Cell;

class Block
{
protected:
    std::vector<Cell *> components;
    int level;
    int alive;
    bool checkCell(char dir, Cell *cell);
    bool move(char dir);
    char blockType;

public:
    Block(Cell *cell1, Cell *cell2, Cell *cell3, Cell *cell4, int alive, int level, char blockType);
    void left(bool isHeavy);
    void right(bool isHeavy);
    bool down();
    virtual void rotate(bool clockwise) = 0;
    char getBlockType();
    void drop();
    int getAlive();
    int setAlive(int alive);
};

#endif
