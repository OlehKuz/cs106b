// This is a .cpp file you will edit and turn in.
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header
#include "random.h"
#include "Boggle.h"
#include <iostream>

using namespace std;

const int pointPerGuess = 1;
// letters on all 6 sides of every cube
static string CUBES[16] = {
    "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
    "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
    "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
    "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
};

// letters on every cube in 5x5 "Big Boggle" version (extension)
static string BIG_BOGGLE_CUBES[25] = {
   "AAAFRS", "AAEEEE", "AAFIRS", "ADENNN", "AEEEEM",
   "AEEGMU", "AEGMNN", "AFIRSY", "BJKQXZ", "CCNSTW",
   "CEIILT", "CEILPT", "CEIPST", "DDLNOR", "DDHNOT",
   "DHHLOR", "DHLNOR", "EIIITT", "EMOTTT", "ENSSSU",
   "FIPRSY", "GORRVW", "HIPRRY", "NOOTUW", "OOOTTU"
};


Boggle::Boggle(Lexicon& dictionary, string boardText) {
    validWords = dictionary;
    if(boardText != ""){
        board = toUpperCase(boardText);
        stringIntoVector(board, shakenCubes);

    }else {       
        board = getRandomCubes();
    }
    humanScore = 0;
    computerScore = 0;
    cout << shakenCubes << endl;

}
void Boggle:: addToGuessed(string word, int n){
    switch(n){
        case 0 :
        playerGuessedWords.add(word);
        humanScore += pointPerGuess;
        break;
        default:
        computerGuessedWords.add(word);
        computerScore += pointPerGuess;
        break;
        }
}

Set<string> Boggle:: getGuessedWords(int n){
    switch(n){
        case 0 : return playerGuessedWords;
    default: return computerGuessedWords;
    }

}
string Boggle::getLetter(int row, int col) {
    int height = shakenCubes.size();
    int width = shakenCubes[0].size();
    if(row > height - 1 || row < 0){
        throw(row);
    }
    if(width < 0 || col > width - 1 ){
        throw(col);
    }
    else{
        return shakenCubes[row, col];
    }
      // remove this
}

bool Boggle::checkWord(string word) {
    string upperCaseWord = toUpperCase(word);
    return upperCaseWord.length() >= 4 &&
                       validWords.contains(upperCaseWord)&&
                       !(playerGuessedWords.contains(upperCaseWord)||
                         computerGuessedWords.contains(upperCaseWord));
}

bool Boggle::humanWordSearch(string word) {

    shakenCubes
    return false;   // remove this
}

int Boggle::getScoreHuman() {
    return humanScore;   // remove this
}

Set<string> Boggle::computerWordSearch() {
    // TODO: implement
    Set<string> result;   // remove this
    return result;        // remove this
}

int Boggle::getScoreComputer() {
    // TODO: implement
    return 0;   // remove this
}

ostream& operator<<(ostream& out, Boggle& boggle) {
    // TODO: implement
    return out;
}

string Boggle:: getboardCubes(){
    return board;
}

//   private

string Boggle:: getRandomCubes(){
    shakenCubes = copyArrayIntoVector();
    shakeBoard(shakenCubes);
    return chooseRandomChars(shakenCubes);
}


Vector <string> Boggle::copyArrayIntoVector(){
    Vector <string> copied ;
    for(string cube : CUBES){
        copied.add(cube);
    }
    return copied;
}
void Boggle::shakeBoard(Vector <string>& shakenCubes){
        cout << shakenCubes << endl;
    int len = shakenCubes.size();
    for(int cube = 0; cube < len; cube++){
        int index = randomInteger(0, len - 1);
        string temp = shakenCubes[cube];
        shakenCubes[cube] = shakenCubes[index];
        shakenCubes[index] = temp;
    }
        cout << shakenCubes << endl;
}

string Boggle::chooseRandomChars(Vector <string>& shakenCubes){
    string s = "";
    int len = shakenCubes[0].size();
    for(int c = 0; c < shakenCubes.size(); c++){
        int index = randomInteger(0, len - 1);
        shakenCubes[c] = shakenCubes[c][index];
        s += shakenCubes[c];
    }
    cout << shakenCubes << endl;
    return s;

}

void Boggle:: stringIntoVector(string source, Vector<string> & addHere){
    int len = source.length();
    for(int i = 0; i < len; i++){
        addHere.add(source.substr(i,1));
    }
}
/*string vectorIntoString(const Vector <string> & v){

    int len = v.size();
    for(int i = 0; i < len; i++){
       s += v.get(i);
    }
    return s;
}
*/
