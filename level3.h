#ifndef LEVEL3_H
#define LEVEL3_H
#include "level.h"

class Block;

class Level3 : public Level
{
    bool noRandomBool;
    std::string noRandomFile;
    int noRandomFileIndex;
    std::vector<char> noRandomFileContent;

public:
    Level3(bool seedBool, unsigned int seed, std::vector<std::vector<std::shared_ptr<Cell>>> cells)
        : Level{seedBool, seed, cells}, noRandomBool{false}, noRandomFile{""}, noRandomFileIndex{0}, noRandomFileContent{std::vector<char>{' '}}
    {
    }
    void setL0File(std::string L0File = "") override;
    std::unique_ptr<Block> CreateNextBlock() override;
    void setNoRandom(bool noRandom, std::string noRandomFile = "") override;
    ~Level3() override;
};

#endif
