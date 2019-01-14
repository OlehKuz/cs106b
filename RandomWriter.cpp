// This is the CPP file you will edit and turn in. (TODO: Remove this comment!)

#include <iostream>
#include <string>
#include <fstream>
#include "console.h"
#include "simpio.h"
#include "vector.h"
#include "string.h"
#include "hashmap.h"
#include "linkedlist.h"
#include "random.h"

using namespace std;
void openFile(ifstream& input);
int buildMap(HashMap<Vector<string>,Vector<string> > &nGram, ifstream &input);
void printRandomText(HashMap<Vector<string>,Vector<string> > &nGram, const int &filesize);

int main() {
    cout << "Welcome to CS 106B Random Writer ('N-Grams')." << endl
         << "This program makes random text based on a document." << endl
         << "Give me an input file and an 'N' value for groups" << endl
         << "of words, and I'll create random text for you." << endl;
    ifstream input;
    openFile(input);
    HashMap<Vector<string>,Vector<string> > nGram;
    int fileSize = buildMap(nGram, input);
    printRandomText(nGram, fileSize);



    cout << "Exiting." << endl;
    return 0;
}

void printRandomText(HashMap<Vector<string>,Vector<string> > &nGram, const int &filesize){
    Vector<Vector<string> > keySet = nGram.keys();
    int keySize = keySet[0].size();
    while(true){
        int lengthText = -1;
        while(lengthText > filesize-1 || lengthText<keySize+1){
            lengthText = getInteger("# of random words to generate (0 to quit)?");
            if(lengthText==0) return;
            if(lengthText < keySize+1) {
                cout << "Minimum number of words is" << keySize+1 << endl;
            }
            if(lengthText>filesize-1) {
                cout << "Generated text cannot exceed "
                        "the length of original text of " << filesize-1<< "characters"<<endl;
            }
        }
        int randomKey = randomInteger(0, keySet.size()-1);
        Vector<string> nMinusOne = keySet[randomKey];
        for(string firstKeyPrint:nMinusOne){
            cout << firstKeyPrint << " ";// prints first random key
        }

        int printedTextLen = nMinusOne.size();
        while(printedTextLen < lengthText){
            int lenValue = nGram.get(nMinusOne).size();
            int randomValue = randomInteger(0, lenValue-1);
            string value = nGram.get(nMinusOne)[randomValue];
            cout << value << " ";
            printedTextLen++;
            nMinusOne.add(value);
            nMinusOne.removeFront();
        }
        cout << endl;
    }
}

/* Map of all possible next words(values) that follow a combination
 * of N consequetive words (keys), as read from file that user supplies
*/
int buildMap(HashMap<Vector<string>,Vector<string> > &nGram, ifstream &input){
    int n;
    // ask user how many consequtive words should be from original text
    while(true){
        n = getInteger("Value of N: ");
        if(n>=2)break;
        cout << "N must be 2 or greater." << endl;
    }
    Vector<string> key; // contains n - 1 words
    Vector<string> value;

    //contains n words for disecting them into key-value pairs
    LinkedList<string> row;

    // saves words for wrap to the first line
    Vector<string> firstKey;

    string word;
    int fileSize = 0;
    // while input file has more words that can be put into key-value pairs, put them to nGram map
    while(input >> word){
        row.add(word);
        fileSize++;
        if(fileSize>=n){
            for(int i = 0; i < n - 1; i++){
                key.add(row[i]);
            }
            value.add(row[n-1]);
            if(nGram.containsKey(key)){
                nGram.put(key, nGram.get(key)+value);
            }
            else if(!nGram.containsKey(key)){
                nGram.put(key, value);
            }
            // remove the first element from linked list, to make place for adding the next word
            row.remove(0);
            key.clear();
            value.clear();
        }else{
            firstKey.add(word);
        }
    }
    /* words that didnt have value pairs(that were at the end of a text) are added the value pair
        from the start of a text (first read in key, that is stored in firstkey vector )*/
    int wrapSize = row.size();  // n-1
    /* add left over words to key, shifting by one index of word that is due to be added to a key,
    each time we use that word in a key*/
    for(int out = 0; out < wrapSize;out++){
        for(int s = out; s < wrapSize; s++){
            key.add(row[s]);
        }
        /* if needed , add to left over words words from first key,in order to form
         * n-1 consequent words, that will map to next word
         * wrapSize-out - for how many left over words we still need to form key-value pairs
        */
        for(int firstWr = 0; firstWr < n - (wrapSize - out) -1; firstWr++){
            key.add(firstKey[firstWr]);
        }
        value.add(firstKey[n - (wrapSize - out)-1]);
        if(nGram.containsKey(key)){
            nGram.put(key, nGram.get(key)+value);
        }
        else if(!nGram.containsKey(key)){
            nGram.put(key, value);
        }
        key.clear();
        value.clear();
    }
    return fileSize;
}

// opens file and reads in words into supplied hashset parameter
void openFile(ifstream& input){
    while(true){
            string filename = getLine("Input file name: ");
            input.open(filename);
            if(input.is_open()) break;
            else{
                cout << "Can't open that file. Try again." << endl;
            }
    }
}
