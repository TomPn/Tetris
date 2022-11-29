#ifndef CELL_H
#define CELL_H

class Block;

class Cell
{
    char c;
    int x, y;
    Cell *top, *bottom, *left, *right;
    bool isBlind;
    Block *myBlock;
    bool change;

    public:
        Cell(char c, int x, int y) : c{c}, x{x}, y{y}, top{nullptr}, bottom{nullptr}, left{nullptr}, right{nullptr}, isBlind{false}, myBlock{nullptr}, change{true} {}
        ~Cell();
        Cell *getCell(char dir);
        Block *getBlock();
        int getX();
        int getY();
        void setBlock(Block *block);
        char getChar(bool isDisplay);
        void setChar(char c);
        bool check(char dir);
        void setCharNeighbour(char dir, char c);
        void setNeighbour(char dir, Cell *cellPtr);
        void setIsBlind(bool isBlind);
        bool getChange();
        void setChange(bool change);
};

#endif
