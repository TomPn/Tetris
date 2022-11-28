#include <fstream>
#include "level0.h"
#include <string>

class Block;

Block *Level0::CreateNextBlock()
{
    // if the index exceeds the length of content, set the index to 0 so that the program will read it again from the beginning
    if (sequenceIndex == sequenceContent.size())
    {
        sequenceIndex = 0;
    }
    if (scriptfileIndex == scriptfileContent.size())
    {
        scriptfileIndex = 0;
    }
    // extract the string that represent the next block
    std::string s = sequenceContent[sequenceIndex];
    if (scriptfileBool == true)
    {
        s = scriptfileContent[scriptfileIndex];
    }
    // create new block according to s;
    Block *nextBlock;
    if (s == "I")
    {
        nextBlock = Level::CreateBlock(0, 'I');
    }
    else if (s == "J")
    {
        nextBlock = Level::CreateBlock(0, 'J');
    }
    else if (s == "L")
    {
        nextBlock = Level::CreateBlock(0, 'L');
    }
    else if (s == "O")
    {
        nextBlock = Level::CreateBlock(0, 'O');
    }
    else if (s == "S")
    {
        nextBlock = Level::CreateBlock(0, 'S');
    }
    else if (s == "Z")
    {
        nextBlock = Level::CreateBlock(0, 'Z');
    }
    else if (s == "T")
    {
        nextBlock = Level::CreateBlock(0, 'T');
    }

    // increment index
    if (scriptfileBool == true)
    {
        ++scriptfileIndex;
    }
    else
    {
        ++sequenceIndex;
    }
    return nextBlock;
}

Level0::~Level0() {}