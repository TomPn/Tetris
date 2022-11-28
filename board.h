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
    bool trigger;
    bool isBlind;
    bool isHeavy;
    bool isForce;
    bool over;
    Block *currBlock;
    Block *nextBlock;
    Level *currLevel;
    std::vector<std::vector<Cell *>> cells;
    bool seedBool;
    unsigned int seed;
    void update();
    int checkClear();
    void addstar();
    bool checkForRotate(Cell *cellPtr, int newRow, int newCol);
    void moveForRotate(Cell *cellPtr, int newRow, int newCol);
    bool checkForCurrBlock(std::vector<Cell *> currCells);

public:
    Board(int level, bool seedBool, unsigned int seed);
    void right(int mult);
    void left(int mult);
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
    bool getTrigger();
    int getLevel();
    bool getChange(int row, int col);
    void setScore(int score);
    void setTrigger(bool trigger);
    char charAt(int row, int col);
    void setL0File(std::string L0File = "");
    void setNoRandom(bool noRandom, std::string noRandomFile = "");
};

#endif
