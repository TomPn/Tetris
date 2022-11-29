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

Board::Board(int level, bool seedBool, unsigned int seed)
    : level{level}, score{0}, blockCount{0}, isBlind{false}, isHeavy{false}, isForce{false}, over{false},
      seedBool{seedBool}, seed{seed}
{
    std::vector<std::vector<Cell *>> cells;
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
            if (cells[i][j]->getX() != 0)
            {
                cells[i][j]->setNeighbour('t', cells[i - 1][j]);
            }
            else if (cells[i][j]->getX() != rows - 1)
            {
                cells[i][j]->setNeighbour('b', cells[i + 1][j]);
            }
            else if (cells[i][j]->getY() != 0)
            {
                cells[i][j]->setNeighbour('l', cells[i][j - 1]);
            }
            else if (cells[i][j]->getY() != cols - 1)
            {
                cells[i][j]->setNeighbour('r', cells[i][j + 1]);
            }
        }
    }
    this->cells = cells;

    // initialize currLevel
    Level *tempLevel;
    if (level == 0)
    {
        tempLevel = new Level0{seedBool, seed, cells};
    }
    else if (level == 1)
    {
        tempLevel = new Level1{seedBool, seed, cells};
    }
    else if (level == 2)
    {
        tempLevel = new Level2{seedBool, seed, cells};
    }
    else if (level == 3)
    {
        tempLevel = new Level3{seedBool, seed, cells};
    }
    else if (level == 4)
    {
        tempLevel = new Level4{seedBool, seed, cells};
    }

    currLevel = tempLevel;
    // get a next block and set it as currBlock
    Block *nextBlock = currLevel->CreateNextBlock();
    char blockType = nextBlock->getBlockType();
    setCurrBlock(blockType);
    delete nextBlock;
    // then get another next block as nextBlock
    Block *nextBlock = currLevel->CreateNextBlock();
    this->nextBlock = nextBlock;
}

void Board::right(int mult)
{
    for (int i = 0; i < mult; i++)
    {
        currBlock->right(isHeavy);
    }
}

void Board::left(int mult)
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
    // once drop, the Force and Blind is completed and should be reset to false
    isForce = false;
    isBlind = false;

    // keep going down until it returns false(that means currBlock is already at the bottom)
    while (down())
    {
    }

    int clearResult = checkClear();
    // if more than two rows are cleared, trigger special action and clear blockCount
    if (clearResult >= 2)
    {
        setTrigger(true);
        blockCount = 0;
    }
    // if no row is cleared, increment blockCount, which is the number of block without clearing at least one row(see Level 4)
    if (clearResult == 0)
    {
        blockCount += 1;
    }
    // otherwise, just clear blockCount
    else
    {
        blockCount = 0;
    }
    // if it's level 4, and blockCount is 5, 10 ,15, etc, then drop a star block to the central col
    if (blockCount % 5 == 0 && blockCount != 0 && level == 4)
    {
        addstar();
    }

    // set current block to next block, delete the old next block, and generate a new next block
    bool over = setCurrBlock(nextBlock->getBlockType());
    delete (nextBlock);
    over = over || checkRowClear(3);

    nextBlock = currLevel->CreateNextBlock();
}

// checks if rotated cell is valid
bool Board::checkForRotate(Cell *cellPtr, int newRow, int newCol)
{
    // cellPtr is the original cell, newRow and newCol locates the desination
    // not valid if out of bound
    if (newRow > 17 || newRow < 0 || newCol > 10 || newCol < 0)
    {
        return false;
    }
    // not valid if the cellPtr is a cell of currBlock and the desination is occupied by a block that is not currBlock
    if (!(currBlock->member(cellPtr) && (cells[newRow][newCol]->getChar(false) != ' ') || currBlock->member(cells[newRow][newCol])))
    {
        return false;
    }
    // else return true
    return true;
}

// move the cellPtr to its desination
void Board::moveForRotate(Cell *cellPtr, int newRow, int newCol)
{
    // update the desination's char and myBlock
    cells[newRow][newCol]->setChar(cellPtr->getChar(false));
    cells[newRow][newCol]->setBlock(cellPtr->getBlock());
    // change the original cell to a blank cell
    cellPtr->setChar(' ');
    cellPtr->setBlock(nullptr);
}

void Board::rotate(bool clockwise)
{
    char blockType = currBlock->getBlockType();
    bool horizontal = currBlock->getHorizontal();
    // TopLeftRow and TopLeftCol locates the top left cell of the rectangle
    int tlRow = currBlock->getTopLeftRow();
    int tlCol = currBlock->getTopLeftCol();
    // valid checks if the rotated block are valid
    bool valid = true;

    // if the rectangle is 2*3
    if (blockType == 'J' || blockType == 'L' || blockType == 'S' || blockType == 'Z' || blockType == 'T')
    {
        if (horizontal && clockwise)
        {
            // check if each cell is valid for being rotated
            valid = valid && checkForRotate(cells[tlRow][tlCol], tlRow - 1, tlCol + 1);
            valid = valid && checkForRotate(cells[tlRow + 1][tlCol], tlRow - 1, tlCol);
            // if valid, move the cells to their desination and update the coordinate of the top left cell and the horizontal
            if (valid)
            {
                moveForRotate(cells[tlRow][tlCol], tlRow - 1, tlCol + 1);
                moveForRotate(cells[tlRow + 1][tlCol], tlRow - 1, tlCol);
                currBlock->setTopLeftRow(tlRow - 1);
                currBlock->setTopLeftCol(tlCol);
                currBlock->setHorizontal(false);
            }
            // valid = valid && checkForRotate(cells[tlRow][tlCol + 1], tlRow, tlCol + 1);
            // valid = valid && checkForRotate(cells[tlRow + 1][tlCol + 1], tlRow, tlCol);
            // valid = valid && checkForRotate(cells[tlRow][tlCol + 2], tlRow + 1, tlCol + 1);
            // valid = valid && checkForRotate(cells[tlRow + 1][tlCol + 2], tlRow + 1, tlCol);
        }
        else if (horizontal && !clockwise)
        {
            valid = valid && checkForRotate(cells[tlRow][tlCol + 2], tlRow - 1, tlCol);
            valid = valid && checkForRotate(cells[tlRow + 1][tlCol + 2], tlRow - 1, tlCol + 1);
            if (valid)
            {
                moveForRotate(cells[tlRow][tlCol + 2], tlRow - 1, tlCol);
                moveForRotate(cells[tlRow + 1][tlCol + 2], tlRow - 1, tlCol + 1);
                currBlock->setTopLeftRow(tlRow - 1);
                currBlock->setTopLeftCol(tlCol);
                currBlock->setHorizontal(false);
            }
            // valid = valid && checkForRotate(cells[tlRow][tlCol + 2], tlRow, tlCol);
            // valid = valid && checkForRotate(cells[tlRow + 1][tlCol + 2], tlRow, tlCol + 1);
            // valid = valid && checkForRotate(cells[tlRow][tlCol + 2], tlRow + 1, tlCol);
            // valid = valid && checkForRotate(cells[tlRow + 1][tlCol + 2], tlRow + 1, tlCol + 1);
        }
        else if (!horizontal && clockwise)
        {
            valid = valid && checkForRotate(cells[tlRow][tlCol], tlRow + 1, tlCol + 2);
            valid = valid && checkForRotate(cells[tlRow][tlCol + 1], tlRow + 2, tlCol + 1);
            if (valid)
            {
                moveForRotate(cells[tlRow][tlCol], tlRow + 1, tlCol + 2);
                moveForRotate(cells[tlRow][tlCol + 1], tlRow + 2, tlCol + 1);
                currBlock->setTopLeftRow(tlRow + 1);
                currBlock->setTopLeftCol(tlCol);
                currBlock->setHorizontal(true);
            }
        }
        else if (!horizontal && !clockwise)
        {
            valid = valid && checkForRotate(cells[tlRow][tlCol], tlRow + 2, tlCol - 1);
            valid = valid && checkForRotate(cells[tlRow][tlCol + 1], tlRow + 1, tlCol - 1);
            if (valid)
            {
                moveForRotate(cells[tlRow][tlCol], tlRow + 2, tlCol - 1);
                moveForRotate(cells[tlRow][tlCol + 1], tlRow + 1, tlCol - 1);
                currBlock->setTopLeftRow(tlRow + 1);
                currBlock->setTopLeftCol(tlCol - 1);
                currBlock->setHorizontal(true);
            }
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
                currBlock->setTopLeftRow(tlRow - 3);
                currBlock->setTopLeftCol(tlCol);
                currBlock->setHorizontal(false);
            }
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
                currBlock->setTopLeftRow(tlRow - 3);
                currBlock->setTopLeftCol(tlCol);
                currBlock->setHorizontal(false);
            }
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
                currBlock->setTopLeftRow(tlRow + 3);
                currBlock->setTopLeftCol(tlCol);
                currBlock->setHorizontal(true);
            }
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
                currBlock->setTopLeftRow(tlRow + 3);
                currBlock->setTopLeftCol(tlCol - 3);
                currBlock->setHorizontal(true);
            }
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
            currLevel = new Level1{seedBool, seed, cells};
        }
        else if (level == 2)
        {
            currLevel = new Level2{seedBool, seed, cells};
        }
        else if (level == 3)
        {
            currLevel = new Level3{seedBool, seed, cells};
        }
        else if (level == 4)
        {
            currLevel = new Level4{seedBool, seed, cells};
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
            currLevel = new Level1{seedBool, seed, cells};
        }
        else if (level == 1)
        {
            currLevel = new Level2{seedBool, seed, cells};
        }
        else if (level == 2)
        {
            currLevel = new Level3{seedBool, seed, cells};
        }
        else if (level == 3)
        {
            currLevel = new Level4{seedBool, seed, cells};
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

bool Board::checkRowClear(int row)
{
    for (int col = 0; col < cols; col++)
    {
        // if we reach a cell that is not occupied, that means the row should not be cleared
        if (cells[row][col]->getBlock() == nullptr && cells[row][col]->getChar(false) == ' ')
        {
            return false;
        }
    }
    return true;
}

int Board::checkClear()
{
    // clear records the number of rows that is cleared
    int clear = 0;
    // rowClear indicates whether a row should be cleared
    bool rowClear;

    // for each row(except for the "Next"), check if the row should be clear
    for (int i = 3; i < rows - 2; i++) // HERE
    {
        rowClear = checkRowClear(i);
        // if the row should be cleared
        if (rowClear)
        {
            clear += 1;
            for (int i2 = i; i2 > 0; i2--)
            {
                for (int j2 = 0; j2 < cols; j2++)
                {
                    // if we're at the row that should be cleared
                    if (i2 == i)
                    {
                        // for each cell, identify its block
                        Block *currBlock = cells[i2][j2]->getBlock();
                        // if that's the last living cell in that block, delete that block
                        if (currBlock->getAlive() == 1)
                        {
                            score += (currBlock->getLevel() + 1) * (currBlock->getLevel() + 1);
                            delete currBlock;
                            cells[i2][j2]->setBlock(nullptr);
                        }
                        else
                        // otherwise if that's not the last living cell, just decrease alive by 1
                        {
                            currBlock->setAlive(currBlock->getAlive() - 1);
                        }
                        // set the cell to blank
                        cells[i2][j2]->setChar(' ');
                    }
                    // for each cell that is above the row that should be cleared(except)
                    if (i2 != 0) // should it be 3?
                    {            // just move them down by 1 cell
                        cells[i2][j2]->setBlock(cells[i2 - 1][j2]->getBlock());
                        cells[i2][j2]->setChar(cells[i2 - 1][j2]->getChar(false));
                    }
                }
            }
        }
    }
    // return
    return clear;
}

bool Board::checkForCurrBlock(std::vector<Cell *> currCells)
{
    for (auto cell : currCells)
    {
        if (cell->getChar(false) != ' ')
        {
            over = true;
            return false;
        }
    }
    return true;
}

bool Board::setCurrBlock(char blockType)
{
    std::vector<Cell *> currCells;
    Block *curr;
    if (blockType == 'I')
    {
        currCells.emplace_back(cells[3][0]);
        currCells.emplace_back(cells[3][1]);
        currCells.emplace_back(cells[3][2]);
        currCells.emplace_back(cells[3][3]);
        if (!checkForCurrBlock(currCells))
        {
            return false;
        }
        curr = new IBlock{currCells[0], currCells[1], currCells[3], currCells[4], 4, level, blockType};
    }
    else if (blockType = 'J')
    {
        currCells.emplace_back(cells[2][0]);
        currCells.emplace_back(cells[3][0]);
        currCells.emplace_back(cells[3][1]);
        currCells.emplace_back(cells[3][2]);
        if (!checkForCurrBlock(currCells))
        {
            return false;
        }
        curr = new JBlock{currCells[0], currCells[1], currCells[3], currCells[4], 4, level, blockType};
    }
    else if (blockType = 'L')
    {
        currCells.emplace_back(cells[2][2]);
        currCells.emplace_back(cells[3][0]);
        currCells.emplace_back(cells[3][1]);
        currCells.emplace_back(cells[3][2]);
        if (!checkForCurrBlock(currCells))
        {
            return false;
        }
        curr = new LBlock{currCells[0], currCells[1], currCells[3], currCells[4], 4, level, blockType};
    }
    else if (blockType = 'O')
    {
        currCells.emplace_back(cells[2][0]);
        currCells.emplace_back(cells[2][1]);
        currCells.emplace_back(cells[3][0]);
        currCells.emplace_back(cells[3][1]);
        if (!checkForCurrBlock(currCells))
        {
            return false;
        }
        curr = new OBlock{currCells[0], currCells[1], currCells[3], currCells[4], 4, level, blockType};
    }
    else if (blockType = 'S')
    {
        currCells.emplace_back(cells[2][1]);
        currCells.emplace_back(cells[2][2]);
        currCells.emplace_back(cells[3][0]);
        currCells.emplace_back(cells[3][1]);
        if (!checkForCurrBlock(currCells))
        {
            return false;
        }
        curr = new SBlock{currCells[0], currCells[1], currCells[3], currCells[4], 4, level, blockType};
    }
    else if (blockType = 'Z')
    {
        currCells.emplace_back(cells[2][0]);
        currCells.emplace_back(cells[2][1]);
        currCells.emplace_back(cells[3][1]);
        currCells.emplace_back(cells[3][2]);
        if (!checkForCurrBlock(currCells))
        {
            return false;
        }
        curr = new ZBlock{currCells[0], currCells[1], currCells[3], currCells[4], 4, level, blockType};
    }
    else if (blockType = 'T')
    {
        currCells.emplace_back(cells[2][0]);
        currCells.emplace_back(cells[2][1]);
        currCells.emplace_back(cells[2][2]);
        currCells.emplace_back(cells[3][1]);
        if (!checkForCurrBlock(currCells))
        {
            return false;
        }
        curr = new TBlock{currCells[0], currCells[1], currCells[3], currCells[4], 4, level, blockType};
    }

    for (auto cell : currCells)
    {
        cell->setChar(blockType);
        cell->setBlock(curr);
    }
    currBlock = curr;
    return true;
}

void Board::IJL(char blockType)
{
    Board::setCurrBlock(blockType);
}

// update for blind
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

// add star for level 4
void Board::addstar()
{
    const int centralCol = 5;
    // find out where the star block should locate(should be located on the downmost cell on the central col)
    int availableRow = 3;
    while (cells[availableRow][centralCol]->getChar(false) == ' ')
    {
        ++availableRow;
    }
    --availableRow;
    // create the star block and update that cell
    Block *star = new StarBlock{cells[availableRow][centralCol], nullptr, nullptr, nullptr, 1, level, '*'};
    cells[availableRow][centralCol]->setChar('*');
    cells[availableRow][centralCol]->setBlock(star);
}

void Board::setL0File(std::string L0File = "")
{
    if (level == 0)
    {
        currLevel->setL0File(L0File);
    }
}

void Board::setNoRandom(bool noRandom, std::string noRandomFile = "")
{
    if (level == 3 || level == 4)
    {
        currLevel->setNoRandom(noRandom, noRandomFile);
    }
}

bool Board::getChange(int row, int col)
{
    return cells[row][col]->getChange();
}

bool Board::getOver()
{
    return over;
}