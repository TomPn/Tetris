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
        this->scriptfile1 = "sequence1.txt";
    }

    if (!haveScript2)
    {
        this->scriptfile2 = "sequence2.txt";
    }

    curPlayer = new Board{startLevel, haveSeed, seed, this->scriptfile1};
    opponent = new Board{startLevel, haveSeed, seed, this->scriptfile2};
    std::vector<std::string> commands{"left", "right", "down", "clockwise", "counterclockwise", "drop", "levelup", "leveldown", "norandom", "random", "sequence", "I", "J", "L", "O", "S", "Z", "T", "restart", "printtext", "printgraphics", "heavy", "force", "blind", "ENDGAME"};
    cmdInter = new CommandInterpreter{commands};
}

Game::~Game() {
    delete curPlayer;
    delete opponent;
    delete cmdInter;
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
            isOver = true;
            Subject::notifyObservers(true);
            break;
        }
        if (isDigit(command[0]))
        {
            int len = command.length();
            for (int i = 0; i < len; ++i)
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
        }
        else if (command == "right" && !isOver)
        {
            right(multiplier);
        }
        else if (command == "down" && !isOver)
        {
            down(multiplier);
        }
        else if (command == "clockwise" && !isOver)
        {
            rotate(1, multiplier);
        }
        else if (command == "counterclockwise" && !isOver)
        {
            rotate(0, multiplier);
        }
        else if (command == "drop" && !isOver)
        {
            drop(multiplier);
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
            // the special effects are triggered after a player drops, which means the round is already over, so the playerRound condition is reversed.if (playerRound)
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
    int callDrop;
    if (!playerRound)
    {
        callDrop = curPlayer->left(multiplier);
    }
    else
    {
        callDrop = opponent->left(multiplier);
    }
    if (callDrop)
    {
        drop(1);
    }
    Subject::notifyObservers(false);
}

void Game::right(int multiplier)
{
    int callDrop;
    if (!playerRound)
    {
        callDrop = curPlayer->right(multiplier);
    }
    else
    {
        callDrop = opponent->right(multiplier);
    }
    if (callDrop)
    {
        drop(1);
    }
    Subject::notifyObservers(false);
}

bool Game::down(int multiplier)
{
    bool ifBot = 0;
    for (int i = 0; i < multiplier; ++i)
    {
        if (!playerRound)
        {
            ifBot = curPlayer->down();
            if (!ifBot)
            {
                break;
            }
        }
        else
        {
            ifBot = opponent->down();
            if (!ifBot)
            {
                break;
            }
        }
        Subject::notifyObservers(false);
    }
    return false;
}

void Game::rotate(bool clockwise, int multiplier)
{

    // multiplier = multiplier % 4;
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
        Subject::notifyObservers(false);
    }
}

void Game::drop(int multiplier)
{
    bool prompt;
    for (int i = 0; i < multiplier; ++i)
    {
        // player 0 turn
        if (!playerRound)
        {
            // drop the block and check if the game is over
            prompt = curPlayer->drop();
            isOver = curPlayer->getOver();
            if (isOver)
            {
                Subject::notifyObservers(false);
                break;
            }
            // switch player round
            playerRound = 1;
            // update the highest score
            if (curPlayer->getScore() > hiScore)
            {
                hiScore = curPlayer->getScore();
            }
        }
        // player 1 turn
        else
        {
            // drop the block and check if the game is over
            prompt = opponent->drop();
            isOver = opponent->getOver();
            if (isOver)
            {
                Subject::notifyObservers(false);
                break;
            }
            // switch player round
            playerRound = 0;
            // update the highest score
            if (opponent->getScore() > hiScore)
            {
                hiScore = opponent->getScore();
            }
        }
        // print the state after the move
        Subject::notifyObservers(false);
        // if 2+ rows have been cleared, print the prompt and let player choose special actions
        if (prompt)
        {
            Subject::notifyObserversPrompt();
        }
    }
    // if the game is over, let the player choose whether end the game or play again
    if (isOver) {
        Subject::notifyObservers(true);
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
        Subject::notifyObservers(false);
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
        return opponent->getLevel();
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
        Subject::notifyObservers(false);
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
        Subject::notifyObservers(false);
    }
}

void Game::restart()
{
    delete curPlayer;
    delete opponent;
    curPlayer = new Board{startLevel, haveSeed, seed, scriptfile1};
    opponent = new Board{startLevel, haveSeed, seed, scriptfile2};
    playerRound = 0;
    isOver = 0;
    Subject::notifyObservers(false);
}

void Game::blind()
{
    // the special effects are triggered after a player drops, which means the round is already over, so the playerRound condition is reversed.
    if (playerRound)
    {
        opponent->setBlind();
    }
    else
    {
        curPlayer->setBlind();
    }
}

void Game::heavy()
{
    // the special effects are triggered after a player drops, which means the round is already over, so the playerRound condition is reversed.
    if (playerRound)
    {
        opponent->setHeavy();
    }
    else
    {
        curPlayer->setHeavy();
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
