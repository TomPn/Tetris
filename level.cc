#include "level.h"
#include <string>
#include <fstream>

// readFile reads the strings in file/sequence/scriptfile store them in a vector of string
std::vector<std::string> Level::readFile(std::string fileName){
    // initialize the file object, a string, and a vector of string
    std::ifstream f{fileName};
    std::string s;
    std::vector<std::string> content;
    // read each string in file and insert them into the vecter of string
    while(f << s){
        content.emplace_back(s);
    }
    return content;
}

Level::Level(std::vector<std::vector<Cell *>> cells):file{""},sequence{""},scriptfile{""},randomBool{false},scriptfileBool{false},seedBool{false},seed{0}, cells{cells}, sequenceIndex{0},scriptfileIndex{0},fileIndex{0} {
    // initialize a placeholder for the vector of string
    std::vector<std::string> placeholder{""};
    // if fileName isn't empty, call readFile to read the strings in the file and store them in a vector of string
    if(file != ""){
        fileContent = Level::readFile(file);
    }else{
        fileContent = placeholder;
    }

    if(sequence != ""){
        sequenceContent = Level::readFile(sequence);
    }else{
        sequenceContent = placeholder;
    }

    if(scriptfile != ""){
        scriptfileContent = Level::readFile(scriptfile);
    }else{
        scriptfileContent = placeholder;
    }

}

Block * Level::CreateIBlock(int level){
    string blockStr = "I";
    cells[19][0].setChar(blockStr);
    cells[19][1].setChar(blockStr);
    cells[19][2].setChar(blockStr);
    cells[19][3].setChar(blockStr);
    Block * nextBlock = new Block{cells[19][0],cells[19][1],cells[19][2],cells[19][3],4,level};
    return nextBlock;
}
Block * Level::CreateJBlock(int level){
    string blockStr = "J";
    cells[18][0].setChar(blockStr);
    cells[19][0].setChar(blockStr);
    cells[19][1].setChar(blockStr);
    cells[19][2].setChar(blockStr);
    Block * nextBlock = new Block{cells[18][0],cells[19][0],cells[19][1],cells[19][2],4,level};
    return nextBlock;
}
Block * Level::CreateLBlock(int level){
    string blockStr = "L";
    cells[18][2].setChar(blockStr);
    cells[19][0].setChar(blockStr);
    cells[19][1].setChar(blockStr);
    cells[19][2].setChar(blockStr);
    Block * nextBlock = new Block{cells[18][2],cells[19][0],cells[19][1],cells[19][2],4,level};
    return nextBlock;
}
Block * Level::CreateOBlock(int level){
    string blockStr = "O";
    cells[18][0].setChar(blockStr);
    cells[18][1].setChar(blockStr);
    cells[19][0].setChar(blockStr);
    cells[19][1].setChar(blockStr);
    Block * nextBlock = new Block{cells[18][0],cells[18][1],cells[19][0],cells[19][1],4,level};
    return nextBlock;
}
Block * Level::CreateSBlock(int level){
    string blockStr = "S";
    cells[18][1].setChar(blockStr);
    cells[18][2].setChar(blockStr);
    cells[19][0].setChar(blockStr);
    cells[19][1].setChar(blockStr);
    Block * nextBlock = new Block{cells[18][1],cells[18][2],cells[19][0],cells[19][1],4,level};
    return nextBlock;
}
Block * Level::CreateZBlock(int level){
    string blockStr = "Z";
    cells[18][0].setChar(blockStr);
    cells[18][1].setChar(blockStr);
    cells[19][1].setChar(blockStr);
    cells[19][2].setChar(blockStr);
    Block * nextBlock = new Block{cells[18][0],cells[18][1],cells[19][1],cells[19][2],4,level};
    return nextBlock;
}
Block * Level::CreateTBlock(int level){
    string blockStr = "T";
    cells[18][0].setChar(blockStr);
    cells[18][1].setChar(blockStr);
    cells[18][2].setChar(blockStr);
    cells[19][1].setChar(blockStr);
    Block * nextBlock = new Block{cells[18][0],cells[18][1],cells[18][2],cells[19][1],4,level};
    return nextBlock;
}








// mutate scriptfileBool and scriptfile
void Level::setScriptfile(bool scriptfileBool,std::string scriptfile = ""){
    this->scriptfileBool = scriptfileBool;
    this->scriptfile = scriptfile;
}

// mutate seedBool and seed
void Level::setSeed(bool seedBool, unsigned int seed){
    this->seedBool = seedBool;
    this->seed = seed;
}


// mutate randomBool
void Level::setRandom(bool random){
    randomBool = random;
}