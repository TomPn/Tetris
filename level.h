#ifndef LEVEL_H
#define LEVEL_H
#include <string>

class Level{
    std::string file,sequence1,sequence2,scriptfile1,scriptfile2;
    bool randomBool,scriptfileBool,seedBool;
    unsigned int seed = 0;
    public:
    Level():file{""},sequence1{""},sequence2{""},scriptfile1{""},scriptfile2{""},randomBool{false},scriptfileBool{false},seedBool{false},seed{0} {}
    virtual ~Level();
    void setScriptfile(bool scriptfile,std::string file1,std::string file2);
    void setSeed(unsigned int seed);
    virtual Block CreateNextBlock() = 0;
    void setRandom(bool random);
};

#endif



