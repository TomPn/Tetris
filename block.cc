#include "block.h"
#include "cell.h"

const int cellNum = 4;

// Block constructor
Block::Block(Cell *cell1, Cell *cell2, Cell *cell3, Cell *cell4, int alive, int level) :
    alive{alive}, level{level} {
    components.emplace_back(cell1);
    components.emplace_back(cell2);
    components.emplace_back(cell3);
    components.emplace_back(cell4);
}


// move the block to the desired direction
bool Block::move(char dir) {
    // check if it can move to the required direction
    for (int i = 0; i < cellNum; i++) {
        if (!components[i]->check(dir)) {
            return false;
        }
    }

    // move the block to the desired direction
    for (int i = 0; i < cellNum; i++) {
        Cell *neighbour = components[i]->getCell(dir);
        neighbour->setChar(components[i]->getChar(false));
        neighbour->setBlock(components[i]->getBlock());
        components[i]->setChar(' ');
        components[i]->setBlock(nullptr);
    }
    return true;
}


// move the block to the left
void Block::left(bool isHeavy) {
    if (move('l')) {
        // if it's heavy, then go down twice
        if (isHeavy) {
            for (int i = 0; i < 2; i++) {
                down();
            }
        }
    }
}


// move the block to the right
void Block::right(bool isHeavy) {
    if (move('r')) {
        // if it's heavy, then go down twice
        if (isHeavy) {
            for (int i = 0; i < 2; i++) {
                down();
            }
        }
    }
}


// move the block down
bool Block::down() {
    if (move('d')) {
        return true;
    } else {
        return false;
    }

}


void Block::drop() {}


int Block::getLevel() {
    return level;
}


int Block::getAlive() {
    return alive;
}

int Block::setAlive(int alive) {
    this->alive = alive;
}


