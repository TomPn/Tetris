#include <iostream>
#include "textViewer.h"
using std::cout;

TextViewer::TextViewer(Game *subject): subject{subject}, top{0}, bot{24}, left{0}, right{28} {
    subject->attach(this);
}

TextViewer::~TextViewer() {
    subject->detach(this);
}

void TextViewer::notify() {
//   out << '+';
//   for (int j = left; j <= right; ++j) out << '-';
//   out << '+' << std::endl;
//   for (int i = top; i <= bot; ++i) {
//     out << '|';
//     for (int j = left; j <= right; ++j) {
//       out << subject->getState(i, j);
//     }
//     out << '|' << std::endl;
//   }
//   out << '+';
//   for (int j = left; j <= right; ++j) out << '-';
//   out << '+' << std::endl;
}
