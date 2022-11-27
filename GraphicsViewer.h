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
        GraphicViewer(Game *subject);
        void notify() override;
        ~GraphicViewer();
};

#endif
