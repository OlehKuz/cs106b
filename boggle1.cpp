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
    Grid<string> g (BOARD_SIZE,BOARD_SIZE);
    shakenCubes = g;
    validWords = dictionary;
    if(boardText != ""){
        board = toUpperCase(boardText);
        stringIntoGrid(board, shakenCubes);

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
string Boggle::getLetter(int row, int col) {
    if(row > BOARD_SIZE - 1 || row < 0){
        throw(row);
    }
    if(col < 0 || col > BOARD_SIZE - 1 ){
        throw(col);
    }
    else{
        return shakenCubes[row][col];
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
    copyArrayIntoGrid(shakenCubes);
    shakeBoard(shakenCubes);
    return chooseOneChar(shakenCubes);
}
string Boggle:: chooseOneChar(Grid <string>& grid){
    cout << grid << endl;
    string s = "";
    for(int i = 0; i < BOARD_SIZE; i++){
        for(int j = 0; j < BOARD_SIZE; j++){
            int random = randomInteger(0, SIDES_IN_CUBE - 1);
            string cube = grid[i][j];
            grid[i][j] = cube[random];
            s += grid[i][j];
        }
    }
    return s;
}

void Boggle::copyArrayIntoGrid(Grid <string>& grid){
    int count = 0;
    for(int i = 0; i < BOARD_SIZE; i++){
        for(int j = 0; j < BOARD_SIZE; j++){
            grid[i][j] = CUBES[count++];
        }

    }
}
void Boggle::shakeBoard(Grid <string>& shakenCubes){
    string s = "";
    for(int i = 0; i < BOARD_SIZE; i++){
        for(int j = 0; j < BOARD_SIZE; j++){
            int row = randomInteger(i, BOARD_SIZE - 1);
            int col = randomInteger(j, BOARD_SIZE - 1);
            string temp = shakenCubes[i][j];
            shakenCubes[i][j] = shakenCubes[row][col];
            shakenCubes[row][col] = temp;
        }
    }
}

void Boggle:: stringIntoGrid(string source, Grid <string> & addHere){
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
