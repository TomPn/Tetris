#ifndef _GAME_H_
#define _GAME_H_
#include <iostream>
#include <string>
#include <memory>
#include "subject.h"
class CommandInterpreter;
class Board;

class Game : public Subject
{
    int playerRound; // 0: curPlayer's round, 1: opponent's round
    int startLevel;  // default level 0
    unsigned int seed;
    bool haveSeed;
    bool haveScript1;
    bool haveScript2;
    bool isOver;
    int hiScore;
    std::string curPlayerName;
    std::string opponentName;
    std::string scriptfile1;
    std::string scriptfile2;
    std::unique_ptr<Board> curPlayer;
    std::unique_ptr<Board> opponent;
    std::unique_ptr<CommandInterpreter> cmdInter;
    bool isDigit(char c);
    int toInt(std::string s);

public:
    explicit Game(int startLevel, unsigned int seed, bool haveSeed, bool haveScript1, bool haveScript2, std::string scriptfile1, std::string scriptfile2);
    ~Game();
    void start();
    void left(int multiplier);
    void right(int multiplier);
    bool down(int multiplier);
    void rotate(bool clockwise, int multiplier);
    bool drop(int multiplier);
    void IJL(char blockType, int multiplier);
    char getState(int player, int row, int col) const override;
    int getLevel(int player) const override;
    int getScore(int player) const override;
    int getBonus(int player) const override;
    bool getOver(int player) const override;
    void setHiScore();
    int getHiScore();
    bool getChange(int player, int row, int col) const override;
    void setChange(int player, int row, int col, bool change) override;
    void noRandom(std::string file);
    void random();
    void levelUp(int multiplier);
    void levelDown(int multiplier);
    void restart();
    void blind();
    void heavy();
    void force(char blockType);
    void checkOver();
    void over();
    void setNames();
    std::string getName(bool player);
};

#endif
