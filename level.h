#ifndef LEVEL_H
#define LEVEL_H
#include <string>

class Level{
    std::string file,scriptfile1,scriptfile2;
    bool randomBool,scriptfileBool,seedBool;
    unsigned int seed = 0;
    public:
    Level():file{""},scriptfile1{""},scriptfile2{""},randomBool{false},scriptfileBool{false},seedBool{false},seed{0} {}
    virtual ~Level();
    void setScriptfile(bool scriptfile,string file1,string file2);
    void setSeed(unsigned int seed);
    virtual Block CreateNextBlock() = 0;
    void setRandom(bool random);
};

#endif



