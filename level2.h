#ifndef LEVEL2_H
#define LEVEL2_H
#include "level.h"

class Block;

class Level2 : public Level
{
public:
    Level2(std::vector<std::vector<std::shared_ptr<Cell>>> cells)
        : Level{cells} {}
    void setL0File(std::string L0File = "") override;
    void setNoRandom(bool noRandom, std::string noRandomFile = "") override;
    std::unique_ptr<Block> CreateNextBlock() override;
    ~Level2() override;
};

#endif
