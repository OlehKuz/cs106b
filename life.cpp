
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
void welcome();

int main() {
    Grid<char> life;
    welcome();
    readIntoGrid(life);

    return 0;
}

void readIntoGrid(Grid<char>& grid){
    ifstream input;
    openFile(input);
    Vector<int> size = resizeGrid(input, grid);
    fillInGrid(input, grid, size);
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

    cout<<grid.toString();
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
