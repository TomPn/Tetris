#ifndef __COMMANDINT_H__
#define __COMMANDINT_H__
#include <iostream>
#include <string>
#include <vector>
#include <memory>

class CommandInterpreterImpl;

class CommandInterpreter {
    std::unique_ptr<CommandInterpreterImpl> pImpl;
    std::vector<std::string> breakCommand(std::string command);
    public:
        CommandInterpreter(std::vector<std::string> commands);
        ~CommandInterpreter();
        // bool setCM();
        std::string getCommand();
        int getMultiplier();
        void rename();
        void addMacro();
        bool isDigit(char c);
        std::string toString(int i);
        int toInt(std::string s);
        std::string isValid(std::string name, int multiplier);
};

#endif
