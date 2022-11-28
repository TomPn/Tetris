#include "board.h"
#include "block.h"
#include "cell.h"
#include "level.h"
#include <vector>

const int rows = 20;
const int cols = 11;

Board::Board(int level, int score, int blockCount, bool isBlind, bool isHeavy, bool isForce,
             Board *opponentBoard, Block *currBlock, Block *nextBlock, Level *currLevel) : level{level}, score{score}, blockCount{blockCount}, isBlind{isBlind}, isHeavy{isHeavy}, isForce{isForce},
                                                                                           opponentBoard{opponentBoard}, currBlock{currBlock}, nextBlock{nextBlock}, currLevel{currLevel}
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
}

void Board::right(bool isHeavy)
{
    currBlock->right(isHeavy);
}

void Board::left(bool isHeavy)
{
    currBlock->left(isHeavy);
}

bool Board::down()
{
    currBlock->down();
}

void Board::rotate(bool clockwise)
{
    currBlock->rotate(clockwise);
}

void Board::drop()
{
}

void Board::levelDown()
{
    if (level >= 1)
    {
        level--;
        currLevel
    }
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
    Block *curr = new Block{currCells[0], currCells[1], currCells[3], currCells[4], 4, level};
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
    Block *star = new starBlock{cells[availableRow][centralCol], nullptr, nullptr, nullptr, 1, level};
    cells[availableRow][centralCol]->setChar('*');
    cells[availableRow][centralCol]->setBlock(star);
    blockCount = 0;
}
