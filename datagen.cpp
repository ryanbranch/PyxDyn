#include <iostream>
#include <cstring>
#include <string>
#include <cstdlib>
#include <fstream>
#include "datagen.h"
#include "helpers.cpp"

using namespace std;

//CLASS: Color
//Default constructor for Color
Color::Color() {
    red = 0;
    green = 0;
    blue = 0;
}

//Constructor for color with decimal input values
Color::Color(int red_, int green_, int blue_) : 
             red(red_), green(green_), blue(blue_) {}

//Constructor for grayscale color with decimal input values
Color::Color(int color) : red(color), green(color), blue(color) {}

//Constructor for a color based on the color's name
Color::Color(string name) {
    if (lowercase(name) == "black") {
        red = 0;
        green = 0;
        blue = 0;
    }
    else if (lowercase(name) == "white") {
        red = 255;
        green = 255;
        blue = 255;
    }
    else if (lowercase(name) == "red") {
        red = 255;
        green = 0;
        blue = 0;
    }
    else if (lowercase(name) == "green") {
        red = 0;
        green = 255;
        blue = 0;
    }
    else if (lowercase(name) == "blue") {
        red = 0;
        green = 0;
        blue = 255;
    }
    else if ((lowercase(name) == "grey") ||
             (lowercase(name) == "gray")) {
        red = 128;
        green = 128;
        blue = 128;
    }
    else {
        cout << "Color input was " << name << endl;
        exit(1);
    }
}

//Get function for red
int Color::getRed() {
    return red;
}

//Set function for red
void Color::setRed(int color) {
    red = color;
}

//Get function for green
int Color::getGreen() {
    return green;
}

//Set function for green
void Color::setGreen(int color) {
    green = color;
}

//Get function for blue
int Color::getBlue() {
    return blue;
}

//Set function for blue
void Color::setBlue(int color) {
    blue = color;
}

//Assignment operator for Color
Color& Color::operator= (const Color &rhs) {
    //Check for self assignment
    if (this == &rhs) {
        return *this;
    }
    //Otherwise, edit the member variables, then return the Color
    red = rhs.red;
    green = rhs.green;
    blue = rhs.blue;
    return *this;
}

//Copy constructor for Color
Color::Color(const Color &other) {
    red = other.red;
    green = other.green;
    blue = other.blue;
}

//CLASS: Object        
//Default constructor for Object
Object::Object() : 
               xPos(0),
               yPos(0),
               ptrColor(new Color()),
               width(1),
               height(1),
               ptrData(new int[7]),
               dataFull(false) {}

//Constructor for object with only position specified
Object::Object(int xPos_, int yPos_) : 
               xPos(xPos_),
               yPos(yPos_),
               ptrColor(new Color()),
               width(1),
               height(1),
               ptrData(new int[7]),
               dataFull(false) {}

//Constructor for object with only position and color specified
Object::Object(int xPos_, int yPos_, Color* ptrColor_) :
               xPos(xPos_),
               yPos(yPos_),
               ptrColor(new Color(*ptrColor_)),
               width(1),
               height(1),
               ptrData(new int[7]),
               dataFull(false) {}
               
//Constructor for object with only color, width and height specified
Object::Object(Color* ptrColor_, int width_, int height_) : 
               xPos(0),
               yPos(0),
               ptrColor(new Color(*ptrColor_)),
               width(width_),
               height(height_),
               ptrData(new int[(3 * width_ * height_) + 4]),
               dataFull(false) {}

//Constructor for object with only color specified
Object::Object(Color* ptrColor_) :
               xPos(0),
               yPos(0),
               ptrColor(new Color(*ptrColor_)),
               width(1),
               height(1),
               ptrData(new int[7]),
               dataFull(false) {}

//Constructor for object with position, width, and height specified
Object::Object(int xPos_, int yPos_, int width_, int height_) :
               xPos(xPos_),
               yPos(yPos_),
               ptrColor(new Color()),
               width(width_),
               height(height_),
               ptrData(new int[(3 * width * height) + 4]),
               dataFull(false) {}

//Constructor for object with position, width, height, and color specified
Object::Object(int xPos_, int yPos_, Color* ptrColor_, int width_, int height_) :
               xPos(xPos_),
               yPos(yPos_),
               ptrColor(new Color(*ptrColor_)),
               width(width_),
               height(height_),
               ptrData(new int[(3 * width_ * height_) + 4]),
               dataFull(false) {}

//Get function for ptrColor
Color* Object::getPtrColor() {
    return ptrColor;
}

//Set function for ptrColor
void Object::setPtrColor(Color* ptrColor_) {
    ptrColor = ptrColor_;
}

//Returns the number of elements that the data array does (or will) hold
//NOTE: Should create some kind of invariant later to test this and make sure
//      that it's actually the same size of the data array.
//      Also would be a good idea to have a bool for whether data is full or not
int Object::getNumElts() {
    if (dataFull) {
        return (3 * width * height) + 4;
    }
    //If ptrData is not full, assume that it has yet to be populated
    else {
        return 0;
    }
}

//Returns the element of dataPtr at the specified index
int Object::getElt(int index) {
    int elt;
    if (dataFull) {
        elt = ptrData[index];
    }
    else {
        cout << "dataFull == false" << endl;
        elt = 0;
    }
    return elt;
}

//Function to build the data array
void Object::buildData() {
    int r = ptrColor->getRed();
    int g = ptrColor->getGreen();
    int b = ptrColor->getBlue();
    ptrData[0] = width;
    ptrData[1] = height;
    ptrData[2] = xPos;
    ptrData[3] = yPos;
    for (int h = 0; h < height; ++h) {
        for (int w = 0; w < width; ++w) {
            ptrData[(3 * ((h * width) + w)) + 4] = r;
            ptrData[(3 * ((h * width) + w)) + 5] = g;
            ptrData[(3 * ((h * width) + w)) + 6] = b;
            //cout << "iteration" << endl;
        }
    }
    dataFull = true;
}

int main(int argc, char* argv[]) {
    string filename;
    if (argc == 2) {
        filename = argv[1];
        cout << filename << endl;
    }
    else {
        filename = "input.csv";
    }
    int xRes = 400;
    int yRes = 300;
    int numObjects = 1;
    Object* objects[numObjects];
    Color* testColor = new Color(101,183,151);
    Object* testObj = new Object(203, 111, testColor, 43, 30);
    testObj->buildData();
    cout << "built data array for testObj" << endl;
    objects[0] = testObj;
    ofstream csv(filename.c_str());
    if (csv.is_open()) {
        csv << xRes << "," << yRes << "," << numObjects << endl;
        for (int i = 0; i < numObjects; ++i) {
            csv << objects[i]->getElt(0) << ",";
            csv << objects[i]->getElt(1) << ",";
            csv << objects[i]->getElt(2) << ",";
            csv << objects[i]->getElt(3) << endl;
            for (int j = 4; j < objects[i]->getNumElts(); j += 3) {
                for (int k = 0; k < 3; ++k) {
                    csv << objects[i]->getElt(j + k);
                    if (k != 2) {
                        csv << ",";
                    }
                    else {
                        csv << endl;
                    }
                }
            }
        }
        csv.close();
    }
    else {
        cout << "Could not open file." << endl;
    }
    return 0;  
}