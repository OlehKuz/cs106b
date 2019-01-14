// This is the CPP file you will edit and turn in. (TODO: Remove this comment!)

#include <iostream>
#include <string>
#include <fstream>
#include "console.h"
#include "hashset.h"
#include "simpio.h"
#include "lexicon.h"
#include "stack.h"
#include "queue.h"
#include "vector.h"


using namespace std;
void askForWords(string& word1, string& word2, HashSet<string>& dict);
void readInWords(HashSet<string>& dict);
Stack<string> algoritm(string& word1, string& word2, HashSet<string>& dict);
void fillValidNeighbors(HashSet<string>& valid, const string& top,
                        const HashSet<string>& usedWords, const HashSet<string>& dict);

int main() {
    cout<<"Welcome to Word Ladder!"<<endl;
    cout << "Give me two English words, and I will change the first "<<endl
            <<"into the second by changing one letter at a time." << endl<< endl;
    HashSet<string>  englDictionary;// better lexicon
    readInWords(englDictionary);
    string word1;
    string word2;
    while(true){
        askForWords(word1, word2, englDictionary);
        if(word2=="" || word1 == ""){
            break;
        }
        else{
            Stack<string> stackWord2 = algoritm(word1, word2, englDictionary);
            if(stackWord2.isEmpty()){
                cout << "No word ladder found from "<< word1 <<" back to "<<word2<< endl;
            }
            else if(!stackWord2.isEmpty()){
                cout << "A ladder from "<< word2<<" back to "<< word1<<": "<< endl;
                while(!stackWord2.isEmpty()){
                    cout << stackWord2.pop() << "  ";
                }
                cout << endl;

            }

        }
    }

    cout << "Have a nice day." << endl;
    return 0;
}

Stack<string> algoritm(string& word1, string& word2, HashSet<string>& dict){
    Queue<Stack<string>> search;
    HashSet<string> usedWords;
    HashSet<string> validNeighbors;

    Stack<string> w1;
    w1.push(word1);
    search.enqueue(w1);
    w1.clear();

    usedWords.add(word1);

    while(!search.isEmpty()){
        Stack<string> s = search.dequeue();
        string top = s.peek();
        fillValidNeighbors(validNeighbors, top, usedWords,dict);
        for(string wd : validNeighbors){
            Stack<string> stack = s;
            stack.push(wd);
            if(wd == word2){
                return stack;
            }
            search.enqueue(stack);
            usedWords.add(wd);
        }
        validNeighbors.clear();

    }
    return w1;
}

void fillValidNeighbors(HashSet<string>& valid, const string& top,
                        const HashSet<string>& usedWords, const HashSet<string>& dict){
    string topCopy = top;
    int len = top.length();
    for(int i = 0; i < len; i++){
        for(char c = 'a'; c <='z'; c++){
            topCopy[i] = c;
            if(dict.contains(topCopy)&&!usedWords.contains(topCopy)){
                valid.add(topCopy);
            }
        }
        topCopy = top;
    }
    //cout<<valid<<endl;
}

void askForWords(string& word1, string& word2, HashSet<string>& dict){
    while(true){
        word1 = toLowerCase(trim(getLine("Word 1 (or Enter to quit): ")));
        if(word1==""){
            break;
        }
        word2 = toLowerCase(trim(getLine("Word 2 (or Enter to quit): ")));
        if(word2==""){
            break;
        }

        if(word1.length()!=word2.length()) {
            cout << "Words should be the same length! "<< endl;
        }

        if(word1==word2) cout << "The two words must be different."<< endl;

        if(!(dict.contains(word1)&&dict.contains(word2))){
             cout << "The two words must be found in the dictionary." << endl;
        }

        else if(dict.contains(word1)&&dict.contains(word2)&&word1.length()==word2.length()){
            break;
        }
    }
}

// opens file and reads in words into supplied hashset parameter
void readInWords(HashSet<string>& dict){
    ifstream input;
    while(true){
            string filename = getLine("Dictionary file name: ");
            input.open(filename);
            if(input.is_open()) break;
    }

    string word;

    while(input>>word){
        dict.add(word);
    }
}
