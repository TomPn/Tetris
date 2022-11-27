#include "board.h"
#include "block.h"
#include "cell.h"
#include "level.h"
#include <vector>

const int rows = 18;
const int cols = 10;

Board::Board(int level, int score, bool isBlind, bool isHeavy, bool isForce,
             Board* opponentBoard, Block* currBlock, Block* nextBlock, Level* currLevel) :
             level{level}, score{score}, isBlind{isBlind}, isHeavy{isHeavy}, isForce{isForce},
             opponentBoard{opponentBoard}, currBlock{currBlock}, nectBlock{nextBlock}, currLevel{currLevel} {
    std::vector<vector<Cell*>> cells; 
    for (int i = 0; i < rows, i++) {
        for (int j = 0; j < cols, j++) {
            cells[i][j] = new Cell{' ', i, j};
        }
    }
    for (int i = 0; i < rows, i++) {
        for (int j = 0; j < cols, j++) {
            if (cells[i][j]->x != 0) {
                cells[i][j]->setNeighbour('t', cells[i - 1][j]);
            } else if (cells[i][j]->x != rows - 1) {
                cells[i][j]->setNeighbour('b', cells[i + 1][j]);
            } else if (cells[i][j]->y != 0) {
                cells[i][j]->setNeighbour('l', cells [i][j - 1]);
            } else if (cells[i][j]->y != cols - 1) {
                cells[i][j]->setNeightbour('r', cells[i][j + 1]);
            }
        }
    }
    this->cells = cells;
}



 

