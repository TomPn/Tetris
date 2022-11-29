

struct CommandInterpreterImpl {
    std::string curCommand;
    int multiplier;
    std::vector<std::string>remainCommands;
    std::vector<std::string>commands;
    std::map<std::string, std::string>renameMap;
    std::map<std::string, std::vector<std::string>>macros;
};

