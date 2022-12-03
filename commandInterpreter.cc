#include <cstdlib>
#include <vector>
#include <map>
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include "commandInterpreter.h"
using std::cin;
using std::cout;
using std::endl;

struct CommandInterpreterImpl {
    std::string curCommand;
    int multiplier;
    std::vector<std::string>remainCommands;
    std::vector<std::string>commands;
    std::map<std::string, std::string>renameMap;
    std::map<std::string, std::vector<std::string>>macros;
};

bool CommandInterpreter::isDigit(char c) {
    if (c >= '0' && c <= '9') return true;
    return false;
}

CommandInterpreter::~CommandInterpreter() {}

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

CommandInterpreter::CommandInterpreter(std::vector<std::string> commands) {
    pImpl = std::make_unique<CommandInterpreterImpl>();
    pImpl->commands = commands;
}

std::string CommandInterpreter::isValid(std::string name, int multiplier) {
    int duplicate = 0;
    int nameLen = name.length();
    std::string extCommand;
    for (auto it: pImpl->commands) {
        if (name == it) {
            if (name == "restart" || name == "norandom" || name == "random" || name == "ENDGAME") {
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
        if (macroCommand == "done") {
            cout << "macro: " << name << " added" << endl;
            break;
        } 
        macroCommands.emplace_back(macroCommand);
    }
    // add the new macro pair to macro map
    pImpl->macros[name] = macroCommands;
}

std::vector<std::string> CommandInterpreter::breakCommand(std::string command) {
    std::vector<std::string> breakedCommand;
    std::string multiplier;
    int commandIndex = 0;
    if (isDigit(command[0])) {
        int len = command.length();
        for (int i = 0; i < len; ++i) {
            if (!isDigit(command[i])) {
                break;
            }
            ++commandIndex;
        }
        if (commandIndex >= len) {
            return breakedCommand;
        }
        multiplier = command.substr(0,commandIndex);
        command = command.substr(commandIndex,command.length()-commandIndex);
        breakedCommand.emplace_back(command);
        breakedCommand.emplace_back(multiplier);
        return breakedCommand;
    }
    breakedCommand.emplace_back(command);
    return breakedCommand;
}

std::string CommandInterpreter::getCommand() {
    std::string command;
    int multiplier = 1;

    // if there is any remaining commands from previous actions, return them first
    if (pImpl->remainCommands.size() != 0) {
        std::string nextCommand = pImpl->remainCommands.front();
        pImpl->remainCommands.erase(pImpl->remainCommands.begin());
        
        std::vector<std::string> breakedCommand = breakCommand(nextCommand);
        if (breakedCommand.size() == 0) {
            return "";
        } else if (breakedCommand.size() == 1) {
            return isValid(breakedCommand[0], 1);
        }
        return isValid(breakedCommand[0], toInt(breakedCommand[1]));        
    }

    // read in the command
    cin >> command;
    // if eof, end the game
    if (cin.eof()) return "ENDGAME";
    // check if a multiplier exists
    std::vector<std::string> brokeCommand = breakCommand(command);
    if (brokeCommand.size() == 0) {
        return "";
    } else if (brokeCommand.size() == 1) { // if size-one vector is return, it means there is no multiplier
        command = brokeCommand[0];
        multiplier = 1;
    } else {
        command = brokeCommand[0];
        multiplier = toInt(brokeCommand[1]);
    }
    // rename command
    if (command == "rename") {
        rename();
    } else if (command == "macro") { // macro command
        addMacro();
    } else if (command == "sequence") { // sequence command
        std::string fileName;
        bool firstCommand = 0;
        std::string command1;

        // read in the file name
        cin >> fileName;
        std::ifstream infile{ fileName };
        
        // read all commands in the file. Store the first command locally and store the other ones in remainCommands.
        while(infile >> command) {
            if (!firstCommand) {
                command1 = command;
                firstCommand = 1;
            }
            pImpl->remainCommands.emplace_back(command);
        }

        // convert the command to the format of command + multiplier vector
        std::vector<std::string> breakedCommand = breakCommand(command1);
        // if no command is return, it means the command is composed of only number, hence not a valid command
        if (breakedCommand.size() == 0) {
            return "";
        } else if (breakedCommand.size() == 1) { // if size-one vector is return, it means there is no multiplier
            return isValid(breakedCommand[0], 1);
        }
        // if none of the above happens, it means its a command with a multiplier
        return isValid(breakedCommand[0], toInt(breakedCommand[1]));   
    }
    else {
        // check if command is a rename of command
        for (auto const &p: pImpl->renameMap) {
            if (command == p.first) {
                return isValid(p.second, multiplier);   
            }
        }
        // check if command is the name of a macro
        std::string newCommand;
        std::vector<std::string> tmpMacro;
        for (auto &p: pImpl->macros) {
            if (command == p.first) {
                newCommand = pImpl->macros[command][0];
                tmpMacro = pImpl->macros[command];
                tmpMacro.erase(tmpMacro.begin());
                pImpl->remainCommands = tmpMacro;
                // if multiple macros are called, add all of them to remainCommands
                for (int i = 1; i < multiplier; ++i) {
                    for (auto it: pImpl->macros[command]) {
                        pImpl->remainCommands.emplace_back(it);
                    }
                }
                // execute the first command
                std::vector<std::string> breakedCommand = breakCommand(newCommand);
                if (breakedCommand.size() == 0) {
                    return "";
                } else if (breakedCommand.size() == 1) {
                    return isValid(breakedCommand[0], 1);
                }
                return isValid(breakedCommand[0], toInt(breakedCommand[1]));   
            }
        }
    }
    return isValid(command, multiplier);
}
