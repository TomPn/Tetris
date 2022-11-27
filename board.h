#ifndef BOARD_H
#define BOARD_H 

#include <vector>

class Board;
class Block;
class Level;

class Board {
    int level;
    int score;
    bool isBlind;
    bool isHeavy;
    bool isForce;
    Board* opponentBoard;
    Block* currBlock;
    Block* nextBlock;
    Level* currLevel;
    std::vector<vector<Cell *>> cells;
    void update();
    int checkClear();

    public:
        Board();
        void right();
        void left();
        bool down();
        void rotate(bool clockwise);
        void drop();
        void levelDown();
        void levelUp();
        void setBlind();
        void setHeavy();
        void setForce(char blockType);
        void IJL(char blockType);
        void setCurrBlock(char blockType);
        int getScore();
        char charAt(int row, int col);

};


#endif




