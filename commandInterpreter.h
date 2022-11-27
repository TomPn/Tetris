#ifndef __COMMANDINT_H__
#define __COMMANDINT_H__
#include <iostream>
#include <string>

class CommandInterpreterImpl;

class commandInterpreter {
    CommandInterpreterImpl * pImpl;
    public:
        bool setCM();
        std::string getCommand();
        int getMultiplier();
        void rename(std::string before, std::string after);
        void addMacro(std::string name);
        bool isValid(std::string name);
};

#endif
