#include <iostream>
#include "graphicsViewer.h"
using std::cout;
using std::endl;

const int rows = 20;
const int cols = 11;
const int dim = 20;

GraphicsViewer::GraphicsViewer(Game *subject) : Observer{false}, subject{subject}, top{0}, bot{65}, left{0}, right{60}
{
    window = new Xwindow{(this->right - this->left + 1) * 10, (this->bot - this->top + 1) * 10};
    subject->attach(this);
}


GraphicsViewer::~GraphicsViewer()
{
    subject->detach(this);
    delete window;
    window = nullptr;
}


void GraphicsViewer::printTitle() {
    window->fillRectangle(200, 10, 10, 30, window->White);
    window->drawString(200, 10, "Highest Score: " + std::to_string(subject->getHiScore()));
    window->drawString(20, 30, "Player1:  " + subject->getName(0));
    window->drawString(300, 30, "Player2:  " + subject->getName(1));
    window->fillRectangle(20, 50, 10, 30, window->White);
    window->drawString(20, 50, "Score: " + std::to_string(subject->getScore(0)));
    window->fillRectangle(300, 50, 10, 30, window->White);
    window->drawString(300, 50, "Score: " + std::to_string(subject->getScore(1)));
    window->fillRectangle(20, 70, 10, 30, window->White);
    window->drawString(20, 70, "Level: " + std::to_string(subject->getLevel(0)));
    window->fillRectangle(300, 70, 10, 30, window->White);
    window->drawString(300, 70, "Level: " + std::to_string(subject->getLevel(1)));
}


void GraphicsViewer::printPlayer(int row_start, int row_end, int x, int y, int player)
{
    int color;
    for (int i = row_start; i <= row_end; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            bool change = subject->getChange(player, i, j);
            char output = subject->getState(player, i, j);

            if (change)
            {
                if (output == '*')
                {
                    color = window->Brown;
                }
                else if (output == 'S')
                {
                    color = window->Blue;
                }
                else if (output == 'J')
                {
                    color = window->Cyan;
                }
                else if (output == 'Z')
                {
                    color = window->Magenta;
                }
                else if (output == 'O')
                {
                    color = window->Red;
                }
                else if (output == 'T')
                {
                    color = window->Orange;
                }
                else if (output == 'I')
                {
                    color = window->Green;
                }
                else if (output == 'L')
                {
                    color = window->Yellow;
                }
                else if (output == '?')
                {
                    color = window->White;
                }
                else if (output == ' ')
                {
                    if (i >= 18) {
                        color = window->White;
                    } else {
                        color = window->Black;
                    }
                }
                window->fillRectangle(x + (dim * j), y + dim * (i - row_start), dim, dim, color);
            }
        }
    }
}

void GraphicsViewer::printOver() {
    //finish later
}

void GraphicsViewer::printSummary() {
    window->drawString(250, 30 ,"Game Summary");
    window->drawString(150, 50, subject->getName(0) + "'s score: " + std::to_string(subject->getScore(0)));
    window->drawString(350, 50, subject->getName(1) + "'s score: " + std::to_string(subject->getScore(1)));
    if (subject->getScore(0) > subject->getScore(1)) {
        window->drawString(220, 150, subject->getName(0) + " won!");
    } else if (subject->getScore(0) < subject->getScore(1)) {
        window->drawString(220, 150, subject->getName(0) + " won!");
    } else {
        window->drawString(250, 150, " tie!");
    }
}

void GraphicsViewer::notify(bool over)
{
    if (over) {
        window->fillRectangle(0, 0, 600, 600, window->White);
        printOver();
        printSummary();
        window->drawString(100, 200, "Enter ENDGAME to end the game or restart to restart the game");
        
    } else {
        printTitle();
        printPlayer(0, 17, 20, 100, 0);
        printPlayer(0, 17, 300, 100, 1);
        window->drawString(20, 500, "Next: ");
        window->drawString(300, 500, "Next: ");
        printPlayer(18, 19, 20, 510, 0);
        printPlayer(18, 19, 300, 510, 1);
    }
}

