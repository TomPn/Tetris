#include "level4.h"
#include <string>
#include <cstdlib>

class Block;

Block * Level4::CreateNextBlock(){
    Block * nextBlock;
    // set up the seed
    if(seedBool ==true){
        std::srand(seed);
    }
    // random is a random int from 1 to 18
    int random = 1 + std::rand()/((RAND_MAX + 1u)/18);
    // SBlock and ZBlock has probability of 2/9 = 4/18
    if(random >= 1 && random <= 4){
        nextBlock = Level::CreateSBlock(3);
    }else if(random >= 5 && random <= 8){
        nextBlock = Level::CreateZBlock(3);
    }
    // other blocks has probability of 1/6
    else if(random == 9 || random == 10){
        nextBlock = Level::CreateIBlock(3);
    }else if(random == 11 || random == 12){
        nextBlock = Level::CreateJBlock(3);
    }else if(random == 13 || random == 14){
        nextBlock = Level::CreateTBlock(3);
    }else if(random == 15 || random == 16){
        nextBlock = Level::CreateOBlock(3);
    }else if(random == 17 || random == 18){
        nextBlock = Level::CreateOLlock(3);
    }
    return nextBlock;
}

Level4::~Level4() {}
