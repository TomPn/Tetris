#ifndef LEVEL_H
#define LEVEL_H
#include <string>
#include <vector>

class Block;
class Cell;

class Level
{
protected:
    std::string L0File, noRandomFile;
    bool noRandomBool, seedBool;
    unsigned int seed;
    int L0FileIndex;
    int noRandomFileIndex;
    std::vector<char> L0FileContent;
    std::vector<char> noRandomFileContent;
    std::vector<std::vector<Cell *>> cells;
    std::vector<char> readFile(std::string fileName);
    Block *CreateNextFromFile(std::vector<char> content, int index);

public:
    Level(std::string L0File, std::string noRandomFile, bool noRandomBool,
          bool seedBool, unsigned int seed, std::vector<std::vector<Cell *>> cells);
    virtual ~Level();
    void setSeed(bool seedBool, unsigned int seed = 0);
    virtual Block *CreateNextBlock() = 0;
    void setNoRandom(bool noRandom);
    Block *CreateBlock(int level, char blockType);
};

#endif
