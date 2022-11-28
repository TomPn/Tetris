#include "level.h"
#include "block.h"
#include "cell.h"
#include <string>
#include <fstream>
#include <vector>

// readFile reads the strings in file/sequence/scriptfile store them in a vector of string
std::vector<std::string> Level::readFile(std::string fileName)
{
    // initialize the file object, a string, and a vector of string
    std::ifstream f{fileName};
    std::string s;
    std::vector<std::string> content;
    // read each string in file and insert them into the vecter of string
    while (f >> s)
    {
        content.emplace_back(s);
    }
    return content;
}

Level::Level(std::vector<std::vector<Cell *>> cells) : file{""}, sequence{""}, scriptfile{""}, randomBool{false},
                                                       scriptfileBool{false}, seedBool{false}, seed{0}, cells{cells}, sequenceIndex{0}, scriptfileIndex{0}, fileIndex{0}
{
    // initialize a placeholder for the vector of string
    std::vector<std::string> placeholder{""};
    // if fileName isn't empty, call readFile to read the strings in the file and store them in a vector of string
    if (file != "")
    {
        fileContent = Level::readFile(file);
    }
    else
    {
        fileContent = placeholder;
    }

    if (sequence != "")
    {
        sequenceContent = Level::readFile(sequence);
    }
    else
    {
        sequenceContent = placeholder;
    }

    if (scriptfile != "")
    {
        scriptfileContent = Level::readFile(scriptfile);
    }
    else
    {
        scriptfileContent = placeholder;
    }
}

Block *Level::CreateBlock(int level, char blockType)
{
    std::vector<Cell *> currCells;
    if (blockType == 'I')
    {
        currCells.emplace_back(cells[18][0]);
        currCells.emplace_back(cells[18][1]);
        currCells.emplace_back(cells[18][2]);
        currCells.emplace_back(cells[18][3]);
    }
    else if (blockType = 'J')
    {
        currCells.emplace_back(cells[18][0]);
        currCells.emplace_back(cells[19][0]);
        currCells.emplace_back(cells[19][1]);
        currCells.emplace_back(cells[19][2]);
    }
    else if (blockType = 'L')
    {
        currCells.emplace_back(cells[18][2]);
        currCells.emplace_back(cells[19][0]);
        currCells.emplace_back(cells[19][1]);
        currCells.emplace_back(cells[19][2]);
    }
    else if (blockType = 'O')
    {
        currCells.emplace_back(cells[18][0]);
        currCells.emplace_back(cells[18][1]);
        currCells.emplace_back(cells[19][0]);
        currCells.emplace_back(cells[19][1]);
    }
    else if (blockType = 'S')
    {
        currCells.emplace_back(cells[18][1]);
        currCells.emplace_back(cells[18][2]);
        currCells.emplace_back(cells[19][0]);
        currCells.emplace_back(cells[19][1]);
    }
    else if (blockType = 'Z')
    {
        currCells.emplace_back(cells[18][0]);
        currCells.emplace_back(cells[18][1]);
        currCells.emplace_back(cells[19][1]);
        currCells.emplace_back(cells[19][2]);
    }
    else if (blockType = 'Z')
    {
        currCells.emplace_back(cells[18][0]);
        currCells.emplace_back(cells[18][1]);
        currCells.emplace_back(cells[18][2]);
        currCells.emplace_back(cells[19][1]);
    }

    Block *nextBlock = new Block{currCells[0], currCells[1], currCells[3], currCells[4], 4, level};
    for (auto cell : currCells)
    {
        cell->setChar(blockType);
        cell->setBlock(nextBlock);
    }
    return nextBlock;
}

// mutate scriptfileBool and scriptfile
void Level::setScriptfile(bool scriptfileBool, std::string scriptfile = "")
{
    this->scriptfileBool = scriptfileBool;
    this->scriptfile = scriptfile;
}

// mutate seedBool and seed
void Level::setSeed(bool seedBool, unsigned int seed)
{
    this->seedBool = seedBool;
    this->seed = seed;
}

// mutate randomBool
void Level::setRandom(bool random)
{
    randomBool = random;
}