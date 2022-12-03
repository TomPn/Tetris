#ifndef LEVEL1_H
#define LEVEL1_H
#include "level.h"

class Block;

class Level1 : public Level
{
public:
    Level1(std::vector<std::vector<std::shared_ptr<Cell>>> cells)
        : Level{cells} {}
    void setL0File(std::string L0File = "") override;
    void setNoRandom(bool noRandom, std::string noRandomFile = "") override;
    std::unique_ptr<Block> CreateNextBlock() override;
    ~Level1() override;
};

#endif
