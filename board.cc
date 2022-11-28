#include "board.h"
#include "block.h"
#include "cell.h"
#include "level.h"
#include <vector>

const int rows = 20;
const int cols = 11;

Board::Board(int level, int score, bool isBlind, bool isHeavy, bool isForce,
             Board* opponentBoard, Block* currBlock, Block* nextBlock, Level* currLevel) :
             level{level}, score{score}, isBlind{isBlind}, isHeavy{isHeavy}, isForce{isForce},
             opponentBoard{opponentBoard}, currBlock{currBlock}, nextBlock{nextBlock}, currLevel{currLevel} {
    std::vector<std::vector<Cell*>> cells; 
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cells[i][j] = new Cell{' ', i, j};
        }
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (cells[i][j]->getX() != 0) {
                cells[i][j]->setNeighbour('t', cells[i - 1][j]);
            } else if (cells[i][j]->getX() != rows - 1) {
                cells[i][j]->setNeighbour('b', cells[i + 1][j]);
            } else if (cells[i][j]->getY() != 0) {
                cells[i][j]->setNeighbour('l', cells [i][j - 1]);
            } else if (cells[i][j]->getY() != cols - 1) {
                cells[i][j]->setNeighbour('r', cells[i][j + 1]);
            }
        }
    }
    this->cells = cells;
}



 

