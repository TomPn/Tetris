#ifndef _TEXTVIEWER_H_
#define _TEXTVIEWER_H_
#include "observer.h"
#include "game.h"

class TextViewer: public Observer {
    Game *subject;
    const int top, bot, left, right;
    std::ostream &out = std::cout;

    public:
        TextViewer(Game *subject);
        void notify() override;
        ~TextViewer();
}; 

#endif
