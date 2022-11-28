#ifndef CELL_H
#define CELL_H

class Block;

class Cell{
    char c;
    int x,y;
    Cell * top, * bottom, * left, * right;
    bool isBlind;
    Block * myBlock;
    public:
    Cell(char c,int x, int y): c{c},x{x},y{y},top{nullptr},bottom{nullptr},left{nullptr},right{nullptr},myBlock{nullptr},isBlind{false} {}
    ~Cell();
    Cell * getCell(char dir);
    Block * getBlock();
    int getX();
    int getY();
    void setBlock(Block * block);
    char getChar(bool isDisplay);
    void setChar(char c);
    bool check(char dir);
    bool setCharNeighbour(char dir, char c);
    void setNeighbour(char dir, Cell * cellPtr);
};

#endif



