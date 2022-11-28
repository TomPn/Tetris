#include "level.h"
#include "block.h"
#include "cell.h"
#include <string>
#include <fstream>
#include <vector>

// readFile reads the strings in file/sequence/scriptfile store them in a vector of string
std::vector<char> Level::readFile(std::string fileName)
{
    // initialize the file object, a string, and a vector of string
    std::ifstream f{fileName};
    char c;
    std::vector<char> content;
    // read each string in file and insert them into the vecter of string
    while (f >> c)
    {
        content.emplace_back(c);
    }
    return content;
}

Level::Level(std::string L0File, std::string noRandomFile, bool noRandomBool,
             bool seedBool, unsigned int seed, std::vector<std::vector<Cell *>> cells)
    : L0File{L0File}, noRandomFile{noRandomFile}, noRandomBool{noRandomBool}, seedBool{seedBool},
      seed{seed}, L0FileIndex{0}, noRandomFileIndex{0}, L0FileContent{std::vector<char>{' '}},
      noRandomFileContent{std::vector<char>{' '}}, cells{cells} {}

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
    else if (blockType = 'T')
    {
        currCells.emplace_back(cells[18][0]);
        currCells.emplace_back(cells[18][1]);
        currCells.emplace_back(cells[18][2]);
        currCells.emplace_back(cells[19][1]);
    }

    Block *nextBlock = new Block{currCells[0], currCells[1], currCells[3], currCells[4], 4, level, blockType};
    for (auto cell : currCells)
    {
        cell->setChar(blockType);
        cell->setBlock(nextBlock);
    }
    return nextBlock;
}

// mutate seedBool and seed
void Level::setSeed(bool seedBool, unsigned int seed = 0)
{
    this->seedBool = seedBool;
    this->seed = seed;
}

// mutate randomBool
void Level::setNoRandom(bool random)
{
    noRandomBool = random;
}

Block *Level::CreateNextFromFile(std::vector<char> content, int index)
{
    char c = content[index];
    // create new block according to s;
    Block *nextBlock = Level::CreateBlock(0, c);
    return nextBlock;
}