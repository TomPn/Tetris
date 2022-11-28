#ifndef _GAME_H_
#define _GAME_H_
#include <iostream>
#include <string>
#include "subject.h"
class CommandInterpreter;
class Board;

class Game: public Subject{
    int playerRound; // 0: curPlayer's round, 1: opponent's round
    Board *curPlayer;
    Board *opponent;
    CommandInterpreter *cmdInter;
    public:
        explicit Game(Board *curPlayer, Board *opponent): curPlayer{curPlayer}, opponent{opponent}, playerRound{0} {}
        int executeCommand();
        void left();
        void right();
        bool down();
        void rotate(bool clockwise);
        void drop();
        void IJL(char blockType);
        char getState(int row, int col) const override;
        int getLevel (int player) const override;
        int getScore (int player) const override;
        void noRandom(std::string file);
        void random();
        void levelUp();
        void levelDown();
        void restart();
        void blind();
        void heavy();
        void force(char blockType);
        ~Game();
};

#endif
