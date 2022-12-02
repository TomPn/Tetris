#include "game.h"
#include "observer.h"
#include "textViewer.h"
#include "graphicsViewer.h"
#include <sstream>
#include <iostream>
#include <memory>

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
    auto game = std::make_unique<Game>(startLevel, seed, haveSeed, haveScript1, haveScript2, scriptfile1, scriptfile2);
    TextViewer observer1{game.get()};
    std::unique_ptr<GraphicsViewer> observer2;
    if (!textMode) {
        observer2 = std::make_unique<GraphicsViewer>(game.get());
    }
    game->setNames();
    game->start();
}
