
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

void readIntoGrid(Grid<char>& life);
void openFile(ifstream& input);
Vector<int> resizeGrid(ifstream& input, Grid<char>& grid);
void fillInGrid(ifstream& input, Grid<char>& grid, const Vector<int>& size);
int countNeighbors(Grid<char>& grid, int r, int c);
void oneTick(Grid<char>& grid);
void cellUpdate(Grid<char>& grid, Grid<char>& copyLife, int r, int c, int neighbors);
void welcome();

int main() {
    Grid<char> life;
    welcome();
    readIntoGrid(life);
    oneTick(life);

    return 0;
}

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


void oneTick(Grid<char>& grid){
    int row = grid.numRows();
    int col = grid.numCols();
    Grid<char> copyLife(row,col);
    for(int r = 0; r < row; r++){
        for(int c = 0; c < col; c++){
            int neighbors = countNeighbors(grid, r, c);
            cout <<"row "<<r+1<<" column "<<c+1<<" has this number of neighbors "<<neighbors << endl;
            cellUpdate(grid, copyLife, r, c, neighbors);
        }
    }
    grid = copyLife;
    for(int r = 0; r < row; r++){
        for(int c = 0; c < col; c++){
            cout<<grid[r][c];
        }
        cout<<endl;
    }
}

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

int countNeighbors(Grid<char>& grid, int r, int c){
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


void fillInGrid(ifstream& input, Grid<char>& grid, const Vector<int>& size ){
    string line;
    int row = 0;
    /* this getline continues to read a file when the previous call to getline
     *  in resize greed function stopped reading*/
    while(getline(input, line)){
        // tokanize line we just have read
       istringstream input(line);
       for(int i = 0; i < size[1]; i++){
           input >> grid[row][i];
       }
        row++;
        if(row==size[0]) break;
    }
    input.close();
}

Vector<int> resizeGrid(ifstream& input, Grid<char>& grid){
    Vector<int> size;
    string line;
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
