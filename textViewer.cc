#include <iostream>
#include "textViewer.h"
using std::cout;
using std::endl;

const int rows = 20;
const int cols = 11;

TextViewer::TextViewer(Game *subject) : subject{subject}
{
    subject->attach(this);
}

TextViewer::~TextViewer()
{
    subject->detach(this);
}

void TextViewer::prompt()
{
    cout << "Choose your special actions(heavy, blind, or force):" << endl;
}

void TextViewer::printLine()
{
    for (int j = 0; j < cols; j++)
    {
        out << "-";
    }
    out << "          ";
    for (int j = 0; j < cols; j++)
    {
        out << "-";
    }
    out << endl;
}
void TextViewer::printData(std::string dataType)
{
    std::string output;
    if (dataType == "Score")
    {
        output = dataType + " " + std::to_string(subject->getScore(0));
    }
    else if (dataType == "Level")
    {
        output = dataType + " " + std::to_string(subject->getLevel(0));
    }
    int wsLength = cols - output.length();
    for (int i = 0; i < wsLength; i++)
    {
        output += " ";
    }
    out << output << "          ";
    if (dataType == "Score")
    {
        out << "Score: " << subject->getScore(1) << endl;
    }
    else if (dataType == "Level")
    {
        out << "Level: " << subject->getLevel(1) << endl;
    }
}

void TextViewer::notify()
{
    out << "      Highest Score:" << subject->getHiScore() << endl;
    for (int j = 0; j < cols * 2 + 10; j++)
    {
        out << "-";
    }
    out << endl
        << endl;
    printData("Score");
    printData("Level");
    printLine();
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            out << subject->getState(0, i, j);
        }
        out << "          ";
        for (int j = 0; j < cols; j++)
        {
            out << subject->getState(1, i, j);
        }
        out << endl;
        if (i == 17)
        {
            printLine();
            out << "Next:                Next: " << endl;
        }
    }
    for (int j = 0; j < cols; j++)
    {
        out << "-";
    }
    out << "          ";
    for (int j = 0; j < cols; j++)
    {
        out << "-";
    }
    out << endl;
}
