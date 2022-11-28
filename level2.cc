#include "level2.h"
#include <string>
#include <cstdlib>

class Block;

Block * Level2::CreateNextBlock(){
    Block * nextBlock;
    // set up the seed
    if(seedBool ==true){
        std::srand(seed);
    }
    // random is a random int from 1 to 7
    int random = 1 + std::rand()/((RAND_MAX + 1u)/7);
    if(random == 1){
        nextBlock = Level::CreateSBlock(2);
    }else if(random == 2){
        nextBlock = Level::CreateZBlock(2);
    }else if(random == 3){
        nextBlock = Level::CreateIBlock(2);
    }else if(random == 4){
        nextBlock = Level::CreateJBlock(2);
    }else if(random == 5){
        nextBlock = Level::CreateTBlock(2);
    }else if(random == 6){
        nextBlock = Level::CreateOBlock(2);
    }else if(random == 7){
        nextBlock = Level::CreateOLlock(2);
    }
    return nextBlock;
}

Level2::~Level2() {}
