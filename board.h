#ifndef BOARD_H
#define BOARD_H 

#include <vector>

class Board;
class Block;
class Level;
class Cell;

class Board {
    int level;
    int score;
    int blockCount;
    bool trigger;
    bool isBlind;
    bool isHeavy;
    bool isForce;
    Board* opponentBoard;
    Block* currBlock;
    Block* nextBlock;
    Level* currLevel;
    std::vector<std::vector<Cell *>> cells;
    void update();
    int checkClear();
    void addstar();

    public:
        Board(int level, int score, int blockCount, bool trigger, bool isBlind, bool isHeavy, bool isForce,
             Board* opponentBoard, Block* currBlock, Block* nextBlock, Level* currLevel);
        void right(bool isHeavy, int mult);
        void left(bool isHeavy, int mult);
        bool down();
        void rotate(bool clockwise);
        void drop();
        void levelDown();
        void levelUp();
        void setBlind();
        void setHeavy();
        bool getTrigger();
        void setTrigger(bool trigger);
        void setForce(char blockType);
        void IJL(char blockType);
        void setCurrBlock(char blockType);
        int getScore();
        int getLevel();
        char charAt(int row, int col);

};


#endif




