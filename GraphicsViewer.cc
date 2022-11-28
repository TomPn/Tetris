#include <iostream>
#include "graphicsViewer.h"
using std::cout;
using std::endl;

GraphicsViewer::GraphicsViewer(Game *subject): subject{subject}, top{0}, bot{250}, left{0}, right{280} {
    window = new XWindow {(this->right-this->left+1)*10, (this->bot-this->top+1)*10};
    subject->attach(this);
}

GraphicsViewer::~GraphicsViewer() {
    subject->detach(this);
    delete window;
    window = nullptr;
}

void TextViewer::notify() {
    // for (int row = top; row < bot; ++row) {
    //     // print the first line of the game
    //     if (row == 0) {
    //         for (int i = 0; i < 2; ++i) {
    //             // each player's level
    //             out << "Level:";
    //             for (int j = 0; j < 4; ++j) out << ' ';
    //             out << subject->getLevel(i);
    //             // print the space between the first player and the second player
    //             if (i == 0) {
    //                 for (int j = 0; j < 6; ++j) out << ' ';
    //             }
    //         }
    //         out << endl;
    //     } else if (row == 1) {
    //         for (int i = 0; i < 2; ++i) {
    //             // each player's level
    //             out << "Score:";
    //             for (int j = 0; j < 4; ++j) out << ' ';
    //             out << subject->getScore(i);
    //             // print the space between the first player and the second player
    //             if (i == 0) {
    //                 for (int j = 0; j < 6; ++j) out << ' ';
    //             }
    //         }
    //         out << endl;
    //     } else if (row == 2 || row == 21) {
    //         // print the breakline between the statistics and the actual game
    //         for (int col = left; col < right; ++col) out << '-';
    //         out << endl;
    //     } else if (row == 22) {
    //         // print the Next section for both players
    //         out << "Next:";
    //         for (int j = 0; j < 10; ++j) out << ' ';
    //         out << "Next:" << endl;
    //     } else {
    //         // print the actual games
    //         for (int col = left; col < right; ++col) {
    //             out << subject->getState(row, col);
    //         }
    //         out << endl;
    //     }
    // }
}
