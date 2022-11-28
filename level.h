#ifndef LEVEL_H
#define LEVEL_H
#include <string>
#include <vector>

class Block;
class Cell;

class Level{
    std::string file,sequence,scriptfile;
    bool randomBool,scriptfileBool,seedBool;
    unsigned int seed = 0;
    int sequenceIndex;
    int scriptfileIndex;
    int fileIndex;
    std::vector<std::string> fileContent;
    std::vector<std::string> sequenceContent;
    std::vector<std::string> scriptfileContent;
    std::vector<std::vector<Cell *>> cells;
    std::vector<std::string> readFile(std::string fileName);
    protected:
    Block * CreateIBlock(int level);
    Block * CreateJBlock(int level);
    Block * CreateLBlock(int level);
    Block * CreateOBlock(int level);
    Block * CreateSBlock(int level);
    Block * CreateZBlock(int level);
    Block * CreateTBlock(int level);
    public:
    Level(std::vector<std::vector<Cell *>> cells);
    virtual ~Level();
    void setScriptfile(bool scriptfileBool,std::string scriptfile = "");
    void setSeed(unsigned int seed);
    virtual Block *CreateNextBlock() = 0;
    void setRandom(bool random);
};

#endif



