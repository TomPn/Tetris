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
#include <iostream>
using std::cout;
using std::endl;
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
    std::cerr << blockCount << std::endl;
    // if it's level 4, and blockCount is 5, 10 ,15, etc, then drop a star block to the central col
    if (blockCount % 5 == 0 && blockCount != 0 && level == 4)
    {
        addstar(); // bool for losing condition
    }

    // set current block to next block, delete the old next block, and generate a new next block
    bool over = setCurrBlock(nextBlock->getBlockType());
    delete (nextBlock);
    over = over || checkRowClear(3);

    nextBlock = currLevel->CreateNextBlock();
    return prompt;
}

//
bool Board::checkForRotate(Cell *cellPtr, int newRow, int newCol, std::vector<int> &rowsOfBlockDesination, std::vector<int> &colsOfBlockDesination)
{
    if (newRow > 17 || newRow < 0 || newCol > 10 || newCol < 0)
    {
        return false; // can't be rotated
    }

    if (currBlock->member(cellPtr) && cells[newRow][newCol]->getBlock() != currBlock && cells[newRow][newCol]->getBlock() != nullptr)
    {
        return false;
    }

    if (currBlock->member(cellPtr))
    {
        // std::cerr << "des rol: " << newRow << "  des col: " << newCol << std::endl;
        rowsOfBlockDesination.emplace_back(newRow);
        colsOfBlockDesination.emplace_back(newCol);
    }

    return true;
}

void Board::moveForRotate(Cell *cellPtr, int newRow, int newCol, std::vector<int> &rowsOfBlockDesination, std::vector<int> &colsOfBlockDesination, char originalChar, Block *originalBlock)
{
    std::cerr << "before:" << endl;
    if (cells[newRow][newCol]->getBlock() == currBlock)
    {
        // std::cerr << newRow << "   " << newCol << std::endl;
    }
    if (cells[newRow][newCol]->getBlock() == nullptr)
    {
        // std::cerr << newRow << "              " << newCol << std::endl;
    }

    // std::cerr << "new row: " << newRow << "new col: " << newCol << std::endl;
    //   cellPtr is the original cell, newRow and newCol locates the desination
    //   not valid if out of bound

    // if the original cell is blank
    if (!currBlock->member(cellPtr))
    {
        return; // do nothing
    }
    else
    {
        // std::cerr << "N blank" << std::endl;
        std::vector<Cell *> components = currBlock->getComponents();
        bool protect = false;
        for (int i = 0; i < 6; ++i)
        {

            // std::cerr << "cellPtr rol: " << cellPtr->getY() << "  cellPtr col: " << cellPtr->getX() << std::endl;

            if (rowsOfBlockDesination[i] == cellPtr->getY() && colsOfBlockDesination[i] == cellPtr->getX())
            {
                // std::cerr << "des rol: " << rowsOfBlockDesination[i] << "  des col: " << colsOfBlockDesination[i] << std::endl;
                protect = true;
                break;
            }
        }

        // the original cell and the desination cell are both pairs of the current block
        if (cells[newRow][newCol]->getBlock() == currBlock)
        {
            if (!protect)
            {
                cellPtr->setChar(' ');
                cellPtr->setBlock(nullptr);
            }
            // std::cerr << "rol now: " << cellPtr->getY() << "  col now: " << cellPtr->getX() << std::endl;
            // for (int i = 0; i < 4; ++i)
            // {

            //     if (components[i] == cellPtr)
            //     {

            //         // std::cerr << "rol before: " << cellPtr->getY() << "  col before: " << cellPtr->getX() << std::endl;
            //         std::cerr << "rol after: " << cells[newRow][newCol]->getY() << "  col after: " << cells[newRow][newCol]->getX() << std::endl;
            //         components[i] = cells[newRow][newCol];
            //         break;
            //     }
            // }
            // currBlock->setComponents(components);
        }
        // the original cell is a pair of the current block and the desination is blank
        else if (cells[newRow][newCol]->getBlock() == nullptr)
        {
            cells[newRow][newCol]->setChar(originalChar);
            cells[newRow][newCol]->setBlock(originalBlock);
            if (!protect)
            {
                // std::cerr << "protected rol: " << cellPtr->getY() << "  protected col: " << cellPtr->getX() << std::endl;
                cellPtr->setChar(' ');
                cellPtr->setBlock(nullptr);
            }
            // std::cerr << "rol now: " << cellPtr->getY() << "  col now: " << cellPtr->getX() << std::endl;
            // for (int i = 0; i < 4; ++i)
            // {
            //     if (components[i] == cellPtr)
            //     {
            //         std::cerr << "rol after: " << newRow << "  col after: " << newCol << std::endl;
            //         // std::cerr << "rol before: " << cellPtr->getY() << "  col before: " << cellPtr->getX() << std::endl;
            //         // std::cerr << "rol after: " << cells[newRow][newCol]->getY() << "  col after: " << cells[newRow][newCol]->getX() << std::endl;
            //         components[i] = cells[newRow][newCol];
            //         break;
            //     }
            // }
            // currBlock->setComponents(components);
        }
    }
    std::cerr << "after:" << endl;
    if (cells[newRow][newCol]->getBlock() == currBlock)
    {
        // std::cerr << newRow << "   " << newCol << std::endl;
    }
    if (cells[newRow][newCol]->getBlock() == nullptr)
    {
        // std::cerr << newRow << "              " << newCol << std::endl;
    }
}

void Board::rotateHelper(bool twoThree, bool horizontal, std::vector<std::pair<int, int>> Original, std::vector<std::pair<int, int>> Desination)
{
    bool valid = true;
    int minRow = 100;
    int minCol = 100;
    std::vector<int> rowsOfComponentsDesination;
    std::vector<int> colsOfComponentsDesination;
    std::vector<char> originalChar;
    std::vector<Block *> originalBlock;
    int range = 4;
    if (twoThree)
    {
        range = 6;
    }
    for (int i = 0; i < range; ++i)
    {
        if (cells[Desination[i].first][Desination[i].second]->getBlock() == currBlock)
        {
            // std::cerr << Desination[i].first << "   " << Desination[i].second << std::endl;
        }
    }
    for (int i = 0; i < range; ++i) // for (int i = range - 1; i >= 0; --i)
    {
        originalChar.emplace_back(cells[Original[i].first][Original[i].second]->getChar(false));
        originalBlock.emplace_back(cells[Original[i].first][Original[i].second]->getBlock());
    }
    for (int i = 0; i < range; ++i)
    {
        // std::cerr << originalChar[i] << std::endl;
    }
    for (int i = 0; i < range; ++i)
    {
        valid = valid && checkForRotate(cells[Original[i].first][Original[i].second], Desination[i].first, Desination[i].second, rowsOfComponentsDesination, colsOfComponentsDesination);
    }
    if (valid)
    {
        for (int i = 0; i < range; ++i)
        {
            moveForRotate(cells[Original[i].first][Original[i].second], Desination[i].first, Desination[i].second, rowsOfComponentsDesination, colsOfComponentsDesination, originalChar[i], originalBlock[i]);
            // std::cerr << "ori row: " << Original[i].first << "  ori col: " << Original[i].second << std::endl;
            // std::cerr << "des row: " << Desination[i].first << "  des col: " << Desination[i].second << std::endl;
            if (Desination[i].first < minRow)
            {
                minRow = Desination[i].first;
            }
            if (Desination[i].second < minCol)
            {
                minCol = Desination[i].second;
            }
            currBlock->setTopLeftRow(minRow);
            currBlock->setTopLeftCol(minCol);
            currBlock->setHorizontal(!horizontal);
        }
    }
    std::vector<Cell *> components;
    for (int i = 0; i < range; ++i)
    {
        if (cells[Desination[i].first][Desination[i].second]->getBlock() == currBlock)
        {
            // std::cerr << "count" << std::endl;
            components.emplace_back(cells[Desination[i].first][Desination[i].second]);
        }
    }
    currBlock->setComponents(components);
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
    std::vector<std::pair<int, int>> Original;
    std::vector<std::pair<int, int>> Desination;
    std::vector<int> rowsOfOriginal;
    std::vector<int> colsOfOriginal;
    std::vector<int> rowsOfDesination;
    std::vector<int> colsOfDesination;
    std::vector<Cell *> components = currBlock->getComponents();
    for (int i = 0; i < 4; ++i)
    {
        // std::cerr << "row: " << components[i]->getY() << "  col: " << components[i]->getX() << std::endl;
    }

    // std::cerr << "tlrow: " << tlRow << "  tlcol: " << tlCol << std::endl;
    // std::cerr << "horizontal: " << h << std::endl;
    //  if the rectangle is 2*3
    if (blockType == 'J' || blockType == 'L' || blockType == 'S' || blockType == 'Z' || blockType == 'T')
    {
        if (horizontal)
        {
            rowsOfOriginal = std::vector<int>{tlRow, tlRow, tlRow, tlRow + 1, tlRow + 1, tlRow + 1};
            colsOfOriginal = std::vector<int>{tlCol, tlCol + 1, tlCol + 2, tlCol, tlCol + 1, tlCol + 2};
            if (clockwise)
            {
                rowsOfDesination = std::vector<int>{tlRow - 1, tlRow, tlRow + 1, tlRow - 1, tlRow, tlRow + 1};
                colsOfDesination = std::vector<int>{tlCol + 1, tlCol + 1, tlCol + 1, tlCol, tlCol, tlCol};
            }
            else
            {
                rowsOfDesination = std::vector<int>{tlRow + 1, tlRow, tlRow - 1, tlRow + 1, tlRow, tlRow - 1};
                colsOfDesination = std::vector<int>{tlCol, tlCol, tlCol, tlCol + 1, tlCol + 1, tlCol + 1};
            }
        }
        else
        {
            rowsOfOriginal = std::vector<int>{tlRow, tlRow, tlRow + 1, tlRow + 1, tlRow + 2, tlRow + 2};
            colsOfOriginal = std::vector<int>{tlCol, tlCol + 1, tlCol, tlCol + 1, tlCol, tlCol + 1};
            if (clockwise)
            {
                rowsOfDesination = std::vector<int>{tlRow + 1, tlRow + 2, tlRow + 1, tlRow + 2, tlRow + 1, tlRow + 2};
                colsOfDesination = std::vector<int>{tlCol + 2, tlCol + 2, tlCol + 1, tlCol + 1, tlCol, tlCol};
            }
            else
            {
                rowsOfDesination = std::vector<int>{tlRow + 2, tlRow + 1, tlRow + 2, tlRow + 1, tlRow + 2, tlRow + 1};
                colsOfDesination = std::vector<int>{tlCol, tlCol, tlCol + 1, tlCol + 1, tlCol + 2, tlCol + 2};
            }
        }
        for (int i = 0; i < 6; ++i)
        {
            Original.emplace_back(std::make_pair(rowsOfOriginal[i], colsOfOriginal[i]));
            Desination.emplace_back(std::make_pair(rowsOfDesination[i], colsOfDesination[i]));
        }
        rotateHelper(true, horizontal, Original, Desination);
    }
    else if (blockType == 'I')
    {
        if (horizontal)
        {
            rowsOfOriginal = std::vector<int>{tlRow, tlRow, tlRow, tlRow};
            colsOfOriginal = std::vector<int>{tlCol, tlCol + 1, tlCol + 2, tlCol + 3};
            if (clockwise)
            {
                rowsOfDesination = std::vector<int>{tlRow - 3, tlRow - 2, tlRow - 1, tlRow};
                colsOfDesination = std::vector<int>{tlCol, tlCol, tlCol, tlCol};
            }
            else
            {
                rowsOfDesination = std::vector<int>{tlRow, tlRow - 1, tlRow - 2, tlRow - 3};
                colsOfDesination = std::vector<int>{tlCol, tlCol, tlCol, tlCol};
            }
        }
        else
        {
            rowsOfOriginal = std::vector<int>{tlRow, tlRow + 1, tlRow + 2, tlRow + 3};
            colsOfOriginal = std::vector<int>{tlCol, tlCol, tlCol, tlCol};
            if (clockwise)
            {
                rowsOfDesination = std::vector<int>{tlRow + 3, tlRow + 3, tlRow + 3, tlRow + 3};
                colsOfDesination = std::vector<int>{tlCol + 3, tlCol + 2, tlCol + 1, tlCol};
            }
            else
            {
                rowsOfDesination = std::vector<int>{tlRow + 3, tlRow + 3, tlRow + 3, tlRow + 3};
                colsOfDesination = std::vector<int>{tlCol, tlCol + 1, tlCol + 2, tlCol + 3};
            }
        }
        for (int i = 0; i < 4; ++i)
        {
            Original.emplace_back(std::make_pair(rowsOfOriginal[i], colsOfOriginal[i]));
            Desination.emplace_back(std::make_pair(rowsOfDesination[i], colsOfDesination[i]));
        }
        rotateHelper(false, horizontal, Original, Desination);
    }

    // std::cerr << "after " << std::endl;
    components = currBlock->getComponents();
    // std::cerr << components.size() << std::endl;
    for (int i = 0; i < 4; ++i)
    {
        // std::cerr << "row: " << components[i]->getY() << "  col: " << components[i]->getX() << std::endl;
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
            blockCount = 0;
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
