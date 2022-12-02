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

Board::Board(int level, bool seedBool, unsigned int seed, std::string L0File)
    : level{level}, score{0}, blockCount{0}, isBlind{false}, isHeavy{false}, isForce{false}, over{false},
      seedBool{seedBool}, seed{seed}, L0File{L0File}
{
    std::vector<std::vector<Cell *>> cells(rows, std::vector<Cell *>(cols, nullptr));
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            cells[i][j] = new Cell{' ', j, i};
        }
    }
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            // check if the cell is at the first row
            if (cells[i][j]->getY() != 0)
            {
                cells[i][j]->setNeighbour('t', cells[i - 1][j]);
            }
            // check if the cell is at the last row
            if (cells[i][j]->getY() != rows - 1)
            {
                cells[i][j]->setNeighbour('b', cells[i + 1][j]);
            }
            // check if the cell is at the leftmost col
            if (cells[i][j]->getX() != 0)
            {
                cells[i][j]->setNeighbour('l', cells[i][j - 1]);
            }
            // check if the cell is at the rightmost col
            if (cells[i][j]->getX() != cols - 1)
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
        tempLevel->setL0File(L0File);
        
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
    nextBlock = currLevel->CreateNextBlock();
    char blockType = nextBlock->getBlockType();
    setCurrBlock(blockType);
    delete nextBlock;
    // then get another next block as nextBlock
    nextBlock = currLevel->CreateNextBlock();
    this->nextBlock = nextBlock;
}

Board::~Board() {
    delete currBlock;
    delete nextBlock;
    delete currLevel;
    for (auto it: cells) {
        for (auto it2: it) {
            delete it2;
        }
    }
}

bool Board::right(int mult)
{
    bool success = currBlock->right();
    if (mult > 1)
    {
        for (int i = 1; i < mult; i++)
        {
            currBlock->right();
        }
    }
    if (success && isHeavy)
    {
        for (int i = 0; i < 2; i++)
            if (!currBlock->down())
            {
                return true;
            }
    }
    return false;
}

bool Board::left(int mult)
{
    bool success = currBlock->left();
    if (mult > 1)
    {
        for (int i = 1; i < mult; i++)
        {
            currBlock->left();
        }
    }
    if (success && isHeavy)
    {

        for (int i = 0; i < 2; i++)
            if (!currBlock->down())
            {
                return true;
            }
    }
    return false;
}

bool Board::down()
{
    return currBlock->down();
}

bool Board::drop()
{
    bool prompt = false;
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
        prompt = true;
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
        addstar(); // bool for losing condition
    }

    // set current block to next block, delete the old next block, and generate a new next block
    bool over = !setCurrBlock(nextBlock->getBlockType());
    delete (nextBlock);
    over = over || checkRowClear(3);
    nextBlock = currLevel->CreateNextBlock();
    return prompt;
}

void Board::rotateHelper(bool rectangleType, bool horizontal, std::vector<int> rowsOfOriginal, std::vector<int> colsOfOriginal, std::vector<int> rowsOfDestination, std::vector<int> colsOfDestination, char blockType) {
    std::vector<int> realRotateRows;
    std::vector<int> realRotateCols;
    // if the block is 2*3
    if (rectangleType) {
        for (int i = 0; i < 6; ++i) {
            // check for out of bound. If it is out of bound, then we can't rotate, so do nothing
            if (rowsOfOriginal[i] < 0 || rowsOfOriginal[i] > 17 || rowsOfDestination[i] < 0 || rowsOfDestination[i] > 17 || colsOfOriginal[i] < 0 || colsOfOriginal[i] > 10 || colsOfDestination[i] < 0 || colsOfDestination[i] > 10) {
                return;
            }
        }

        for (int i = 0; i < 6; ++i) {
            // search for all 4 rotating cells
            if (cells[rowsOfOriginal[i]][colsOfOriginal[i]]->getBlock() == currBlock) {
                realRotateRows.emplace_back(rowsOfDestination[i]);
                realRotateCols.emplace_back(colsOfDestination[i]);
            }
        }
    } else { // if the block is 1*4
        for (int i = 0; i < 4; ++i) {
            // check for out of bound. If it is out of bound, then we can't rotate, so do nothing
            if (rowsOfOriginal[i] < 0 || rowsOfOriginal[i] > 17 || rowsOfDestination[i] < 0 || rowsOfDestination[i] > 17 || colsOfOriginal[i] < 0 || colsOfOriginal[i] > 10 || colsOfDestination[i] < 0 || colsOfDestination[i] > 10) {
                return;
            }
        }
        realRotateRows = rowsOfDestination;
        realRotateCols = colsOfDestination;
    }

    for (int i = 0; i < 4; ++i) {
        // if the resulting cell is not empty and is not one of the current block's cell, it means the destination is occupied, hence do nothing
        if ((cells[realRotateRows[i]][realRotateCols[i]]->getChar(false) != ' ') && (cells[realRotateRows[i]][realRotateCols[i]]->getBlock() != currBlock)) {
            return;
        }
    }

    // get the components from the current block for replacement
    std::vector<Cell *> components = currBlock->getComponents();
    int minRow = 18;
    int minCol = 12;
    // clear all cells in current block
    for (int i = 0; i < 4; ++i) {
        components[i]->setChar(' ');
        components[i]->setBlock(nullptr);
    }
    // replace cells in current block
    for (int i = 0; i < 4; ++i) {
        // initialize and assign new cells
        cells[realRotateRows[i]][realRotateCols[i]]->setChar(blockType);
        cells[realRotateRows[i]][realRotateCols[i]]->setBlock(currBlock);
        // replace cell
        components[i] = cells[realRotateRows[i]][realRotateCols[i]];
        // update the minimum row and column
        if (realRotateRows[i] < minRow) {minRow = realRotateRows[i];}
        if (realRotateCols[i] < minCol) {minCol = realRotateCols[i];}
    }
    // update the current block with new elements
    currBlock->setComponents(components);
    currBlock->setHorizontal(!horizontal);
    currBlock->setTopLeftRow(minRow);
    currBlock->setTopLeftCol(minCol);
}

void Board::rotate(bool clockwise)
{
    char blockType = currBlock->getBlockType();
    bool horizontal = currBlock->getHorizontal();
    // TopLeftRow and TopLeftCol locates the top left cell of the rectangle
    int tlRow = currBlock->getTopLeftRow();
    int tlCol = currBlock->getTopLeftCol();
    std::vector<std::pair<int, int>> Original;
    std::vector<std::pair<int, int>> Desination;
    std::vector<int> rowsOfOriginal;
    std::vector<int> colsOfOriginal;
    std::vector<int> rowsOfDestination;
    std::vector<int> colsOfDestination;
    std::vector<Cell *> components = currBlock->getComponents();
    // if the rectangle is 2*3
    if (blockType == 'J' || blockType == 'L' || blockType == 'S' || blockType == 'Z' || blockType == 'T')
    {
        if (horizontal)
        {
            rowsOfOriginal = std::vector<int>{tlRow, tlRow, tlRow, tlRow + 1, tlRow + 1, tlRow + 1};
            colsOfOriginal = std::vector<int>{tlCol, tlCol + 1, tlCol + 2, tlCol, tlCol + 1, tlCol + 2};
            if (clockwise)
            {
                rowsOfDestination = std::vector<int>{rowsOfOriginal[0]-1, rowsOfOriginal[1], rowsOfOriginal[2]+1, rowsOfOriginal[3]-2, rowsOfOriginal[4]-1, rowsOfOriginal[5]};
                colsOfDestination = std::vector<int>{colsOfOriginal[0]+1, colsOfOriginal[1], colsOfOriginal[2]-1, colsOfOriginal[3], colsOfOriginal[4]-1, colsOfOriginal[5]-2};
            }
            else
            {
                rowsOfDestination = std::vector<int>{rowsOfOriginal[0]+1, rowsOfOriginal[1], rowsOfOriginal[2]-1, rowsOfOriginal[3], rowsOfOriginal[4]-1, rowsOfOriginal[5]-2};
                colsOfDestination = std::vector<int>{colsOfOriginal[0], colsOfOriginal[1]-1, colsOfOriginal[2]-2, colsOfOriginal[3]+1, colsOfOriginal[4], colsOfOriginal[5]-1};
            }
        }
        else
        {
            rowsOfOriginal = std::vector<int>{tlRow, tlRow+1, tlRow+2, tlRow, tlRow+1, tlRow+2};
            colsOfOriginal = std::vector<int>{tlCol, tlCol, tlCol, tlCol+1, tlCol+1, tlCol+1};
            if (clockwise)
            {
                rowsOfDestination = std::vector<int>{rowsOfOriginal[0]+1, rowsOfOriginal[1], rowsOfOriginal[2]-1, rowsOfOriginal[3]+2, rowsOfOriginal[4]+1, rowsOfOriginal[5]};
                colsOfDestination = std::vector<int>{colsOfOriginal[0]+2, colsOfOriginal[1]+1, colsOfOriginal[2], colsOfOriginal[3]+1, colsOfOriginal[4], colsOfOriginal[5]-1};
            }
            else
            {
                rowsOfDestination = std::vector<int>{rowsOfOriginal[0]+2, rowsOfOriginal[1]+1, rowsOfOriginal[2], rowsOfOriginal[3]+1, rowsOfOriginal[4], rowsOfOriginal[5]-1};
                colsOfDestination = std::vector<int>{colsOfOriginal[0], colsOfOriginal[1]+1, colsOfOriginal[2]+2, colsOfOriginal[3]-1, colsOfOriginal[4], colsOfOriginal[5]+1};
            }
        }
        rotateHelper(true, horizontal, rowsOfOriginal, colsOfOriginal, rowsOfDestination, colsOfDestination, blockType);
    }
    // if the rectangle is 1*4
    else if (blockType == 'I')
    {
        if (horizontal)
        {
            rowsOfOriginal = std::vector<int>{tlRow, tlRow, tlRow, tlRow};
            colsOfOriginal = std::vector<int>{tlCol, tlCol + 1, tlCol + 2, tlCol + 3};
            if (clockwise)
            {
                rowsOfDestination = std::vector<int>{rowsOfOriginal[0]-3, rowsOfOriginal[1]-2, rowsOfOriginal[2]-1, rowsOfOriginal[3]};
                colsOfDestination = std::vector<int>{colsOfOriginal[0], colsOfOriginal[1]-1, colsOfOriginal[2]-2, colsOfOriginal[3]-3};
            }
            else
            {
                rowsOfDestination = std::vector<int>{rowsOfOriginal[0], rowsOfOriginal[1]-1, rowsOfOriginal[2]-2, rowsOfOriginal[3]-3};
                colsOfDestination = std::vector<int>{colsOfOriginal[0], colsOfOriginal[1]-1, colsOfOriginal[2]-2, colsOfOriginal[3]-3};
            }
        }
        else
        {
            rowsOfOriginal = std::vector<int>{tlRow, tlRow + 1, tlRow + 2, tlRow + 3};
            colsOfOriginal = std::vector<int>{tlCol, tlCol, tlCol, tlCol};
            if (clockwise)
            {
                rowsOfDestination = std::vector<int>{rowsOfOriginal[0]+3, rowsOfOriginal[1]+2, rowsOfOriginal[2]+1, rowsOfOriginal[3]};
                colsOfDestination = std::vector<int>{colsOfOriginal[0]+3, colsOfOriginal[1]+2, colsOfOriginal[2]+1, colsOfOriginal[3]};
            }
            else
            {
                rowsOfDestination = std::vector<int>{rowsOfOriginal[0]+3, rowsOfOriginal[1]+2, rowsOfOriginal[2]+1, rowsOfOriginal[3]};
                colsOfDestination = std::vector<int>{colsOfOriginal[0], colsOfOriginal[1]+1, colsOfOriginal[2]+2, colsOfOriginal[3]+3};
            }
        }
        rotateHelper(false, horizontal, rowsOfOriginal, colsOfOriginal, rowsOfDestination, colsOfDestination, blockType);
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
            isHeavy = true;
            currLevel = new Level3{seedBool, seed, cells};
        }
        else if (level == 4)
        {
            isHeavy = true;
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
    if (clear > 0)
    {

        score += (level + clear) * (level + clear);
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
        curr = new IBlock{currCells[0], currCells[1], currCells[2], currCells[3], 4, level, blockType};
    }
    else if (blockType == 'J')
    {
        currCells.emplace_back(cells[2][0]);
        currCells.emplace_back(cells[3][0]);
        currCells.emplace_back(cells[3][1]);
        currCells.emplace_back(cells[3][2]);
        if (!checkForCurrBlock(currCells))
        {
            return false;
        }
        curr = new JBlock{currCells[0], currCells[1], currCells[2], currCells[3], 4, level, blockType};
    }
    else if (blockType == 'L')
    {
        currCells.emplace_back(cells[2][2]);
        currCells.emplace_back(cells[3][0]);
        currCells.emplace_back(cells[3][1]);
        currCells.emplace_back(cells[3][2]);
        if (!checkForCurrBlock(currCells))
        {
            return false;
        }
        curr = new LBlock{currCells[0], currCells[1], currCells[2], currCells[3], 4, level, blockType};
    }
    else if (blockType == 'O')
    {
        currCells.emplace_back(cells[2][0]);
        currCells.emplace_back(cells[2][1]);
        currCells.emplace_back(cells[3][0]);
        currCells.emplace_back(cells[3][1]);
        if (!checkForCurrBlock(currCells))
        {
            return false;
        }
        curr = new OBlock{currCells[0], currCells[1], currCells[2], currCells[3], 4, level, blockType};
    }
    else if (blockType == 'S')
    {
        currCells.emplace_back(cells[2][1]);
        currCells.emplace_back(cells[2][2]);
        currCells.emplace_back(cells[3][0]);
        currCells.emplace_back(cells[3][1]);
        if (!checkForCurrBlock(currCells))
        {
            return false;
        }
        curr = new SBlock{currCells[0], currCells[1], currCells[2], currCells[3], 4, level, blockType};
    }
    else if (blockType == 'Z')
    {
        currCells.emplace_back(cells[2][0]);
        currCells.emplace_back(cells[2][1]);
        currCells.emplace_back(cells[3][1]);
        currCells.emplace_back(cells[3][2]);
        if (!checkForCurrBlock(currCells))
        {
            return false;
        }
        curr = new ZBlock{currCells[0], currCells[1], currCells[2], currCells[3], 4, level, blockType};
    }
    else if (blockType == 'T')
    {
        currCells.emplace_back(cells[2][0]);
        currCells.emplace_back(cells[2][1]);
        currCells.emplace_back(cells[2][2]);
        currCells.emplace_back(cells[3][1]);
        if (!checkForCurrBlock(currCells))
        {
            return false;
        }
        curr = new TBlock{currCells[0], currCells[1], currCells[2], currCells[3], 4, level, blockType};
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
    delete currBlock;
    setCurrBlock(blockType);
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
    int availableRow = 2;
    while (cells[availableRow][centralCol]->getChar(false) == ' ')
    {
        ++availableRow;
        if (availableRow == 18)
        {
            break;
        }
    }
    --availableRow;
    // create the star block and update that cell
    Block *star = new StarBlock{cells[availableRow][centralCol], nullptr, nullptr, nullptr, 1, level, '*'};
    cells[availableRow][centralCol]->setChar('*');
    cells[availableRow][centralCol]->setBlock(star);
}

void Board::setL0File(std::string L0File)
{
    if (level == 0)
    {
        currLevel->setL0File(L0File);
    }
}

void Board::setNoRandom(bool noRandom, std::string noRandomFile)
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


void Board::setName(std::string name) {
    playerName = name;
} 

std::string Board::getName() {
    return playerName;
}

