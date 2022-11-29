#include <iostream>
#include "graphicsViewer.h"
using std::cout;
using std::endl;

const int rows = 20;
const int cols = 11;
const int dim = 20;


GraphicsViewer::GraphicsViewer(Game *subject): subject{subject}, top{0}, bot{60}, left{0}, right{60} {
    window = new Xwindow {(this->right-this->left+1) * 10, (this->bot-this->top+1) * 10};
    subject->attach(this);
}


GraphicsViewer::~GraphicsViewer() {
    subject->detach(this);
    delete window;
    window = nullptr;
}


void GraphicsViewer::printTitle() {
    window->drawString(200, 10, "Highest Score: " + std::to_string(subject->getHi()));
    window->drawString(20, 40, "Score: " + std::to_string(subject->getScore(0)));
    window->drawString(300, 40, "Score: " + std::to_string(subject->getScore(1)));
    window->drawString(20, 70, "Level: " + std::to_string(subject->getLevel(0)));
    window->drawString(300, 70, "Level: " + std::to_string(subject->getLevel(1)));
}

void GraphicsViewer::printPlayer(int row_start, int row_end,int x, int y, int player) {
    int color;
    for (int i = row_start; i <= row_end; ++i) {
        for (int j = 0; j < cols; ++j) {
            bool change = subject->getChange(player, i, j);
            char output = subject->getState(player, i, j);
            if (change) {
                if (output == '*') {
                    color = window->Brown;
                } else if (output == 'S') {
                    color = window->Blue;
                } else if (output == 'J') {
                    color = window->Cyan;
                } else if (output == 'Z') {
                    color = window->Magenta;
                } else if (output == 'O') {
                    color = window->Red;
                } else if (output == 'T') {
                    color = window->Orange;
                } else if (output == 'I') {
                    color = window->Green; 
                } else if (output == 'L') {
                    color = window->Yellow;
                } else if (output == '?') {
                    color = window->White;
                } else if (output == ' ') {
                    color = window->Black;
                }
            }
            window->fillRectangle(x + dim * j, y + dim * (i - row_start), dim, dim, color);
        }
    }
}


void GraphicsViewer::notify() {
    printTitle();
    printPlayer(0, 17, 20, 100, 0);
    printPlayer(0, 17, 300, 100, 0);
    window->drawString(20, 500, "Next: ");
    window->drawString(300, 500, "Next: ");
    printPlayer(18, 19, 20, 510, 0);
    printPlayer(18, 19, 300, 510, 0);
}



