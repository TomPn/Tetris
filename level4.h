#ifndef LEVEL4_H
#define LEVEL4_H
#include "level.h"

class Block;

class Level4 : public Level
{
    bool noRandomBool;
    std::string noRandomFile;
    int noRandomFileIndex;
    std::vector<char> noRandomFileContent;

public:
    Level4(bool seedBool, unsigned int seed, std::vector<std::vector<Cell *>> cells)
        : Level{seedBool, seed, cells}, noRandomBool{false}, noRandomFile{""}, noRandomFileIndex{0}, noRandomFileContent{std::vector<char>{' '}}
    {
    }
    void setNoRandom(bool noRandom, std::string noRandomFile = "");
    Block *CreateNextBlock() override;
    ~Level4() override;
};

#endif
