
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include "console.h"
#include "filelib.h"
#include "grid.h"
#include "gwindow.h"
#include "simpio.h"
#include "lifegui.h"

// Feel free to add any other #includes you might need here

using namespace std;

void welcome();
// This block reads file input into grid
void readIntoGrid(Grid<char>& life);
void openFile(ifstream& input);
Vector<int> resizeGrid(ifstream& input, Grid<char>& grid);
void fillInGrid(ifstream& input, Grid<char>& grid, const Vector<int>& size);
//decides on neighbors counting algoritm
bool askIfWrap();
// This block updates grid to the next generation
void oneTick(Grid<char>& grid, bool wrap);
int countNeighborsNoWrap(Grid<char>& grid, int r, int c);
int countNeighborsWrapping(Grid<char>& grid, int r, int c);
void cellUpdate(Grid<char>& grid, Grid<char>& copyLife, int r, int c, int neighbors);

string animateTickQuit();
void computeGenerations(Grid<char>& life, bool toWrap, int NGenerations = 1);
// prints updated grid
void printGrid(Grid<char>& grid);


int main() {
    Grid<char> life;
    welcome();
    readIntoGrid(life);
    bool toWrap = askIfWrap();
    printGrid(life);
    // Game
    string gameFormat = animateTickQuit();
    while(gameFormat!="q"){
        if(gameFormat =="t"){
        computeGenerations(life, toWrap);
    }
        if(gameFormat =="a"){
            int frames = getInteger("How many frames? ");
            computeGenerations(life, toWrap, frames);
        }
        gameFormat = animateTickQuit();
    }
    return 0;
}

void computeGenerations(Grid<char>& life, bool toWrap, int NGenerations){
    for(int generation = 0; generation < NGenerations; generation++){
        pause(50);
        clearConsole();
        oneTick(life, toWrap);
        printGrid(life);

    }
}

string animateTickQuit(){
    string form;
    string gameForm = getLine("a)nimate, t)ick, q)uit ? ");
    while(!startsWith(gameForm,"t")&&!startsWith(gameForm,"a")&&!startsWith(gameForm,"q")){
        gameForm = getLine("a)nimate, t)ick, q)uit ? ");
    }
    if(startsWith(gameForm,"t")) form = "t";
    else if(startsWith(gameForm,"a")) form = "a";
    else if(startsWith(gameForm,"q")) form = "q";
    return form;
}

bool askIfWrap(){
    bool wrap = getYesOrNo("Should the simulation wrap around the grid (y/n) ? ", "Please, type in y or no");
    return wrap;
}

void printGrid(Grid<char>& grid){
    int row = grid.numRows();
    int col = grid.numCols();
    for(int r = 0; r < row; r++){
        for(int c = 0; c < col; c++){
            cout<<grid[r][c];
        }
        cout<<endl;
    }
    cout<<endl;
}
// reads file input into grid
void readIntoGrid(Grid<char>& grid){
    ifstream input;
    openFile(input);
    Vector<int> size = resizeGrid(input, grid);
    fillInGrid(input, grid, size);
}


/*     grid[r-1][c-1]        grid[r-1][c]     grid[r - 1][c + 1]
       grid[r][c - 1]        grid[r][c]       grid[r][c + 1]
       grid[r + 1][c - 1]    grid[r + 1][c]   grid[r + 1][c + 1]
*/

// updates original grid with cells for the next generation
void oneTick(Grid<char>& grid, bool wrap){
    int row = grid.numRows();
    int col = grid.numCols();
    Grid<char> copyLife(row,col);
    for(int r = 0; r < row; r++){
        for(int c = 0; c < col; c++){
            int neighbors;
            if(wrap)neighbors = countNeighborsWrapping(grid, r, c);
            else if(!wrap)neighbors = countNeighborsNoWrap(grid, r, c);
            cellUpdate(grid, copyLife, r, c, neighbors);
        }
    }
    grid = copyLife;
}

/* Updates a state of a cell  in a copy of a grid. Takes reference parameters of
 * original grid and copy grid, as well as row, column number of individual cell, number of
 * neigbors a cell has. We need a copy of grid, because we need to catch a previous state
 * of a colony and show the next generation of cells. If we change original grid, the state
 * of cells in next rows will be defined by current generation of cells, not the previous generation,
 * which is incorrect.
*/

void cellUpdate(Grid<char>& grid, Grid<char>& copyLife, int r, int c, int neighbors){
    if(neighbors==3){
        copyLife[r][c] = 'X';
    }
    else if(neighbors == 2){
        if(grid[r][c]=='X') copyLife[r][c] = 'X';
        if(grid[r][c]=='-') copyLife[r][c] = '-';
    }
    else{
        copyLife[r][c] = '-';
    }
}

int countNeighborsWrapping(Grid<char>& grid, int r, int c){
    int count = 0;
    return count;
}

int countNeighborsNoWrap(Grid<char>& grid, int r, int c){
    int count = 0;
    if(grid.inBounds(r-1, c-1)){
        if(grid[r-1][c-1] == 'X') count++;
    }
    if(grid.inBounds(r-1, c) ){
        if(grid[r-1][c] == 'X') count++;
    }
    if(grid.inBounds(r-1, c+1) ){
        if(grid[r-1][c+1] == 'X') count++;
    }
    if(grid.inBounds(r, c-1) ){
        if(grid[r][c-1] == 'X') count++;
    }
    if(grid.inBounds(r, c+1) ){
        if(grid[r][c+1] == 'X') count++;
    }
    if(grid.inBounds(r+1, c-1) ){
        if(grid[r+1][c-1] == 'X') count++;
    }
    if(grid.inBounds(r+1, c) ){
        if(grid[r+1][c] == 'X') count++;
    }
    if(grid.inBounds(r+1, c+1) ){
        if(grid[r+1][c+1] == 'X') count++;
    }
    return count;
}

// Fills in grid with input from a file.
void fillInGrid(ifstream& input, Grid<char>& grid, const Vector<int>& size ){
    string line;
    int row = 0;
    /* this getline continues to read a file from place when the previous call to
     * getline in resizeGrid function stopped reading*/
    while(getline(input, line)){
        // tokanize line we just have read
       istringstream input(line);
       for(int col = 0; col < size[1]; col++){
           input >> grid[row][col];
       }
        row++;
        // break when we reach actual height capacity of a grid
        if(row==size[0]) break;
    }
    input.close();
}

// resizes a grid with size provided in input file. returns grid size
Vector<int> resizeGrid(ifstream& input, Grid<char>& grid){
    Vector<int> size;
    string line;
    // loop 2 times, because on first two lines numbers for size of a grid are expected
    for(int i = 0; i < 2; i++){
        // if input is const, i cant readline on it
        getline(input, line);
        if(stringIsInteger(line)){
             int n = stringToInteger(line);
             size.add(n);
        }
    }
    grid.resize(size[0], size[1]);
return size;
}


// prompts user until it gives a valid  file name
void openFile(ifstream& input){
    string fileName = getLine("Enter a file name: ");
    input.open(fileName);
    while(input.fail()){
        cout << "Cant open that file " << endl;
        input.open(getLine("Enter a file name: "));
    }
}

// Print the welcome information.
void welcome() {
    cout << "Welcome to the CS 106B Game of Life, a simulation of the lifecycle of a bacteria colony." << endl;
    cout << "Cells (X) live and die by the following rules:" << endl;
    cout << "- A cell with 1 or fewer neighbors dies." << endl;
    cout << "- Locations with 2 neighbors remain stable." << endl;
    cout << "- Locations with 3 neighbors will create life." << endl;
    cout << "- A cell with 4 or more neighbors dies." << endl;
}

