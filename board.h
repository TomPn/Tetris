#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <string>
#include <memory>
class Board;
class Block;
class Level;
class Cell;

class Board
{
    std::string playerName;
    int level;
    int score;
    int blockCount;
    bool trigger;
    bool isBlind;
    bool isHeavy;
    bool isForce;
    bool over;
    std::unique_ptr<Block> currBlock;
    std::unique_ptr<Block> nextBlock;
    std::unique_ptr<Level> currLevel;
    std::vector<std::vector<std::shared_ptr<Cell>>> cells;
    std::vector<std::unique_ptr<Block>> blocksPlaced;
    bool seedBool;
    unsigned int seed;
    std::string L0File;
    void update();
    int checkClear();
    void addstar();
    bool checkForCurrBlock(std::vector<Cell *> currCells);
    bool checkRowClear(int row);
    void rotateHelper(bool rectangleType, bool horizontal, std::vector<int> rowsOfOriginal, std::vector<int> colsOfOriginal, std::vector<int> rowsOfDesination, std::vector<int> colsOfDesination, char blockType);

public:
    Board(int level, bool seedBool, unsigned int seed, std::string L0File);
    ~Board();
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
    void setName(std::string name);
    std::string getName();
};

#endif
