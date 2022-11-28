#ifndef __COMMANDINT_H__
#define __COMMANDINT_H__
#include <iostream>
#include <string>
#include <vector>

class CommandInterpreterImpl;

class CommandInterpreter {
    CommandInterpreterImpl * pImpl;
    public:
        CommandInterpreter(std::vector<std::string> commands);
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
