#ifndef _TEXTVIEWER_H_
#define _TEXTVIEWER_H_
#include <string>
#include "observer.h"
#include "game.h"

class TextViewer : public Observer
{
    Game *subject;
    std::ostream &out = std::cout;

public:
    TextViewer(Game *subject);
    void notify() override;
    void prompt() override;
    void printData(std::string dataType);
    void printLine();
    ~TextViewer();
};

#endif
