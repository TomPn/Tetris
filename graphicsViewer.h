#ifndef _GRAPHICSVIEWER_H_
#define _GRAPHICSVIEWER_H_
#include "observer.h"
#include "game.h"
#include "xWindow.h"
#include <memory>

class GraphicsViewer: public Observer {
    Game *subject;
    const int top, bot, left, right;
    std::unique_ptr<Xwindow> window;
    void printPlayer(int row_start, int row_end,int x, int y, int player);
    void printTitle();
    void printSummary();
    public:
        GraphicsViewer(Game *subject);
        void notify(bool over) override;
        void clear() override;
        void prompt() override;
        ~GraphicsViewer();
};

#endif

