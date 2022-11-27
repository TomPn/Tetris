#ifndef _GAME_H_
#define _GAME_H_
#include <iostream>
#include <string>
#include "subject.h"
class Board;

class Game: public Subject{

    Board *curPlayer;
    Board *opponent;

    public:
        explicit Game(Board *curPlayer, Board *opponent): curPlayer{curPlayer}, opponent{opponent} {}
        void left();
        void right();
        void reset();
        bool down();
        void rotate(bool clockwise);
        void drop();
        void IJL(char blockType);
        void getState(int row, int col);
        void noRandom(std::string file);
        void random();
        void levelUp();
        void levelDown();
        void sequence();
        void restart();
        void blind();
        void heavy();
        void force(char blockType);
        ~Game();
};

#endif
