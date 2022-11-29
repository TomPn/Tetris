#include <cstdlib>
#include <vector>
#include <map>
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include "commandInterpreter.h"
#include "commandInterpreterImpl.h"

using std::cin;

bool CommandInterpreter::isDigit(char c) {
    if (c >= '0' && c <= '9') return true;
    return false;
}

std::string CommandInterpreter::toString(int i) {
    std::stringstream os;
    os << i;
    std::string s{};
    os >> s;
    return s;
}

int CommandInterpreter::toInt(std::string s) {
    std::stringstream os;
    os << s;
    int i;
    os >> i;
    return i;
}

CommandInterpreter::CommandInterpreter(std::vector<std::string> commands): pImpl{new CommandInterpreterImpl} {
    pImpl->commands = commands;
}

std::string CommandInterpreter::isValid(std::string name, int multiplier) {
    int duplicate = 0;
    int nameLen = name.length();
    std::string extCommand;
    for (auto it: pImpl->commands) {
        if (name == it) {
            if (name == "restart" || name == "norandom" || name == "random") {
                return name;
            }
            return toString(multiplier) + name;
        }
    }
    // check if any head of the command equals to the current command
    for (auto it: pImpl->commands) {
        if (name == it.substr(0, nameLen)){
            ++duplicate;
            extCommand = it;
        }
    }
    // if no ambiguious meaning of the current command, return the command
    if (duplicate == 1) return toString(multiplier) + extCommand;
    return "";
}

void CommandInterpreter::rename() {
    int commandInCommands = 0; 
    int nameUsed = 0;
    std::string oldCommand;
    // read in the command name
    cin >> oldCommand;
    // check if the command name is a valid command
    for (auto &it: pImpl->commands) {
        if (oldCommand == it) {
            commandInCommands = 1;
        }
    }
    // if it is, read the name used for renaming
    if (commandInCommands) {
        std::string name;
        cin >> name;
        // check if the name is already used
        for (auto &p: pImpl->renameMap) {
            if (p.first == name && p.second != oldCommand) {
                nameUsed = 1;
            }
        }
        // if not used, create a new pair in renameMap
        if (!nameUsed) {
            pImpl->renameMap[name] = oldCommand;
        }
    }
}

void CommandInterpreter::addMacro() {
    // read in the name of the macro
    std::string name, macroCommand;
    std::vector<std::string> macroCommands;
    cin >> name;
    // read in the sequence of commands
    while (cin >> macroCommand) {
        if (macroCommand == "done") break;
        macroCommands.emplace_back(macroCommand);
    }
    // add the new macro pair to macro map
    pImpl->macros[name] = macroCommands;
}

std::string CommandInterpreter::getCommand() {
    std::string command;
    int multiplier = 1;
    int commandIndex = 0;
    cin >> command;
    if (cin.eof()) return "ENDGAME";
    // check if a multiplier exists
    if (isDigit(command[0])) {
        for (int i = 0; i < command.length(); ++i) {
            if (!isDigit(command[i])) {
                break;
            }
            ++commandIndex;
        }
        if (commandIndex >= command.length()) {
            return "";
        }
        multiplier = toInt(command.substr(0,commandIndex));
        command = command.substr(commandIndex,command.length()-commandIndex);
    }
    // rename command
    if (command == "rename") {
        rename();
    } // macro command
    else if (command == "macro") {
        addMacro();
    } // sequence command
    else if (command == "sequence") {
        std::string fileName;
        bool firstCommand = 0;
        std::string command1;
        // read in the file name
        cin >> fileName;
        std::ifstream infile{ fileName };
        while(infile >> command) {
            if (!firstCommand) {
                command1 = command;
                firstCommand = 1;
            }
            pImpl->remainCommands.emplace_back(command);
        }
        return isValid(command1, multiplier);
    } else {
        // check if command is a rename of command
        pImpl->multiplier = 0;
        for (auto const &p: pImpl->renameMap) {
            if (command == p.first) {
                return isValid(pImpl->renameMap[command], multiplier);
            }
        }
        // check if command is the name of a macro
        std::string newCommand;
        for (auto &p: pImpl->macros) {
            if (command == p.first) {
                if (pImpl->macros[command].size() == 1) {
                    return isValid(pImpl->macros[command][0], multiplier);
                }
                newCommand = pImpl->macros[command][0];
                pImpl->macros[command].erase(pImpl->macros[command].begin());
                pImpl->remainCommands = pImpl->macros[command];
                return isValid(pImpl->macros[command][0], multiplier);
            }
        }
    }
    return isValid(command, multiplier);
}
