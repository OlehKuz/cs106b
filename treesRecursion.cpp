/**
 * File: trees.cpp
 * ---------------
 * Draws a recursive tree as specified in the Assignment 3 handout.
 */

#include <string>    // for string
#include <iostream>  // for cout, endl
using namespace std;

#include "console.h" // required of all CS106 C++ programs
#include "gwindow.h" // for GWindow class and its setTitle, setColor, and drawPolarLine methods
#include "gtypes.h"  // for GPoint class
#include "gevents.h" // for the GMouseEvent type
#include "random.h"  // for randomChance function

static void drawTree(GWindow& window, int order, int theta, GPoint trunkBase, double len);

const static double kWindowWidth = 600;
const static double kWindowHeight = 600;
const static string kWindowTitle = "Recursive Trees";
const static double kTrunkLength  = kWindowHeight/4;
const static double kShrinkFactor = 0.70;
const static int kBranchAngleSeparation = 15;
const static int kTrunkStartAngle = 90;
const static string kLeafColor = "#2e8b57";
const static string kTrunkColor = "#8b7765";
const static int numberBranches = 7;
const static double kBranchProbability = 1.0;

static void drawTree(GWindow& window, int order) {
    GPoint trunkBase(window.getWidth()/2, window.getHeight());
    window.setColor(order < 2 ? kLeafColor : kTrunkColor);
    trunkBase = window.drawPolarLine(trunkBase, kTrunkLength, kTrunkStartAngle);
    int theta = kTrunkStartAngle;
   // drawTree(window, order - 1, theta, trunkBase, kTrunkLength*kShrinkFactor);
    // update this function to wrap around another version of drawTree, which
    // recursively draws the tree of the specified order....
}

static void drawTree(GWindow& window, int order, int theta, GPoint trunkBase, double len){
    int angle = theta - 45;
    for(int i = 0; i < numberBranches; i++){
        if(order == 0){
            window.drawPolarLine(trunkBase, len, angle + i * kBranchAngleSeparation);
        }
        else{
            GPoint base = window.drawPolarLine(trunkBase, len, angle + i * kBranchAngleSeparation);
            drawTree(window, order-1, angle + i * kBranchAngleSeparation, base,len * kShrinkFactor);
        }
    }
}

const static int kHighestOrder = 5;
int main() {
    GWindow window(kWindowWidth, kWindowHeight);
    window.setWindowTitle(kWindowTitle);
    cout << "Repeatedly click the mouse in the graphics window to draw " << endl;
    cout << "recursive trees of higher and higher order." << endl;
    for (int order = 0; order <= kHighestOrder; order++) {
        waitForClick();
        window.clear();
        drawTree(window, order);
    }
    
    cout << endl;
    cout << "All trees through order " << kHighestOrder << " have been drawn." << endl;
    cout << "Click the mouse anywhere in the graphics window to quit." << endl;
    waitForClick();
    return 0;
}
