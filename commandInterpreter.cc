#include <cstdlib>
#include <vector>
#include <map>
#include "commandInterpreter.h"

struct CommandInterpreterImpl {
    std::string curCommand;
    int multiplier;
    std::vector<std::string> commands;
    std::map<std::string, std::string> rename;
    std::map<std::string, std::vector<std::string>> macro;
};
