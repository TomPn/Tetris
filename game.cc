#include "game.h"
#include "board.h"
#include "commandInterpreter.h"
#include <sstream>
using std::cin;
using std::cout;
using std::endl;

bool Game::isDigit(char c)
{
    if (c >= '0' && c <= '9')
        return true;
    return false;
}

int Game::toInt(std::string s)
{
    std::stringstream os;
    os << s;
    int i;
    os >> i;
    return i;
}

Game::Game(int startLevel, unsigned int seed, bool haveSeed, bool haveScript1, bool haveScript2, std::string scriptfile1, std::string scriptfile2) : playerRound{0}, startLevel{startLevel}, seed{seed}, haveSeed{haveSeed}, haveScript1{haveScript1}, haveScript2{haveScript2}, scriptfile1{scriptfile1}, scriptfile2{scriptfile2}
{
    if (!haveScript1)
    {
        scriptfile1 = "sequence1.txt";
    }

    if (!haveScript2)
    {
        scriptfile2 = "sequence2.txt";
    }
    
    curPlayer = new Board{startLevel, haveSeed, seed, scriptfile1};
    opponent = new Board{startLevel, haveSeed, seed, scriptfile2};
    std::vector<std::string> commands { "left", "right", "down", "clockwise", "counterclockwise", "drop", "levelup", "leveldown", "norandom", "random", "sequence", "I", "J", "L", "O", "S", "Z", "T", "restart", "printtext", "printgraphics", "ENDGAME"};
    
    cmdInter = new CommandInterpreter{commands};
}

void Game::start()
{
    std::string command;
    Subject::notifyObservers(false);

    while (true)
    {
        int multiplier = 1;
        int commandIndex = 0;
        command = cmdInter->getCommand();

        if (command == "ENDGAME") {
            break;
        }
        if (isDigit(command[0]))
        {
            for (int i = 0; i < command.length(); ++i)
            {
                if (!isDigit(command[i]))
                {
                    break;
                }
                ++commandIndex;
            }
            multiplier = toInt(command.substr(0, commandIndex));
            command = command.substr(commandIndex, command.length() - commandIndex);
        }
        if (command == "left" && !isOver)
        {
            left(multiplier);
            Subject::notifyObservers(false);
        }
        else if (command == "right" && !isOver)
        {
            right(multiplier);
            Subject::notifyObservers(false);
        }
        else if (command == "down" && !isOver)
        {
            down(multiplier);
            Subject::notifyObservers(false);
        }
        else if (command == "clockwise" && !isOver)
        {
            rotate(1, multiplier);
            Subject::notifyObservers(false);
        }
        else if (command == "counterclockwise" && !isOver)
        {
            rotate(0, multiplier);
            Subject::notifyObservers(false);
        }
        else if (command == "drop" && !isOver)
        {
            drop(multiplier);
            if (isOver) {
                Subject::notifyObservers(true);
            } else {
                Subject::notifyObservers(false);
            }
        }
        else if (command == "levelup" && !isOver)
        {
            levelUp(multiplier);
        }
        else if (command == "leveldown" && !isOver)
        {
            levelDown(multiplier);
        }
        else if (command == "norandom" && !isOver)
        {
            cin >> command;
            noRandom(command);
        }
        else if (command == "random" && !isOver)
        {
            random();
        }
        else if ((command == "I" || command == "J" || command == "L" || command == "O" || command == "S" || command == "Z" || command == "T") && !isOver)
        {
            IJL(command[0], multiplier);
        }
        else if (command == "restart")
        {
            
            restart();
        }
        else if (command == "heavy" && !isOver)
        {
            std::cout << "heavy" << std::endl;
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
        else if (command == "force" && !isOver)
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
        else if (command == "blind"  && !isOver)
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
    bool ifBot = 0;
    for (int i = 0; i < multiplier; ++i)
    {
        if (!playerRound)
        {
            ifBot = curPlayer->down();
            if (!ifBot) {break;}
        }
        else
        {
            ifBot = opponent->down();
            if (!ifBot) {break;}
        }
    }
    return false;
}

void Game::rotate(bool clockwise, int multiplier)
{

    multiplier = multiplier % 4;
    for (int i = 0; i < multiplier; ++i)
    {
        if (!playerRound)
        {
            curPlayer->rotate(clockwise);
        }
        else
        {
            opponent->rotate(clockwise);
        }
    }
}

void Game::drop(int multiplier)
{
    for (int i = 0; i < multiplier; ++i)
    {
        if (!playerRound)
        {
            curPlayer->drop();
            isOver = curPlayer->getOver();
            isOver = true;
            if (isOver)
            {
                break;
            }
            playerRound = 1;
            if (curPlayer->getScore() > hiScore) {
                hiScore = curPlayer->getScore();
            }
        }
        else
        {
            opponent->drop();
            isOver = curPlayer->getOver();
            if (isOver)
            {
                break;
            }
            playerRound = 0;
            if (opponent->getScore() > hiScore) {
                hiScore = curPlayer->getScore();
            }
        }
    }
}

void Game::IJL(char blockType, int multiplier)
{
    for (int i = 0; i < multiplier; ++i)
    {
        if (!playerRound)
        {
            curPlayer->IJL(blockType);
        }
        else
        {
            opponent->IJL(blockType);
        }
    }
}

char Game::getState(int player, int row, int col) const
{
    if (!player)
    {
        return curPlayer->charAt(row, col);
    }
    else
    {
        return opponent->charAt(row, col);
    }
}

bool Game::getChange(int player, int row, int col) const
{
    if (!player)
    {
        return curPlayer->getChange(row, col);
    }
    else
    {
        return opponent->getChange(row, col);
    }
}

int Game::getLevel(int player) const
{
    if (!player)
    {
        return curPlayer->getLevel();
    }
    else
    {
        return  opponent->getLevel();
    }
}

int Game::getScore(int player) const
{
    if (!player)
    {
        return curPlayer->getScore();
    }
    else
    {
        return opponent->getScore();
    }
}

void Game::noRandom(std::string file)
{
    if (curPlayer->getLevel() == 3 || curPlayer->getLevel() == 4)
    {
        curPlayer->setNoRandom(true, file);
    }
    if (opponent->getLevel() == 3 || opponent->getLevel() == 3)
    {
        opponent->setNoRandom(true, file);
    }
}

void Game::random()
{
    if (curPlayer->getLevel() == 3 || curPlayer->getLevel() == 4)
    {
        curPlayer->setNoRandom(false, "");
    }
    if (opponent->getLevel() == 3 || opponent->getLevel() == 3)
    {
        opponent->setNoRandom(false, "");
    }
}

void Game::levelUp(int multiplier)
{
    for (int i = 0; i < multiplier; ++i)
    {
        if (!playerRound)
        {
            curPlayer->levelUp();
        }
        else
        {
            opponent->levelUp();
        }
    }
}

void Game::levelDown(int multiplier)
{
    for (int i = 0; i < multiplier; ++i)
    {
        if (!playerRound)
        {
            curPlayer->levelDown();
        }
        else
        {
            opponent->levelDown();
        }
    }
}

void Game::restart()
{
    delete curPlayer;
    delete opponent;
    curPlayer = new Board{startLevel, haveSeed, seed, scriptfile1};
    opponent = new Board{startLevel, haveSeed, seed, scriptfile2};
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

void Game::setHiScore()
{
    if (curPlayer->getScore() > hiScore)
    {
        hiScore = curPlayer->getScore();
    }
    if (opponent->getScore() > hiScore)
    {
        hiScore = opponent->getScore();
    }
}

int Game::getHiScore()
{
    return hiScore;
}


void Game::over() {
    notifyObservers(true);
}

Game::~Game() {}

void Game::setNames() {
    cout << "Enter Player1 Name: " << endl;
    std::string name;
    cin >> name;
    curPlayer->setName(name);
    cout << "Enter Player2 Name: " << endl;
    cin >> name;
    opponent->setName(name);
}

std::string Game::getName(bool player) {
    if (!player) {
        return curPlayer->getName();
    } else {
        return opponent->getName();
    }

}
