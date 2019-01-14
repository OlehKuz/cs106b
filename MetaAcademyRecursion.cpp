/* 
 * TODO: put your own comments here. Also you should leave comments on
 * each of your methods.
 */

#include <math.h>
#include "recursion.h"
#include "map.h"
#include "vector.h"
#include "set.h"
#include "gwindow.h"
#include "gobjects.h"
#include "tokenscanner.h"
using namespace std;
int floodFillX(GBufferedImage& image, int x, int y, const int newColor,
               const int startPixelColor);
void personalCurriculumHelp(Map<string, Vector<string>> & prereqMap,
                        string goal, Set<string> &usedCourses);

int gcd(int a, int b) {

    if(b == 0) {
         return a;
    }
    else {
        cout << "gcd("<<a<<", "<< b<< ") = "
                << "gcd("<<b<<", "<< a%b<< ")" << endl;
        return gcd(b, a%b);

    }
}

void serpinskii(GWindow &w, int leftX, int leftY, int size, int order) {
    if(order == 1){
        // draw flipped triangle
        w.drawLine(leftX, leftY, leftX + size, leftY); // top
        w.drawLine(leftX, leftY, leftX + size/2, leftY + size*sqrt(3)/2); // left
        w.drawLine(leftX + size, leftY, leftX + size/2, leftY + size*sqrt(3)/2); // right
    }else if (order >= 1){
        // draw straight triangle
        w.drawLine(leftX + size/4, leftY + size*sqrt(3)/4,
                   leftX + 3*size/4, leftY + size*sqrt(3)/4); // bottom
        w.drawLine(leftX + size/4, leftY + size*sqrt(3)/4, leftX + size/2, leftY);// left
        w.drawLine(leftX + 3*size/4, leftY + size*sqrt(3)/4, leftX + size/2, leftY);// right
        // self similar problem: imagine that we have 3 flipped triangles, and call serpinski on those triangles
        serpinskii(w, leftX, leftY, size/2, order-1); // left triangle
        serpinskii(w, leftX + size/2, leftY, size/2, order-1); // right triangle
        serpinskii(w, leftX + size/4, leftY + size*sqrt(3)/4, size/2, order-1); // bottom triangle
    }
}

int floodFill(GBufferedImage& image, int x, int y, int newColor) {
    int colored = 0;
    int startPixelColor = image.getRGB(x,y);
    if(startPixelColor==newColor) {
         return colored;
    }
    colored = floodFillX(image, x, y, newColor, startPixelColor);
    return colored;
}

int floodFillX(GBufferedImage& image, int x, int y, const int newColor, const int startPixelColor) {
    int coloredPixels = 0;
    if(image.getRGB(x,y)==startPixelColor){
        image.setRGB(x,y,newColor);
        coloredPixels++;
        if(image.inBounds(x+1,y)){
            coloredPixels += floodFillX(image, x+1, y, newColor, startPixelColor);
        }
        if(image.inBounds(x,y-1)){
            coloredPixels +=floodFillX(image, x, y-1, newColor, startPixelColor);
        }
        if(image.inBounds(x-1,y)){
            coloredPixels +=floodFillX(image, x-1, y, newColor, startPixelColor);
        }
        if(image.inBounds(x,y+1)){
            coloredPixels +=floodFillX(image, x, y+1, newColor, startPixelColor);
        }

    }
    return coloredPixels;
}
void personalCurriculum(Map<string, Vector<string>> & prereqMap,
                        string goal) {
    Set<string> usedCourses;
    personalCurriculumHelp(prereqMap, goal, usedCourses);
    cout << goal << endl;
}


void personalCurriculumHelp(Map<string, Vector<string>> & prereqMap,
                        string goal, Set<string> &usedCourses) {
    Vector<string> prereq = prereqMap.get(goal);
    for(string course : prereq){
        if ((!prereqMap.containsKey(course) && !usedCourses.contains(course))){
              cout << course << endl;
              usedCourses.add(course);
        }
        else if(prereqMap.containsKey(course)&&!usedCourses.contains(course)){
            Vector <string> p = prereqMap.get(course);
            bool e = true;
            for(string c : p){
                if(!usedCourses.contains(c)){
                    e = false;
                    break;
                }
            }

            if(e){
                cout << course << endl;
                usedCourses.add(course);
            }
            if(!e){
                personalCurriculumHelp(prereqMap,course, usedCourses);
                personalCurriculumHelp(prereqMap,goal, usedCourses);
            }

        }
    }
}

string generate(Map<string, Vector<string> > & grammar, string symbol) {
    string symbolGenerated = "";
    Vector<string> expressionToGenerate = grammar.get(symbol);
    int random = randomInteger(0, expressionToGenerate.size()-1);
    TokenScanner scanner(expressionToGenerate[random]);
    while(scanner.hasMoreTokens()){
        string token = scanner.nextToken();
        if(!grammar.containsKey(token)){
            symbolGenerated += token;
        }
        else{
            symbolGenerated += generate(grammar, token);
        }
    }
    return symbolGenerated;
}
