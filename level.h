#ifndef LEVEL_H
#define LEVEL_H
#include <string>
#include <vector>

class Block;
class Cell;

class Level
{
protected:
    bool seedBool;
    unsigned int seed;
    std::vector<std::vector<Cell *>> cells;
    std::vector<char> readFile(std::string fileName);
    Block *CreateNextFromFile(std::vector<char> content, int index);

public:
    Level(bool seedBool, unsigned int seed, std::vector<std::vector<Cell *>> cells);
    virtual ~Level();
    virtual void setL0File(std::string L0File = "");
    virtual void setNoRandom(bool noRandom, std::string noRandomFile = "");
    void setSeed(bool seedBool, unsigned int seed = 0);
    virtual Block *CreateNextBlock() = 0;
    Block *CreateBlock(int level, char blockType);
};

#endif
