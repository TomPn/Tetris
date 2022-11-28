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
    std::string L0File;
    bool noRandomBool;
    std::string noRandomFile;
    bool seedBool;
    unsigned int seed;
    void update();
    std::vector<int> checkClear();
    void addstar();

public:
    Board(int level, std::string L0File, bool noRandomBool, std::string noRandomFile, bool seedBool, unsigned int seed);
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
