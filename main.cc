#include "game.h"
#include <sstream>

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
        if (argv[argi] == "-text") {
            textMode = 1;
        } else if (argv[argi] == "-seed") {
            haveSeed = 1;
            std::stringstream os;
            os << argv[argi+1];
            os >> seed;
            ++argi;
        } else if (argv[argi] == "-scriptfile1") {
            haveScript1 = 1;
            scriptfile1 = argv[argi+1];
            ++argi;
        } else if (argv[argi] == "-scriptfile2") {
            haveScript2 = 1;
            scriptfile2 = argv[argi+1];
            ++argi;
        } else if (argv[argi] == "-startlevel") {
            std::stringstream os;
            os << argv[argi+1];
            os >> startLevel;
            ++argi;
        }
    }
    Game * game = new Game{startLevel, textMode, seed, haveSeed, haveScript1, haveScript2, scriptfile1, scriptfile2};
    game->start();
    delete game;
}