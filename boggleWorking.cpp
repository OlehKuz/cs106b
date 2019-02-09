
// This is a .cpp file you will edit and turn in.
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header
#include "random.h"
#include "Boggle.h"
#include <iostream>

using namespace std;

const int BOARD_SIZE = 4;
const int POINT_PER_GUESS = 1;
const int SIDES_IN_CUBE = 6;
const int COMPUTER_EN = 1;

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
    Grid<char> g (BOARD_SIZE,BOARD_SIZE);
    shaken = g;
    validWords = dictionary;
    if(boardText != ""){
        board = toUpperCase(boardText);
    }else {
        board = getRandomCubes();
    }
    stringIntoGrid(board, shaken);
    humanScore = 0;
    computerScore = 0;
    cout << shakenCubes << endl;
        cout << shaken << endl;

}
void Boggle:: addToGuessed(string word, int n){
    word = toUpperCase(word);
    switch(n){
        case 0 :
        playerGuessedWords.add(word);
        humanScore += POINT_PER_GUESS;
        break;
        default:
        computerGuessedWords.add(word);
        computerScore += POINT_PER_GUESS;
        break;
        }
}

Set<string> Boggle:: getGuessedWords(int n){
    switch(n){
        case 0 : return playerGuessedWords;
    default: return computerGuessedWords;
    }

}
char Boggle::getLetter(int row, int col) {
    if(row > BOARD_SIZE - 1 || row < 0){
        return '-';
        //throw(row);
    }
    if(col < 0 || col > BOARD_SIZE - 1 ){
        return '-';
        //throw(col);
    }
    else{
        return shaken[row][col];
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

bool Boggle:: humanSearchHelp(const string &word, int index, int row, int col){
    if(index == word.length()){
        return true;
    }else{
         char ch = getLetter(row, col);
            if(ch == '-') return false;
            else if(ch == word[index]){
                for(int c = -1; c <=1; c++){
                    for(int r = -1; r <= 1; r++){
                        if(c == 0 && r == 0){
                            // initial position
                        }else{
                            bool hasWord = humanSearchHelp(word, index + 1, row + r, col + c);
                            if(hasWord){
                                return true;
                            }
                        }
                    }
                }
                return false;
            }
            else{
                return false;
            }
        }
    }

bool Boggle::humanWordSearch(string word) {
    string upperCaseWord = toUpperCase(word);
    for(int i = 0; i < BOARD_SIZE; i++){
        for(int j = 0; j < BOARD_SIZE; j++){
            if(humanSearchHelp(upperCaseWord, 0, i,j)){
                return true;
            }
        }
    }
    return false;
}

int Boggle::getScoreHuman() {
    return humanScore;   // remove this
}

void Boggle:: computerWordSearchHelp(string formedWord, int row, int col){
    if(checkWord(formedWord)){
            computerGuessedWords.add(formedWord);
    }
    if(validWords.containsPrefix(formedWord)){
        for(int r = -1; r <= 1; r++){
            for(int c = -1; c <= 1; c++){
                char ch = getLetter(row + r, col + c);
                if((c == 0 && r == 0) || ch == '-'){
                    // initial position
                }else{
                    computerWordSearchHelp(formedWord + ch, row + r, col + c);
                }
            }
        }
    }
}

Set<string> Boggle::computerWordSearch() {
  // remove this
    for(int i = 0; i < BOARD_SIZE; i++){
        for(int j = 0; j < BOARD_SIZE; j++){
            computerWordSearchHelp("", i, j);
        }
    }
    Set<string> result = computerGuessedWords;
    return result;
}

int Boggle::getScoreComputer() {
    return computerGuessedWords.size();   // remove this
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
    int len = shakenCubes.size();
    for(int cube = 0; cube < len; cube++){
        int index = randomInteger(cube, len - 1);
        string temp = shakenCubes[cube];
        shakenCubes[cube] = shakenCubes[index];
        shakenCubes[index] = temp;
    }
}

string Boggle::chooseRandomChars(Vector <string>& shakenCubes){
    string s = "";
    int len = shakenCubes[0].size();
    for(int c = 0; c < shakenCubes.size(); c++){
        int index = randomInteger(0, len - 1);
        shakenCubes[c] = shakenCubes[c][index];
        s += shakenCubes[c];
    }
    return s;

}

void Boggle:: stringIntoGrid(string source, Grid <char> & addHere){
    int count = 0;
    for(int i = 0; i < BOARD_SIZE; i++){
        for(int j = 0; j < BOARD_SIZE; j++){
            addHere[i][j] = source[count];
            count++;

        }


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

