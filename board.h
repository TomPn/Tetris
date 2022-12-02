#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <string>
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
    std::string L0File;
    void update();
    int checkClear();
    void addstar();
    bool checkForRotate(Cell *cellPtr, int newRow, int newCol, std::vector<int> &rowsOfBlockDesination, std::vector<int> &colsOfBlockDesination);
    void moveForRotate(Cell *cellPtr, int newRow, int newCol, std::vector<int> &rowsOfBlockDesination, std::vector<int> &colsOfBlockDesination, char originalChar, Block *originalBlock);
    bool checkForCurrBlock(std::vector<Cell *> currCells);
    bool checkRowClear(int row);
    void rotateHelper(bool twoThree, bool horizontal, std::vector<std::pair<int, int>> Original, std::vector<std::pair<int, int>> Desination);

public:
    Board(int level, bool seedBool, unsigned int seed, std::string L0File);
    bool right(int mult);
    bool left(int mult);
    bool down();
    void rotate(bool clockwise);
    bool drop();
    void levelDown();
    void levelUp();
    void setBlind();
    void setHeavy();
    void setForce(char blockType);
    void IJL(char blockType);
    bool setCurrBlock(char blockType);
    int getScore();
    bool getTrigger();
    int getLevel();
    bool getChange(int row, int col);
    void setScore(int score);
    void setTrigger(bool trigger);
    char charAt(int row, int col);
    void setL0File(std::string L0File = "");
    void setNoRandom(bool noRandom, std::string noRandomFile = "");
    bool getOver();
};

#endif
