#include "board.h"
#include "block.h"
#include "iBlock.h"
#include "jBlock.h"
#include "lBlock.h"
#include "oBlock.h"
#include "sBlock.h"
#include "zBlock.h"
#include "tBlock.h"
#include "starBlock.h"
#include "cell.h"
#include "level.h"
#include "level0.h"
#include "level1.h"
#include "level2.h"
#include "level3.h"
#include "level4.h"
#include <vector>

const int rows = 20;
const int cols = 11;

Board::Board(int level, std::string L0File, bool noRandomBool, std::string noRandomFile, bool seedBool, unsigned int seed)
    : level{level}, score{0}, blockCount{0}, isBlind{false}, isHeavy{false}, isForce{false}, over{false}, L0File{L0File}, noRandomBool{noRandomBool}, noRandomFile{noRandomFile},
      seedBool{seedBool}, seed{seed}
{

    std::vector<std::vector<Cell *>> cells(rows, std::vector<Cell *> (cols, nullptr));
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            cells[i][j] = new Cell{' ', i, j};
        }
    }
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (cells[i][j]->getY() != 0)
            {
                cells[i][j]->setNeighbour('t', cells[i - 1][j]);
            }
            else if (cells[i][j]->getY() != rows - 1)
            {
                cells[i][j]->setNeighbour('b', cells[i + 1][j]);
            }
            else if (cells[i][j]->getX() != 0)
            {
                cells[i][j]->setNeighbour('l', cells[i][j - 1]);
            }
            else if (cells[i][j]->getX() != cols - 1)
            {
                cells[i][j]->setNeighbour('r', cells[i][j + 1]);
            }
        }
    }
    this->cells = cells; // could be wrong

    Level *tempLevel;
    if (level == 0)
    {
        tempLevel = new Level0{L0File, noRandomBool, noRandomFile, seedBool, seed, cells};
    }
    else if (level == 1)
    {
        tempLevel = new Level1{L0File, noRandomBool, noRandomFile, seedBool, seed, cells};
    }
    else if (level == 2)
    {
        tempLevel = new Level2{L0File, noRandomBool, noRandomFile, seedBool, seed, cells};
    }
    else if (level == 3)
    {
        tempLevel = new Level3{L0File, noRandomBool, noRandomFile, seedBool, seed, cells};
    }
    else if (level == 4)
    {
        tempLevel = new Level4{L0File, noRandomBool, noRandomFile, seedBool, seed, cells};
    }

    currLevel = tempLevel;

    Block *nextBlock = currLevel->CreateNextBlock();
    char blockType = nextBlock->getBlockType();
    setCurrBlock(blockType);
    delete nextBlock;
    Block *nextBlock = currLevel->CreateNextBlock();
    this->nextBlock = nextBlock;
}

void Board::right(bool isHeavy, int mult)
{
    for (int i = 0; i < mult; i++)
    {
        currBlock->right(isHeavy);
    }
}

void Board::left(bool isHeavy, int mult)
{
    for (int i = 0; i < mult; i++)
    {
        currBlock->left(isHeavy);
    }
}

bool Board::down()
{
    currBlock->down();
}

void Board::drop()
{
    isForce = false;
    isBlind = false;
    while (down())
    {
    }
    int clearResult = checkClear();

    if (clearResult >= 2)
    {
        setTrigger(true);
    }
    if (clearResult == 0)
    {
        blockCount += 1;
    }
    else
    {
        blockCount = 0;
    }
    if (blockCount == 5)
    {
        addstar();
        blockCount = 0;
    }
    setCurrBlock(nextBlock->getBlockType());
    delete (nextBlock);
    nextBlock = currLevel->CreateNextBlock();
}

bool Board::checkForRotate(Cell *cellPtr, int newRow, int newCol)
{
    if (newRow > 17 || newRow < 0 || newCol > 10 || newCol < 0)
    {
        return false;
    }
    if (!(currBlock->member(cellPtr) && cells[newRow][newCol]->check('s')))
    {
        return false;
    }

    return true;
}

void Board::moveForRotate(Cell *cellPtr, int newRow, int newCol)
{
    cells[newRow][newCol]->setChar(cellPtr->getChar(false));
    cells[newRow][newCol]->setBlock(cellPtr->getBlock());
    cellPtr->setChar(' ');
    cellPtr->setBlock(nullptr);
}

void Board::rotate(bool clockwise)
{
    char blockType = currBlock->getBlockType();
    bool horizontal = currBlock->getHorizontal();
    int tlRow = currBlock->getTopLeftRow();
    int tlCol = currBlock->getTopLeftCol();
    bool valid = true;
    if (blockType == 'J' || blockType == 'L' || blockType == 'S' || blockType == 'Z' || blockType == 'T')
    {
        if (horizontal && clockwise)
        {
            valid = valid && checkForRotate(cells[tlRow][tlCol], tlRow - 1, tlCol + 1);
            valid = valid && checkForRotate(cells[tlRow + 1][tlCol], tlRow - 1, tlCol);
            if (valid)
            {
                moveForRotate(cells[tlRow][tlCol], tlRow - 1, tlCol + 1);
                moveForRotate(cells[tlRow + 1][tlCol], tlRow - 1, tlCol);
            }
            // valid = valid && checkForRotate(cells[tlRow][tlCol + 1], tlRow, tlCol + 1);
            // valid = valid && checkForRotate(cells[tlRow + 1][tlCol + 1], tlRow, tlCol);
            // valid = valid && checkForRotate(cells[tlRow][tlCol + 2], tlRow + 1, tlCol + 1);
            // valid = valid && checkForRotate(cells[tlRow + 1][tlCol + 2], tlRow + 1, tlCol);
            currBlock->setTopLeftRow(tlRow - 1);
            currBlock->setTopLeftCol(tlCol);
            currBlock->setHorizontal(false);
        }
        else if (horizontal && !clockwise)
        {
            valid = valid && checkForRotate(cells[tlRow][tlCol + 2], tlRow - 1, tlCol);
            valid = valid && checkForRotate(cells[tlRow + 1][tlCol + 2], tlRow - 1, tlCol + 1);
            if (valid)
            {
                moveForRotate(cells[tlRow][tlCol + 2], tlRow - 1, tlCol);
                moveForRotate(cells[tlRow + 1][tlCol + 2], tlRow - 1, tlCol + 1);
            }
            // valid = valid && checkForRotate(cells[tlRow][tlCol + 2], tlRow, tlCol);
            // valid = valid && checkForRotate(cells[tlRow + 1][tlCol + 2], tlRow, tlCol + 1);
            // valid = valid && checkForRotate(cells[tlRow][tlCol + 2], tlRow + 1, tlCol);
            // valid = valid && checkForRotate(cells[tlRow + 1][tlCol + 2], tlRow + 1, tlCol + 1);
            currBlock->setTopLeftRow(tlRow - 1);
            currBlock->setTopLeftCol(tlCol);
            currBlock->setHorizontal(false);
        }
        else if (!horizontal && clockwise)
        {
            valid = valid && checkForRotate(cells[tlRow][tlCol], tlRow + 1, tlCol + 2);
            valid = valid && checkForRotate(cells[tlRow][tlCol + 1], tlRow + 2, tlCol + 1);
            if (valid)
            {
                moveForRotate(cells[tlRow][tlCol], tlRow + 1, tlCol + 2);
                moveForRotate(cells[tlRow][tlCol + 1], tlRow + 2, tlCol + 1);
            }
            currBlock->setTopLeftRow(tlRow + 1);
            currBlock->setTopLeftCol(tlCol);
            currBlock->setHorizontal(true);
        }
        else if (!horizontal && !clockwise)
        {
            valid = valid && checkForRotate(cells[tlRow][tlCol], tlRow + 2, tlCol - 1);
            valid = valid && checkForRotate(cells[tlRow][tlCol + 1], tlRow + 1, tlCol - 1);
            if (valid)
            {
                moveForRotate(cells[tlRow][tlCol], tlRow + 2, tlCol - 1);
                moveForRotate(cells[tlRow][tlCol + 1], tlRow + 1, tlCol - 1);
            }
            currBlock->setTopLeftRow(tlRow + 1);
            currBlock->setTopLeftCol(tlCol - 1);
            currBlock->setHorizontal(true);
        }
    }
    else if (blockType == 'I')
    {
        if (horizontal && clockwise)
        {
            valid = valid && checkForRotate(cells[tlRow][tlCol], tlRow - 3, tlCol);
            valid = valid && checkForRotate(cells[tlRow][tlCol + 1], tlRow - 2, tlCol);
            valid = valid && checkForRotate(cells[tlRow][tlCol + 2], tlRow - 1, tlCol);
            valid = valid && checkForRotate(cells[tlRow][tlCol + 3], tlRow, tlCol);
            if (valid)
            {
                moveForRotate(cells[tlRow][tlCol], tlRow - 3, tlCol);
                moveForRotate(cells[tlRow][tlCol + 1], tlRow - 2, tlCol);
                moveForRotate(cells[tlRow][tlCol + 2], tlRow - 1, tlCol);
                moveForRotate(cells[tlRow][tlCol + 3], tlRow, tlCol);
            }
            currBlock->setTopLeftRow(tlRow - 3);
            currBlock->setTopLeftCol(tlCol);
            currBlock->setHorizontal(false);
        }
        else if (horizontal && !clockwise)
        {
            valid = valid && checkForRotate(cells[tlRow][tlCol + 1], tlRow - 1, tlCol);
            valid = valid && checkForRotate(cells[tlRow][tlCol + 2], tlRow - 2, tlCol);
            valid = valid && checkForRotate(cells[tlRow][tlCol + 3], tlRow - 3, tlCol);
            if (valid)
            {
                moveForRotate(cells[tlRow][tlCol + 1], tlRow - 1, tlCol);
                moveForRotate(cells[tlRow][tlCol + 2], tlRow - 2, tlCol);
                moveForRotate(cells[tlRow][tlCol + 3], tlRow - 3, tlCol);
            }
            currBlock->setTopLeftRow(tlRow - 3);
            currBlock->setTopLeftCol(tlCol);
            currBlock->setHorizontal(false);
        }
        else if (!horizontal && clockwise)
        {
            valid = valid && checkForRotate(cells[tlRow][tlCol], tlRow + 3, tlCol);
            valid = valid && checkForRotate(cells[tlRow + 1][tlCol], tlRow + 2, tlCol + 1);
            valid = valid && checkForRotate(cells[tlRow + 2][tlCol], tlRow + 1, tlCol + 2);
            valid = valid && checkForRotate(cells[tlRow + 3][tlCol], tlRow, tlCol + 3);
            if (valid)
            {
                moveForRotate(cells[tlRow][tlCol], tlRow + 3, tlCol);
                moveForRotate(cells[tlRow + 1][tlCol], tlRow + 2, tlCol + 1);
                moveForRotate(cells[tlRow + 2][tlCol], tlRow + 1, tlCol + 2);
                moveForRotate(cells[tlRow + 3][tlCol], tlRow, tlCol + 3);
            }
            currBlock->setTopLeftRow(tlRow + 3);
            currBlock->setTopLeftCol(tlCol);
            currBlock->setHorizontal(true);
        }
        else if (!horizontal && !clockwise)
        {
            valid = valid && checkForRotate(cells[tlRow][tlCol], tlRow + 3, tlCol - 3);
            valid = valid && checkForRotate(cells[tlRow + 1][tlCol], tlRow + 2, tlCol - 2);
            valid = valid && checkForRotate(cells[tlRow + 2][tlCol], tlRow + 1, tlCol - 1);
            valid = valid && checkForRotate(cells[tlRow + 3][tlCol], tlRow, tlCol);
            if (valid)
            {
                moveForRotate(cells[tlRow][tlCol], tlRow + 3, tlCol - 3);
                moveForRotate(cells[tlRow + 1][tlCol], tlRow + 2, tlCol - 2);
                moveForRotate(cells[tlRow + 2][tlCol], tlRow + 1, tlCol - 1);
                moveForRotate(cells[tlRow + 3][tlCol], tlRow, tlCol);
            }
            currBlock->setTopLeftRow(tlRow + 3);
            currBlock->setTopLeftCol(tlCol - 3);
            currBlock->setHorizontal(true);
        }
    }
}

bool Board::getTrigger()
{
    return trigger;
}

void Board::setTrigger(bool trigger)
{
    this->trigger = trigger;
}

void Board::levelDown()
{
    if (level > 0)
    {
        level--;
        Level *tmp = currLevel;
        if (level == 1)
        {
            currLevel = new Level1{L0File, noRandomBool, noRandomFile, seedBool, seed, cells};
        }
        else if (level == 2)
        {
            currLevel = new Level2{L0File, noRandomBool, noRandomFile, seedBool, seed, cells};
        }
        else if (level == 3)
        {
            currLevel = new Level3{L0File, noRandomBool, noRandomFile, seedBool, seed, cells};
        }
        else if (level == 4)
        {
            currLevel = new Level4{L0File, noRandomBool, noRandomFile, seedBool, seed, cells};
        }
        delete tmp;
    }
}

void Board::levelUp()
{
    if (level < 4)
    {
        level++;
        Level *tmp = currLevel;
        if (level == 0)
        {
            currLevel = new Level1{L0File, noRandomBool, noRandomFile, seedBool, seed, cells};
        }
        else if (level == 1)
        {
            currLevel = new Level2{L0File, noRandomBool, noRandomFile, seedBool, seed, cells};
        }
        else if (level == 2)
        {
            currLevel = new Level3{L0File, noRandomBool, noRandomFile, seedBool, seed, cells};
        }
        else if (level == 3)
        {
            currLevel = new Level4{L0File, noRandomBool, noRandomFile, seedBool, seed, cells};
        }
        delete tmp;
    }
}

void Board::setBlind()
{
    isBlind = true;
}

void Board::setHeavy()
{
    isHeavy = true;
}

void Board::setForce(char blockType)
{
    setCurrBlock(blockType);
    isForce = true;
}

int Board::getScore()
{
    return score;
}

void Board::setScore(int score)
{
    this->score = score;
}

int Board::getLevel()
{
    return level;
}

char Board::charAt(int row, int col)
{
    return cells[row][col]->getChar(isBlind);
}

int Board::checkClear()
{
    int clear = 0;
    bool rowClear;

    for (int i = 0; i < rows - 2; i++)
    {
        rowClear = true;
        for (int j = 0; j < cols; j++)
        {
            if (cells[i][j]->getBlock() == nullptr)
            {
                rowClear = false;
                break;
            }
        }
        if (rowClear)
        {
            clear += 1;
            for (int i2 = i; i2 > 0; i2--)
            {
                for (int j2 = 0; j2 < cols; j2++)
                {
                    if (i2 == i)
                    {
                        Block *currBlock = cells[i2][j2]->getBlock();
                        if (currBlock->getAlive() == 1)
                        {
                            score += (currBlock->getLevel() + 1) * (currBlock->getLevel() + 1); 
                            delete currBlock;
                            cells[i2][j2]->setBlock(nullptr);
                        }
                        else
                        {
                            currBlock->setAlive(currBlock->getAlive() - 1);
                        }
                        cells[i2][j2]->setChar(' ');
                    }
                    if (i2 != 0)
                    {
                        cells[i2][j2]->setBlock(cells[i2 - 1][j2]->getBlock());
                        cells[i2][j2]->setChar(cells[i2 - 1][j2]->getChar(false));
                    }
                }
            }
        }
    }
    score += (level + clear) * (level + clear); 
    return clear;
}


void Board::setCurrBlock(char blockType)
{
    std::vector<Cell *> currCells;
    if (blockType == 'I')
    {
        currCells.emplace_back(cells[3][0]);
        currCells.emplace_back(cells[3][1]);
        currCells.emplace_back(cells[3][2]);
        currCells.emplace_back(cells[3][3]);
    }
    else if (blockType = 'J')
    {
        currCells.emplace_back(cells[2][0]);
        currCells.emplace_back(cells[3][0]);
        currCells.emplace_back(cells[3][1]);
        currCells.emplace_back(cells[3][2]);
    }
    else if (blockType = 'L')
    {
        currCells.emplace_back(cells[2][2]);
        currCells.emplace_back(cells[3][0]);
        currCells.emplace_back(cells[3][1]);
        currCells.emplace_back(cells[3][2]);
    }
    else if (blockType = 'O')
    {
        currCells.emplace_back(cells[2][0]);
        currCells.emplace_back(cells[2][1]);
        currCells.emplace_back(cells[3][0]);
        currCells.emplace_back(cells[3][1]);
    }
    else if (blockType = 'S')
    {
        currCells.emplace_back(cells[2][1]);
        currCells.emplace_back(cells[2][2]);
        currCells.emplace_back(cells[3][0]);
        currCells.emplace_back(cells[3][1]);
    }
    else if (blockType = 'Z')
    {
        currCells.emplace_back(cells[2][0]);
        currCells.emplace_back(cells[2][1]);
        currCells.emplace_back(cells[3][1]);
        currCells.emplace_back(cells[3][2]);
    }
    else if (blockType = 'Z')
    {
        currCells.emplace_back(cells[2][0]);
        currCells.emplace_back(cells[2][1]);
        currCells.emplace_back(cells[2][2]);
        currCells.emplace_back(cells[3][1]);
    }
    for (auto cell : currCells)
    {
        if (cell->getChar(false) != ' ')
        {
            over = true;
            return;
        }
    }
    Block *curr = new Block{currCells[0], currCells[1], currCells[3], currCells[4], 4, level, blockType};
    for (auto cell : currCells)
    {
        cell->setChar(blockType);
        cell->setBlock(curr);
    }
    currBlock = curr;
}

void Board::IJL(char blockType)
{
    Board::setCurrBlock(blockType);
}

void Board::update()
{
    for (int row = 2; row < 12; ++row)
    {
        for (int col = 2; col < 9; ++col)
        {
            cells[row][col]->setIsBlind(true);
        }
    }
}

void Board::addstar()
{
    const int centralCol = 5;
    int availableRow = 3;
    while (cells[availableRow][centralCol]->getChar(false) == ' ')
    {
        ++availableRow;
    }
    --availableRow;
    Block *star = new StarBlock{cells[availableRow][centralCol], nullptr, nullptr, nullptr, 1, level, '*'};
    cells[availableRow][centralCol]->setChar('*');
    cells[availableRow][centralCol]->setBlock(star);
    blockCount = 0;
}
