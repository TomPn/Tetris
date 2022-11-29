#include <iostream>
#include "graphicsViewer.h"
using std::cout;
using std::endl;

const int rows = 20;
const int cols = 11;
const int dim = 10;

GraphicsViewer::GraphicsViewer(Game *subject) : Observer{false}, subject{subject}, top{0}, bot{65}, left{0}, right{60}
{
    window = new Xwindow{(this->right - this->left + 1) * 10, (this->bot - this->top + 1) * 10};
    cout << "constructor" << subject->getState(0, 0, 0) << endl;
    subject->attach(this);
}

GraphicsViewer::~GraphicsViewer()
{
    subject->detach(this);
    delete window;
    window = nullptr;
}

void GraphicsViewer::printTitle()
{
    window->drawString(100, 10, "Highest Score" + std::to_string(subject->getHiScore()));
    window->drawString(10, 40, "Score: " + std::to_string(subject->getScore(0)));
    window->drawString(200, 40, "Score: " + std::to_string(subject->getScore(1)));
    window->drawString(10, 70, "Level: " + std::to_string(subject->getLevel(0)));
    window->drawString(200, 70, "Level: " + std::to_string(subject->getLevel(1)));
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
                    color = window->Black;
                }
            }
            cout << "i: " << i << "j: " << j << endl;
            window->fillRectangle(x + dim * (j - cols), y + dim * (i - rows), dim, dim, color);
        }
    }
}

void GraphicsViewer::notify()
{
    printTitle();
    cout << "title" << endl;
    cout << subject->getState(0, 0, 0) << endl;
    printPlayer(0, 17, 10, 100, 0);
    cout << "player1" << endl;
    printPlayer(0, 17, 200, 100, 0);
    cout << "player2" << endl;
    window->drawString(10, 400, "Next: ");
    window->drawString(200, 400, "Next: ");
    printPlayer(18, 19, 10, 100, 0);
    cout << "next1" << endl;
    printPlayer(18, 19, 200, 100, 0);
    cout << "next2" << endl;
}
