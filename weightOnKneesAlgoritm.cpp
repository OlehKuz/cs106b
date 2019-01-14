// This is the .cpp file you will edit and turn in.
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header

// Please feel free to add any other #includes you need!
#include "recursionproblems.h"
#include <cmath>
#include <iostream>
#include "hashmap.h"
#include "map.h"
#include "random.h"
using namespace std;


double weightOnKnees(int row, int col, const Vector<Vector<double> >& weights) {
    double weight = 0.0;
    int height = weights.size();
    if(row >= 0 && row < height){
        int len = weights[row].size();
        if(col < len && col >= 0) {
            weight = weights[row][col];
        }
        weight += weightOnKnees(row-1, col -1, weights)/2;
        weight += weightOnKnees(row-1, col, weights)/2;
    }

    return weight;
}

double weightOnKneesFaster(int row, int col, const Vector<Vector<double> >& weights,
                           Vector<Vector<double> >& memos) {
    double weight = 0.0;
    int height = weights.size();
    if(row >= 0 && row < height){
        int len = weights[row].size();
        if(col < len && col >= 0) {
            weight = weights[row][col];
            // flags if we need to count weight recursively
            bool left = true;
            bool rigth = true;
            if((row-1) >= 0) {
                if(col-1>=0){
                    if(memos[row-1][col-1]!= 0.0){
                        weight += memos[row-1][col-1]/2;
                        left = false;
                    }
                    if(left) {
                        // evaluates recursively, because we dont have the value stored yet
                        weight += weightOnKneesFaster(row-1, col -1, weights, memos)/2;
                    }
                }
                 if(col < weights[row-1].size()){
                     if(memos[row-1][col]!= 0.0){
                         weight += memos[row-1][col]/2;
                         rigth = false;
                     }
                     if(rigth) {
                         weight += weightOnKneesFaster(row-1, col, weights, memos)/2;
                     }
                 }
                 memos[row][col] = weight;
            }
        }
    }

    return weight;
}

double weightOnKneesFaster(int row, int col, const Vector<Vector<double> >& weights) {
    int nR = weights.size();
    Vector<Vector<double> > memos;
    for (int r = 0; r < nR; r++) {
        Vector<double> currentRow;
        for (int c = 0; c <= r; c++) {
            currentRow.add(0.0);
        }
        memos.add(currentRow);
    }
    return weightOnKneesFaster(row, col, weights, memos);
}
