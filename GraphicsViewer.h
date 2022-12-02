#ifndef _GRAPHICSVIEWER_H_
#define _GRAPHICSVIEWER_H_
#include "observer.h"
#include "game.h"
#include "xWindow.h"

class GraphicsViewer: public Observer {
    Game *subject;
    const int top, bot, left, right;
    Xwindow *window;
    public:
        GraphicsViewer(Game *subject);
        void printPlayer(int row_start, int row_end,int x, int y, int player);
        void printTitle();
        void notify(bool over) override;
        void printOver();
        void printSummary();
        ~GraphicsViewer();
};

#endif

