#include <iostream>
#include <cmath>
#include "console.h"
#include "simpio.h"  // for getLine
#include "vector.h"  // for Vector
using namespace std;

// Transposition Cipher

const char PAD = '~'; // padding character for cipher

// Function Prototypes
// Add more functions of your own, as well
string encrypt(string plaintext, string key);
string decrypt(string ciphertext, string key);
void   putTextIntoColumns(Vector<Vector<char> > &plainInColumns,
       const string &plaintext, const int &keyLen);
void   resortTextColumns(Vector<Vector<char> > &resorted,
       const Vector<Vector<char> > &plainInColumns,const Vector<int> &sortedKey);
void   flipRowColumn(Vector<Vector<char> > &flip, const Vector<Vector<char> > &resorted);
string convToString(const Vector<Vector<char> > &vect);

void sortKey(Vector<int> &sortedKey,const string &key);

int main() {
    int encryptChoice = 1;
    while (encryptChoice > 0) {
        cout << "Welcome to the Transposition Cipher Machine!" << endl;
        cout << "Please choose:" << endl;
        cout << "1) encrypt text" << endl;
        cout << "2) decrypt text" << endl;
        encryptChoice = getInteger("Please type your choice, 0 to end:","Please type an integer!");

        if (encryptChoice > 0) {
            cout << "Please enter the text to " << (encryptChoice == 1 ? "encrypt: " : "decrypt: ");
            string text = getLine();
            string key = getLine("Please type in a key: ");
            string output;
            if (encryptChoice == 1) {
                output = encrypt(text, key);
                cout << "Encrypted ";

            } else if (encryptChoice == 2) {
                output = decrypt(text, key);
                cout << "Decrypted ";
            }
            cout << "text:" << endl << endl << "\"" << output << "\"" << endl << endl;
        }
    }
    cout << "Goodbye!" << endl;
    return 0;
}

string encrypt(string plaintext, string key) {
    int keyLen = key.length();
    int vectorLen = ceil(1.0*plaintext.length()/keyLen);
    Vector<Vector<char> > plainInColumns(vectorLen);
    putTextIntoColumns(plainInColumns, plaintext, keyLen);
    Vector<int> sortedKey;
    sortKey(sortedKey,key);

    // resort according to key
    Vector<Vector<char> > resorted(vectorLen);
    resortTextColumns(resorted,plainInColumns,sortedKey);

    // flip column row, instead of row column
    Vector<Vector<char> > flip(keyLen);
    flipRowColumn(flip,resorted);

    string ciphertext = convToString(flip);
    return ciphertext;

}

string convToString(const Vector<Vector<char> > &vect){
    string s = "";
    for(Vector<char> cypher: vect){
        for(char c : cypher){
            s+=c;
        }
    }
    return s;
}

void flipRowColumn(Vector<Vector<char> > &flip, const Vector<Vector<char> > &resorted){
    int inx = 0;
    for(int j = 0; j < flip.size(); j++){ // flip.size() == keyLen from encrypt function
        for(int i = 0; i < resorted.size();i++){ //resorted.size()== vectorLen from encrypt function
            flip[j].add(resorted[i][inx]);
        }
        inx++;
    }
   // cout << flip;
}


void resortTextColumns(Vector<Vector<char> > &resorted,
             const Vector<Vector<char> > &plainInColumns,const Vector<int> &sortedKey){
    int index = 0;
    for(Vector<char> row: plainInColumns){
        for(int key:sortedKey){
            resorted[index].add(row[key]);
        }
        index++;
    }
   // cout << resorted;
}

/* змінює вектор, так що вектор містить черговість індексів,
    які ми маємо покликати в даній послідовності, щоб видозмінити
    (зашифрувати)наш початковий текст
*/
void sortKey(Vector<int> &sortedKey, const string &key){
    int keyLen = key.length();
    for(char c = 'a'; c < 'z'; c++){
        for(int i = 0; i < keyLen;i++){
            if (key[i]==c){
                sortedKey.add(i);
            }
        }
    }
   // cout << sortedKey;

}

void putTextIntoColumns(Vector<Vector<char> > &plainInColumns,
                        const string &plaintext, const int &keyLen){
    int index = 0;
    for(char c: plaintext){
        plainInColumns[index]+=c;
        if(plainInColumns[index].size()==keyLen){
            index++;
        }
    }
    for(int i = plainInColumns[plainInColumns.size()-1].size(); i < keyLen; i++){
        plainInColumns[plainInColumns.size()-1]+=PAD;
    }
   // cout << plainInColumns;
}

string decrypt(string ciphertext, string key) {
    // TODO: Implement the transposition cipher decryption
    string plaintext;
    return plaintext;
}
