#ifndef _TEXTVIEWER_H_
#define _TEXTVIEWER_H_
#include <string>
#include "observer.h"
#include "game.h"

class TextViewer : public Observer
{
    Game *subject;
    std::ostream &out = std::cout;
    void printData(std::string dataType);
    void printLine();
    void printGrid();
    void printSummary();

public:
    TextViewer(Game *subject);
    void notify(bool over) override;
    void prompt() override;
    void clear() override;
    ~TextViewer();
};

#endif
