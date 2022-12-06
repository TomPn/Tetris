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
        output = dataType + ": " + std::to_string(subject->getLevel(0));
    } 
    else if (dataType == "Bonus")
    {
        output = dataType + ": " + std::to_string(subject->getBonus(0));
    }
    else if (dataType == "Player") 
    {
        output = dataType + ": " + subject->getName(0);
    }
    else if (dataType == "Status") {
        if (subject->getOver(0) == 1) {
            output = dataType + ": Dead";
        } else {
            output = dataType + ": Alive";
        }
    }
    int wsLength = cols + 10 - output.length();
    for (int i = 0; i < wsLength; i++)
    {
        output += " ";
    }
    out << output;
    if (dataType == "Score")
    {
        out << dataType << ": " << subject->getScore(1) << endl;
    }
    else if (dataType == "Level")
    {
        out << dataType << ": " << subject->getLevel(1) << endl;
    }
    else if (dataType == "Bonus")
    {
        out << dataType << ": " << subject->getBonus(1) << endl;
    }
    else if (dataType == "Player") 
    {
        out << dataType << ": " << subject->getName(1) << endl;
    }
    else if (dataType == "Status") {
        if (subject->getOver(1) == 1) {
            out << dataType << ": Dead" << endl;
        } else {
            out << dataType << ": Alive" << endl;
        }
    }
}

void TextViewer::clear() {}


void TextViewer::printGrid() {
    out << "        Highest Score:" << subject->getHiScore() << endl;

    for (int j = 0; j < cols * 2 + 10; j++)
    {
        out << "-";
    }
    out << endl
        << endl;
    printData("Player");
    printData("Score");
    printData("Bonus");
    printData("Level");
    printData("Status");
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
    out << "Please enter your command: " << endl;
}


void TextViewer::printSummary() {
    out << "                   GAME OVER" << endl;
    out << " Game Summary:" << endl << endl;
    int p1Total = subject->getScore(0) + subject->getBonus(0);
    int p2Total = subject->getScore(1) + subject->getBonus(1);
    out << " Player: "<< subject->getName(0) << "'s score: " << subject->getScore(0)  << "  bonus: " << subject->getBonus(0)<< "  total: " << p1Total << endl;
    out << " Player: "<< subject->getName(1) << "'s score: " << subject->getScore(1) << "  bonus: " << subject->getBonus(1)<< "  total: " << p2Total << endl;
    if (p1Total > p2Total) {
        out << "                 Player: "<< subject->getName(0) << " won!" << endl << endl;
    } else if (p1Total < p2Total){
        out << "                 Player: "<< subject->getName(1) << " won!" << endl << endl;
    } else {
        out << "                      Tie!" << endl << endl;
    }
    out << "Enter ENDGAME to end the game or restart to restart the game" << endl;
}


void TextViewer::notify(bool over)
{
    if (over) {
        printSummary();
    } else {
        printGrid();
    }
}
