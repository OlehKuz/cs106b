// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own.
// TODO: rewrite this comment

#include <iostream>
#include "console.h"
#include "gwindow.h"
#include "grid.h"
#include "simpio.h"
#include "strlib.h"
#include "gbufferedimage.h"
#include "gevents.h"
#include "math.h" //for sqrt and exp in the optional Gaussian kernel
#include "gmath.h" // for sinDegrees(), cosDegrees(), PI
using namespace std;

static const int    WHITE = 0xFFFFFF;
static const int    BLACK = 0x000000;
static const int    GREEN = 0x00FF00;

void     doFauxtoshop(GWindow &gw, GBufferedImage &img);
bool     openUserImage(GBufferedImage &img);
void     setWindowToImage(GWindow &gw, GBufferedImage &img);
int      imageFilter();
int      differenceNeighbors(const Grid<int> &copyImg, int row, int col);
int      difTwoPixels(const Grid<int> &copyImg, int rowOrigin,
                 int colOrigin,int rowNeighbor, int columnNeighbor);

void     applyFilter(Grid<int> &img, int filter);
void     scatter(Grid<int> &img);
void     edgeDetect(Grid<int> &img);
void     greenScreen(Grid<int> &img);
void     compareImg(Grid<int> &img);
void     rotate(Grid<int> &img);
void     blur(Grid<int> &img);

void     saveImage(GBufferedImage &img);
bool     openImageFromFilename(GBufferedImage& img, string filename);
bool 	 saveImageToFilename(const GBufferedImage &img, string filename);
void     getMouseClickLocation(int &row, int &col);
Vector<double> gaussKernelForRadius(int radius);

/* STARTER CODE FUNCTION - DO NOT EDIT
 *
 * This main simply declares a GWindow and a GBufferedImage for use
 * throughout the program. By asking you not to edit this function,
 * we are enforcing that the GWindow have a lifespan that spans the
 * entire duration of execution (trying to have more than one GWindow,
 * and/or GWindow(s) that go in and out of scope, can cause program
 * crashes).
 */
int main() {
    GWindow gw;
    gw.setTitle("Fauxtoshop");
    gw.setVisible(true);
    GBufferedImage img;
    doFauxtoshop(gw, img);
    return 0;
}

/* This is yours to edit. Depending on how you approach your problem
 * decomposition, you will want to rewrite some of these lines, move
 * them inside loops, or move them inside helper functions, etc.
 *
 * TODO: rewrite this comment.
 */
void doFauxtoshop(GWindow &gw, GBufferedImage &img) {

    cout << "Welcome to Fauxtoshop!" << endl;
    bool doPhotoshop = openUserImage(img);
    while(doPhotoshop){
        setWindowToImage(gw, img);
        Grid<int> image = img.toGrid();
        int filter = imageFilter();
        applyFilter(image, filter);
        img.fromGrid(image);
        saveImage(img);
        gw.clear();
        cout << endl;
        doPhotoshop = openUserImage(img);
    }


    /*GBufferedImage img2;
    openImageFromFilename(img2, "beyonce.jpg");
    img.countDiffPixels(img2);

    int row, col;
    getMouseClickLocation(row, col);
    gw.clear();*/
}

void saveImage(GBufferedImage &img){
    string saveLocation;
    bool success = false;
    while(!success){
        saveLocation = getLine("Enter filename to save image (or blank to skip saving): ");
        if(saveLocation=="") {
            cout << "Image won't be saved" << endl;
            break;
        }
        success = saveImageToFilename(img,saveLocation);
    }

}

int differenceNeighbors(const Grid<int> &copyImg, int row, int col){
    int max=0;
    for(int h = row - 1; h < row + 1; h++) {
        if(h >= 0 && h < copyImg.height()) {
            for(int w = col - 1; w < col + 1; w++) {
                if(w >= 0 && w < copyImg.width()) {
                    int dif = difTwoPixels(copyImg, row, col, h, w);
                    if(dif>max) max = dif;
                }
            }
        }
    }
    return max;
}

int difTwoPixels(const Grid<int> &copyImg, int rowOrigin,
                 int colOrigin,int rowNeighbor, int columnNeighbor){

    int originalPixel = copyImg[rowOrigin][colOrigin];
    int red, green, blue;
    GBufferedImage::getRedGreenBlue(originalPixel, red, green, blue);

    int neighborPixel = copyImg[rowNeighbor][columnNeighbor];
    int redN, greenN, blueN;
    GBufferedImage::getRedGreenBlue(neighborPixel, redN, greenN, blueN);

    int rdif = abs(red-redN);
    int gdif = abs(green-greenN);
    int bdif = abs(blue-blueN);

    int maxDif = (max(rdif,max(gdif,bdif)));

    return maxDif;
}

void applyFilter(Grid<int> &img, int filter){
    switch(filter) {
        case 1: scatter(img); break;
        case 2: edgeDetect(img); break;
        case 3: greenScreen(img); break;
        case 4: compareImg(img); break;
        case 5: rotate(img); break;
        case 6: blur(img); break;
    }
}

void scatter(Grid<int> &img){
    Grid<int> copyImg = img;
    int width = img.width();
    int height = img.height();
    int scatter = getInteger("Enter degree of scatter (1-100): ");
    int scatterCol = width*(double)scatter/100;
    int scatterRow = height*(double)scatter/100;
    for(int row = 0; row < height; row++){
        for(int col = 0; col < width; col++){
            while(true){
                int randomCol = randomInteger((col-scatterCol), (col+scatterCol));
                int randomRow = randomInteger((row-scatterRow), (row+scatterRow));
                if(copyImg.inBounds(randomRow, randomCol)){
                    img[row][col]=copyImg[randomRow][randomCol];
                    break;
                }
            }

        }
    }
}

void edgeDetect(Grid<int> &img){
   int threshold = getInteger("Enter threshold for edge detection: ");
   Grid<int> copyImg = img;
        for(int row = 0; row < img.height(); row++) {
            for(int col = 0; col < img.width(); col++) {
                int maxDifference = differenceNeighbors(copyImg,row, col);
                if(threshold<=maxDifference){
                    img[row][col]=BLACK;
                }
                else{
                    img[row][col]=WHITE;
                }
            }
        }
    }

void greenScreen(Grid<int> &img){

}

void compareImg(Grid<int> &img){

}

void rotate(Grid<int> &img){

}

void blur(Grid<int> &img){

}

int imageFilter(){
    int filter = 0;
    while(!(filter >=1 && filter <= 6)){
        cout << "Which image filter would you like to apply: " << endl;
        cout << "1 - Scatter" << endl;
        cout << "2 - Edge detection" << endl;
        cout << "3 - Green screen with another image " << endl;
        cout << "4 - Compare image with another image" << endl;
        cout << "5 - Rotation" << endl;
        cout << "6 - C blur" << endl;
        filter = getInteger("Your choice: ");
    }
    return filter;
}

bool openUserImage(GBufferedImage &img){
    bool cont = true;
    string file = "filename";
    bool successOpenImage = false;
    while(!successOpenImage) {
        file = getLine("Enter name of image file to open (or blank to quit): ");
        if(file=="") {
            cout << "Quiting program" << endl;
            cont = false;
            break;
        }
        successOpenImage = openImageFromFilename(img, file);
        if(successOpenImage) cout << "Opening image file..." << endl;
    }
    return cont;
}


void setWindowToImage(GWindow &gw, GBufferedImage &img){
    gw.setCanvasSize(img.getWidth(), img.getHeight());
    gw.add(&img,0,0);
}

/* STARTER CODE HELPER FUNCTION - DO NOT EDIT
 *
 * Attempts to open the image file 'filename'.
 *
 * This function returns true when the image file was successfully
 * opened and the 'img' object now contains that image, otherwise it
 * returns false.
 */
bool openImageFromFilename(GBufferedImage& img, string filename) {
    try { img.load(filename); }
    catch (...) { return false; }
    return true;
}

/* STARTER CODE HELPER FUNCTION - DO NOT EDIT
 *
 * Attempts to save the image file to 'filename'.
 *
 * This function returns true when the image was successfully saved
 * to the file specified, otherwise it returns false.
 */
bool saveImageToFilename(const GBufferedImage &img, string filename) {
    try { img.save(filename); }
    catch (...) { return false; }
    return true;
}

/* STARTER CODE HELPER FUNCTION - DO NOT EDIT
 *
 * Waits for a mouse click in the GWindow and reports click location.
 *
 * When this function returns, row and col are set to the row and
 * column where a mouse click was detected.
 */
void getMouseClickLocation(int &row, int &col) {
    GMouseEvent me;
    do {
        me = getNextEvent(MOUSE_EVENT);
    } while (me.getEventType() != MOUSE_CLICKED);
    row = me.getY();
    col = me.getX();
}

/* HELPER FUNCTION
 *
 * This is a helper function for the Gaussian blur option.
 *
 * The function takes a radius and computes a 1-dimensional Gaussian blur kernel
 * with that radius. The 1-dimensional kernel can be applied to a
 * 2-dimensional image in two separate passes: first pass goes over
 * each row and does the horizontal convolutions, second pass goes
 * over each column and does the vertical convolutions. This is more
 * efficient than creating a 2-dimensional kernel and applying it in
 * one convolution pass.
 *
 * This code is based on the C# code posted by Stack Overflow user
 * "Cecil has a name" at this link:
 * http://stackoverflow.com/questions/1696113/how-do-i-gaussian-blur-an-image-without-using-any-in-built-gaussian-functions
 *
 */
Vector<double> gaussKernelForRadius(int radius) {
    if (radius < 1) {
        Vector<double> empty;
        return empty;
    }
    Vector<double> kernel(radius * 2 + 1);
    double magic1 = 1.0 / (2.0 * radius * radius);
    double magic2 = 1.0 / (sqrt(2.0 * PI) * radius);
    int r = -radius;
    double div = 0.0;
    for (int i = 0; i < kernel.size(); i++) {
        double x = r * r;
        kernel[i] = magic2 * exp(-x * magic1);
        r++;
        div += kernel[i];
    }
    for (int i = 0; i < kernel.size(); i++) {
        kernel[i] /= div;
    }
    return kernel;
}
