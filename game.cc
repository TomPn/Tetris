#include "game.h"
#include "board.h"
#include "commandInterpreter.h"
using std::cin;

int Game::executeCommand() {
    std::string command;
    while (true) {
        command = cmdInter->getCommand();
        if (command == "ENDGAME") {break;}
        else if (command == "left") {
            left();
        } else if (command == "right") {
            right();
        } else if (command == "down") {
            down();
        } else if (command == "clockwise") {
            rotate(1);
        } else if (command == "counterclockwise") {
            rotate(0);
        } else if (command == "drop") {
            drop();
        } else if (command == "levelup") {
            levelUp();
        } else if (command == "leveldown") {
            levelDown();
        } else if (command == "norandom") {
            cin >> command;
            noRandom(command);
        } else if (command == "random") {
            random();
        } else if (command == "I" || command == "J" || command == "L"  || command == "O"  || command == "S"  || command == "Z" || command == "T") {
            IJL(command[0]);
        } else if (command == "restart") {
            restart();
        } else if (command == "heavy") {
            // the special effects are triggered after a player drops, which means the round is already over, so the playerRound condition is reversed.
            if (playerRound) {
                if (curPlayer->getTrigger()) {
                    heavy();
                    curPlayer->setTrigger(0);
                }
                // could give a note of invalid command here
            } else {
                if (opponent->getTrigger()) {
                    heavy();
                    opponent->setTrigger(0);
                }
            }
        } else if (command == "force") {
            // the special effects are triggered after a player drops, which means the round is already over, so the playerRound condition is reversed.
            if (playerRound) {
                if (curPlayer->getTrigger()) {
                    while (cin >> command) {
                        if (command == "I" || command == "J" || command == "L"  || command == "O"  || command == "S"  || command == "Z" || command == "T") {
                            force(command[0]);
                            curPlayer->setTrigger(0);
                            break;
                        }
                    }
                }
                // could give a note of invalid command here
            } else {
                if (opponent->getTrigger()) {
                    while (cin >> command) {
                        if (command == "I" || command == "J" || command == "L"  || command == "O"  || command == "S"  || command == "Z" || command == "T") {
                            force(command[0]);
                            opponent->setTrigger(0);
                            break;
                        }
                    }
                }
            }
        } else if (command == "blind") {
            // the special effects are triggered after a player drops, which means the round is already over, so the playerRound condition is reversed.
            if (playerRound) {
                if (curPlayer->getTrigger()) {
                    blind();
                    curPlayer->setTrigger(0);
                }
                // could give a note of invalid command here
            } else {
                if (opponent->getTrigger()) {
                    blind();
                    opponent->setTrigger(0);
                }
            }
        }
    }
}

void Game::left() {
    if (!playerRound) {
        curPlayer->left();
    } else {
        opponent->left();
    }
}

void Game::right() {
    if (!playerRound) {
        curPlayer->right();
    } else {
        opponent->right();
    }
}

bool Game::down() {
    if (!playerRound) {
        curPlayer->down();
    } else {
        opponent->down();
    }
}

void Game::rotate(bool clockwise) {
    if (!playerRound) {
        curPlayer->rotate(clockwise);
    } else {
        opponent->rotate(clockwise);
    }
}

void Game::drop() {
    if (!playerRound) {
        curPlayer->drop();
        playerRound = 1;
    } else {
        opponent->drop();
        playerRound = 0;
    }
}

void Game::IJL(char blockType) {
    if (!playerRound) {
        curPlayer->IJL(blockType);
    } else {
        opponent->IJL(blockType);
    }
}

char Game::getState(int row, int col) const {
    if (!playerRound) {
        curPlayer->getState(row, col);
    } else {
        opponent->getState(row, col);
    }
}

char Game::getLevel(int player) const {
    if (!player) {
        curPlayer->getLevel();
    } else {
        opponent->getLevel();
    }
}

char Game::getScore(int player) const {
    if (!player) {
        curPlayer->getScore();
    } else {
        opponent->getScore();
    }
}

void Game::noRandom(std::string file) {
    curPlayer->getLevel()->setScriptfile(1, file);
    opponent->getLevel()->setScriptfile(1, file);
}

void Game::random() {
    curPlayer->getLevel()->setScriptfile(0);
    opponent->getLevel()->setScriptfile(0);
}

void Game::levelUp() {
    if (!playerRound) {
        curPlayer->levelUp();
    } else {
        opponent->levelUp();
    }
}

void Game::levelDown() {
    if (!playerRound) {
        curPlayer->levelDown();
    } else {
        opponent->levelDown();
    }
}

void Game::restart() {
    delete curPlayer;
    delete opponent;
    curPlayer = new Board();
    opponent = new Board();
}

void Game::blind() {
    // the special effects are triggered after a player drops, which means the round is already over, so the playerRound condition is reversed.
    if (playerRound) {
        curPlayer->setBlind();
    } else {
        opponent->setBlind();
    }
}

void Game::heavy() {
    // the special effects are triggered after a player drops, which means the round is already over, so the playerRound condition is reversed.
    if (playerRound) {
        curPlayer->setHeavy();
    } else {
        opponent->setHeavy();
    }
}

void Game::force(char blockType) {
    // the special effects are triggered after a player drops, which means the round is already over, so the playerRound condition is reversed.
    if (playerRound) {
        opponent->setForce(blockType);
    } else {
        curPlayer->setForce(blockType);
    }
}

