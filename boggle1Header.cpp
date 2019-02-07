// This is a .h file you will edit and turn in.
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#ifndef _boggle_h
#define _boggle_h

#include <iostream>
#include <string>
#include "lexicon.h"
#include "grid.h"
using namespace std;

class Boggle {
public:
    Boggle(Lexicon& dictionary, string boardText = "");
    string getLetter(int row, int col);
    bool checkWord(string word);
    bool humanWordSearch(string word);
    Set<string> computerWordSearch();
    int getScoreHuman();
    int getScoreComputer();

    string getboardCubes();
    Set<string> getGuessedWords(int n);
    void addToGuessed(string word, int n);
    friend ostream& operator<<(ostream& out, Boggle& boggle);

private:
    void stringIntoGrid(string source, Grid<string> & addHere);
    Set<string> playerGuessedWords;
    Set<string> computerGuessedWords;
    Lexicon validWords;
    int computerScore;
    int humanScore;
    string board;
    Grid<string> shaken;
    Vector<string> shakenCubes;
    string chooseRandomChars( Vector <string>& shakenCubes);
    void copyArrayIntoGrid(Grid <string> & grid);

    string getRandomCubes();
    void shakeBoard(Grid <string>& shakenCubes);

    string chooseOneChar(Grid <string>& grid);
};

#endif // _boggle_h
