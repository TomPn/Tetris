#ifndef LEVEL_H
#define LEVEL_H
#include <string>
#include <vector>
#include <memory>

class Block;
class Cell;

class Level
{
protected:
    bool seedBool;
    unsigned int seed;
    std::vector<std::vector<std::shared_ptr<Cell>>> cells;
    std::vector<char> readFile(std::string fileName);
    std::unique_ptr<Block> CreateNextFromFile(std::vector<char> content, int index);

public:
    Level(std::vector<std::vector<std::shared_ptr<Cell>>> cells);
    virtual ~Level() = 0;
    virtual void setL0File(std::string L0File = "") = 0;
    virtual void setNoRandom(bool noRandom, std::string noRandomFile = "") = 0;
    void setSeed(unsigned int seed);
    virtual std::unique_ptr<Block> CreateNextBlock() = 0;
    std::unique_ptr<Block> CreateBlock(int level, char blockType);
};

#endif
