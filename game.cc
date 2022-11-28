#include "game.h"
#include "board.h"
#include "commandInterpreter.h"
using std::cin;

Game::Game(int startLevel, bool textMode, unsigned int seed, bool haveSeed, bool haveScript1, bool haveScript2, std::string scriptfile1, std::string scriptfile2) : playerRound{0},
                                                                                                                                                                    startLevel{startLevel}, textMode{textMode}, seed{seed}, haveSeed{haveSeed}, haveScript1{haveScript1}, haveScript2{haveScript2}, scriptfile1{scriptfile1}, scriptfile2{scriptfile2}
{
    if (haveSeed)
    {
        if (haveScript1)
        {
            if (haveScript2)
            {
                this->curPlayer = new Board{startLevel, scriptfile1, 1, seed};
                this->opponent = new Board{startLevel, scriptfile2, 1, seed};
            }
            else
            {
                this->curPlayer = new Board{startLevel, scriptfile1, 1, seed};
                this->opponent = new Board{startLevel, "sequence2.txt", 1, seed};
            }
        }
        else
        {
            if (haveScript2)
            {
                this->curPlayer = new Board{startLevel, "sequence1.txt", 1, seed};
                this->opponent = new Board{startLevel, scriptfile2, 1, seed};
            }
            else
            {
                this->curPlayer = new Board{startLevel, "sequence1.txt", 1, seed};
                this->opponent = new Board{startLevel, "sequence2.txt", 1, seed};
            }
        }
    }
    else
    {
        if (haveScript1)
        {
            if (haveScript2)
            {
                this->curPlayer = new Board{startLevel, scriptfile1, 0, seed};
                this->opponent = new Board{startLevel, scriptfile2, 0, seed};
            }
            else
            {
                this->curPlayer = new Board{startLevel, scriptfile1, 0, seed};
                this->opponent = new Board{startLevel, "sequence2.txt", 0, seed};
            }
        }
        else
        {
            if (haveScript2)
            {
                this->curPlayer = new Board{startLevel, "sequence1.txt", 0, seed};
                this->opponent = new Board{startLevel, scriptfile2, 0, seed};
            }
            else
            {
                this->curPlayer = new Board{startLevel, "sequence1.txt", 0, seed};
                this->opponent = new Board{startLevel, "sequence2.txt", 0, seed};
            }
        }
    }
}

int Game::start()
{
    std::string command;
    while (true)
    {
        int multiplier = 0;
        int commandIndex = 0;
        command = cmdInter->getCommand();
        if (command == "ENDGAME")
        {
            break;
        }
        if (isdigit(command[0]))
        {
            for (int i = 0; i < command.length(); ++i)
            {
                if (!isdigit(command[i]))
                {
                    break;
                }
                ++commandIndex;
            }
            multiplier = std::stoi(command.substr(0, commandIndex));
            command = command.substr(commandIndex, command.length() - commandIndex);
        }
        if (command == "left")
        {
            left(multiplier);
        }
        else if (command == "right")
        {
            right(multiplier);
        }
        else if (command == "down")
        {
            down(multiplier);
        }
        else if (command == "clockwise")
        {
            rotate(1, multiplier);
        }
        else if (command == "counterclockwise")
        {
            rotate(0, multiplier);
        }
        else if (command == "drop")
        {
            drop(multiplier);
        }
        else if (command == "levelup")
        {
            levelUp(multiplier);
        }
        else if (command == "leveldown")
        {
            levelDown(multiplier);
        }
        else if (command == "norandom")
        {
            cin >> command;
            noRandom(command);
        }
        else if (command == "random")
        {
            random();
        }
        else if (command == "I" || command == "J" || command == "L" || command == "O" || command == "S" || command == "Z" || command == "T")
        {
            IJL(command[0], multiplier);
        }
        else if (command == "restart")
        {
            restart();
        }
        else if (command == "heavy")
        {
            // the special effects are triggered after a player drops, which means the round is already over, so the playerRound condition is reversed.
            if (playerRound)
            {
                if (curPlayer->getTrigger())
                {
                    heavy();
                    curPlayer->setTrigger(0);
                }
                // could give a note of invalid command here
            }
            else
            {
                if (opponent->getTrigger())
                {
                    heavy();
                    opponent->setTrigger(0);
                }
            }
        }
        else if (command == "force")
        {
            // the special effects are triggered after a player drops, which means the round is already over, so the playerRound condition is reversed.
            if (playerRound)
            {
                if (curPlayer->getTrigger())
                {
                    while (cin >> command)
                    {
                        if (command == "I" || command == "J" || command == "L" || command == "O" || command == "S" || command == "Z" || command == "T")
                        {
                            force(command[0]);
                            curPlayer->setTrigger(0);
                            break;
                        }
                    }
                }
                // could give a note of invalid command here
            }
            else
            {
                if (opponent->getTrigger())
                {
                    while (cin >> command)
                    {
                        if (command == "I" || command == "J" || command == "L" || command == "O" || command == "S" || command == "Z" || command == "T")
                        {
                            force(command[0]);
                            opponent->setTrigger(0);
                            break;
                        }
                    }
                }
            }
        }
        else if (command == "blind")
        {
            // the special effects are triggered after a player drops, which means the round is already over, so the playerRound condition is reversed.
            if (playerRound)
            {
                if (curPlayer->getTrigger())
                {
                    blind();
                    curPlayer->setTrigger(0);
                }
                // could give a note of invalid command here
            }
            else
            {
                if (opponent->getTrigger())
                {
                    blind();
                    opponent->setTrigger(0);
                }
            }
        }
    }
}

void Game::left(int multiplier)
{
    if (!playerRound)
    {
        curPlayer->left(multiplier);
    }
    else
    {
        opponent->left(multiplier);
    }
}

void Game::right(int multiplier)
{
    if (!playerRound)
    {
        curPlayer->right(multiplier);
    }
    else
    {
        opponent->right(multiplier);
    }
}

bool Game::down(int multiplier)
{
    if (!playerRound)
    {
        curPlayer->down(multiplier);
    }
    else
    {
        opponent->down(multiplier);
    }
}

void Game::rotate(bool clockwise, int multiplier)
{
    if (!playerRound)
    {
        curPlayer->rotate(clockwise, multiplier);
    }
    else
    {
        opponent->rotate(clockwise, multiplier);
    }
}

void Game::drop(int multiplier)
{
    if (!playerRound)
    {
        curPlayer->drop(multiplier);
        playerRound = 1;
    }
    else
    {
        opponent->drop(multiplier);
        playerRound = 0;
    }
}

void Game::IJL(char blockType, int multiplier)
{
    if (!playerRound)
    {
        curPlayer->IJL(blockType, multiplier);
    }
    else
    {
        opponent->IJL(blockType, multiplier);
    }
}

char Game::getState(int row, int col) const
{
    if (!playerRound)
    {
        curPlayer->getState(row, col);
    }
    else
    {
        opponent->getState(row, col);
    }
}

char Game::getLevel(int player) const
{
    if (!player)
    {
        curPlayer->getLevel();
    }
    else
    {
        opponent->getLevel();
    }
}

char Game::getScore(int player) const
{
    if (!player)
    {
        curPlayer->getScore();
    }
    else
    {
        opponent->getScore();
    }
}

char Game::getChange(int row, int col) const
{
    if (!playerRound)
    {
        curPlayer->getChange(row, col);
    }
    else
    {
        opponent->getChange(row, col);
    }
}

void Game::noRandom(std::string file)
{
    curPlayer->getLevel()->setScriptfile(1, file);
    opponent->getLevel()->setScriptfile(1, file);
}

void Game::random()
{
    curPlayer->getLevel()->setScriptfile(0);
    opponent->getLevel()->setScriptfile(0);
}

void Game::levelUp(int multiplier)
{
    if (!playerRound)
    {
        curPlayer->levelUp(multiplier);
    }
    else
    {
        opponent->levelUp(multiplier);
    }
}

void Game::levelDown(int multiplier)
{
    if (!playerRound)
    {
        curPlayer->levelDown(multiplier);
    }
    else
    {
        opponent->levelDown(multiplier);
    }
}

void Game::restart()
{
    delete curPlayer;
    delete opponent;
    curPlayer = new Board{startLevel};
    opponent = new Board{startLevel};
}

void Game::blind()
{
    // the special effects are triggered after a player drops, which means the round is already over, so the playerRound condition is reversed.
    if (playerRound)
    {
        curPlayer->setBlind();
    }
    else
    {
        opponent->setBlind();
    }
}

void Game::heavy()
{
    // the special effects are triggered after a player drops, which means the round is already over, so the playerRound condition is reversed.
    if (playerRound)
    {
        curPlayer->setHeavy();
    }
    else
    {
        opponent->setHeavy();
    }
}

void Game::force(char blockType)
{
    // the special effects are triggered after a player drops, which means the round is already over, so the playerRound condition is reversed.
    if (playerRound)
    {
        opponent->setForce(blockType);
    }
    else
    {
        curPlayer->setForce(blockType);
    }
}
