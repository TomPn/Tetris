#ifndef CELL_H
#define CELL_H

class Block;

class Cell{
    char c;
    int x,y;
    Cell * top, bottom, left, right;
    bool isBlind;
    Block * myBlock;
    public:
    Cell(char c,int x, int y, Cell* top, Cell* bottom, Cell* left, Cell* right, Block * myBlock): c{c},x{x},y{y},top{top},bottom{bottom},left{left},right{right},myBlock{myBlock},isBlind{false} {}
    ~Cell();
    Cell * getCell(char dir);
    Block * getBlock();
    void setBlock(Block * block);
    char getChar(bool isDisplay);
    void setChar(char c);
    Bool check(char dir);
    Bool setNeighbour(char dir);
};

#endif



