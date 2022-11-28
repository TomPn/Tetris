#ifndef LEVEL0_H
#define LEVEL0_H
#include "level.h"

class Block;

class Level0 : public Level
{
public:
    Level0() : Level{file, sequence, scriptfile, randomBool, scriptfileBool, seedBool, seed, cells, sequenceIndex, scriptfileIndex, fileIndex, sequenceContent, scriptfileContent, fileContent} {};
    Block *CreateNextBlock() override;
    ~Level0() override;
};

#endif
