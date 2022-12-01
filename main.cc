#include "game.h"
#include "observer.h"
#include "textViewer.h"
#include "graphicsViewer.h"
#include <sstream>
#include <iostream>
int main(int argc, char **argv) {
    bool textMode = 0;
    bool haveSeed = 0;
    bool haveScript1 = 0;
    bool haveScript2 = 0;
    unsigned int seed;
    int startLevel = 0;
    std::string scriptfile1;
    std::string scriptfile2;
    for (int argi = 0; argi < argc; ++argi) {
        std::string flag = argv[argi];
        if (flag == "-text") {
            textMode = 1;
        } else if (flag == "-seed") {
            haveSeed = 1;
            std::stringstream os;
            os << argv[argi+1];
            os >> seed;
            ++argi;
        } else if (flag == "-scriptfile1") {
            haveScript1 = 1;
            scriptfile1 = argv[argi+1];
            ++argi;
        } else if (flag == "-scriptfile2") {
            haveScript2 = 1;
            scriptfile2 = argv[argi+1];
            ++argi;
        } else if (flag == "-startlevel") {
            std::stringstream os;
            os << argv[argi+1];
            os >> startLevel;
            ++argi;
        }
    }
    std::vector<Observer*> observers;
    Game * game = new Game{startLevel, seed, haveSeed, haveScript1, haveScript2, scriptfile1, scriptfile2};
    observers.emplace_back(new TextViewer{game});
    if (!textMode)  {observers.emplace_back(new GraphicsViewer{game});}
    game->start();
    delete game;
}
