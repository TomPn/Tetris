#ifndef BLOCK_H
#define BLOCK_H 

class Cell;

class Block {
    protected:
        Cell* cell1;
        Cell* cell2;
        Cell* cell3;
        Cell* cell4;
        int alive;

    public:
        Block(Cell* cell1, Cell* cell2, Cell* cell3, Cell* cell4, int alive): cell1{cell1}, cell2{cell2}, cell3{cell3}, cell4(cell4), alive{alive} {};
        void left();
        void right();
        bool down();
        virtual void rotate(bool clockwise);
        void drop() const;
        int getAlive();
        int setAlive(int alive);
};


#endif


