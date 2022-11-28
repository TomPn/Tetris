#include "level.h"
#include "block.h"
#include "iBlock.h"
#include "jBlock.h"
#include "lBlock.h"
#include "oBlock.h"
#include "sBlock.h"
#include "zBlock.h"
#include "tBlock.h"
#include "cell.h"
#include <string>
#include <fstream>

// readFile reads the characters in file/sequence/scriptfile store them in a vector of char
std::vector<char> Level::readFile(std::string fileName)
{
    // initialize the file object, a char, and a vector of char
    std::ifstream f{fileName};
    char c;
    std::vector<char> content;
    // read each char in file and insert them into the vecter of char
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
      noRandomFileContent{std::vector<char>{' '}}, cells{cells} {} // not sure if vector constructor is used correctly here

Block *Level::CreateBlock(int level, char blockType)
{
    std::vector<Cell *> currCells;
    Block *nextBlock;

    // reset the last two rows
    for (int row = 18; row < 20; ++row)
    {
        for (int col = 0; col < 11; ++col)
        {
            cells[row][col]->setChar(' ');
            cells[row][col]->setBlock(nullptr);
        }
    }

    // for each blockType, insert the corresponding cells to currCells and create a pointer to a new block of the corresponding blockType
    switch ( blockType ) {
        case 'I':
          currCells.emplace_back(cells[18][0]);
          currCells.emplace_back(cells[18][1]);
          currCells.emplace_back(cells[18][2]);
          currCells.emplace_back(cells[18][3]);
          nextBlock = new IBlock{currCells[0], currCells[1], currCells[3], currCells[4], 4, level, blockType};
          break;
        case 'J':
            currCells.emplace_back(cells[18][0]);
            currCells.emplace_back(cells[19][0]);
            currCells.emplace_back(cells[19][1]);
            currCells.emplace_back(cells[19][2]);
            nextBlock = new JBlock{currCells[0], currCells[1], currCells[3], currCells[4], 4, level, blockType};
            break;
        case 'L':
            currCells.emplace_back(cells[18][2]);
            currCells.emplace_back(cells[19][0]);
            currCells.emplace_back(cells[19][1]);
            currCells.emplace_back(cells[19][2]);
            nextBlock = new LBlock{currCells[0], currCells[1], currCells[3], currCells[4], 4, level, blockType};
            break;
        case 'O':
            currCells.emplace_back(cells[18][0]);
            currCells.emplace_back(cells[18][1]);
            currCells.emplace_back(cells[19][0]);
            currCells.emplace_back(cells[19][1]);
            nextBlock = new OBlock{currCells[0], currCells[1], currCells[3], currCells[4], 4, level, blockType};
            break;
         case 'S':
            currCells.emplace_back(cells[18][1]);
            currCells.emplace_back(cells[18][2]);
            currCells.emplace_back(cells[19][0]);
            currCells.emplace_back(cells[19][1]);
            nextBlock = new SBlock{currCells[0], currCells[1], currCells[3], currCells[4], 4, level, blockType};
            break;
          case 'Z':
            currCells.emplace_back(cells[18][0]);
            currCells.emplace_back(cells[18][1]);
            currCells.emplace_back(cells[19][1]);
            currCells.emplace_back(cells[19][2]);
            nextBlock = new ZBlock{currCells[0], currCells[1], currCells[3], currCells[4], 4, level, blockType};\
            break;
          case 'T':
            currCells.emplace_back(cells[18][0]);
            currCells.emplace_back(cells[18][1]);
            currCells.emplace_back(cells[18][2]);
            currCells.emplace_back(cells[19][1]);
            nextBlock = new TBlock{currCells[0], currCells[1], currCells[3], currCells[4], 4, level, blockType};
            break;
    }


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

// generate a newBlock by taking input from file content
Block *Level::CreateNextFromFile(std::vector<char> content, int index)
{
    char c = content[index];
    // create new block according to s;
    Block *nextBlock = CreateBlock(0, c);
    return nextBlock;
}
