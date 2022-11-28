#ifndef BOARD_H
#define BOARD_H

#include <vector>

class Board;
class Block;
class Level;
class Cell;

class Board
{
    int level;
    int score;
    int blockCount;
    bool isBlind;
    bool isHeavy;
    bool isForce;
    bool over;
    Board *opponentBoard;
    Block *currBlock;
    Block *nextBlock;
    Level *currLevel;
    std::vector<std::vector<Cell *>> cells;
    void update();
    int checkClear();
    void addstar();

public:
    Board(int level, int score, int blockCount, bool isBlind, bool isHeavy, bool isForce,
          Board *opponentBoard, Block *currBlock, Block *nextBlock, Level *currLevel);
    void right(bool isHeavy);
    void left(bool isHeavy);
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
