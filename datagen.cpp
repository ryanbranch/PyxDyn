#include <iostream>
#include <cstring>
#include <string>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include "datagen.h"
#include "helpers.cpp"

using namespace std;

//CLASS: Simulation
//Default constructor for Simulation
Simulation::Simulation() {
    
}
//Constructor for Simulation with inputs
Simulation::Simulation(int xRes_,
                       int yRes_,
                       int numObjects_, 
                       Color** colors_,
                       Object** objects_) :
                       xRes(xRes_),
                       yRes(yRes_),
                       numObjects(numObjects_),
                       colors(new Color*[numObjects_]),
                       objects(new Object*[numObjects_]) {
    for (int i = 0; i < numObjects_; ++i) {
        colors[i] = colors_[i];
        objects[i] = objects_[i];
    }
}

//Destructor for Simulation
Simulation::~Simulation() {
    //cout << "Simulation dtor" << endl;
    //Run destructor for any colors or objects
    for (int i = 0; i < numObjects; ++i) {
        delete colors[i];
        delete objects[i];
    }
}

//Get function for xRes
int Simulation::getXRes() {
    return xRes;
}

//Get function for yRes
int Simulation::getYRes() {
    return yRes;
}

//Get function for numObjects
int Simulation::getNumObjects() {
    return numObjects;
}

//Returns pointer to Color at index i of colors
Color* Simulation::getColor(int i) {
    return colors[i];
}

//Returns pointer to Object at index i of objects
Object* Simulation::getObject(int i) {
    return objects[i];
}

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
    try {
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
            string e = "Color input was ";
            e += name;
            throw e;
        }
    }
    catch (string exception) {
        cout << exception << endl;
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

//Destructor for Object
Object::~Object(){
    //cout << "Object dtor" << endl;
    //delete ptrColor;
    //delete[] ptrData;
}

//Assignment operator for Object
Object& Object::operator= (const Object &rhs) {
    //Check for self assignment
    if (this == &rhs) {
        return *this;
    }
    //Otherwise, edit the member variables, then return the Color
    /*
    red = rhs.red;
    green = rhs.green;
    blue = rhs.blue;
    */
    return *this;
}

//Copy constructor for Object
Object::Object(const Object &other) {
    /*
    red = other.red;
    green = other.green;
    blue = other.blue;
    */
}

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
    ptrData[0] = xPos;
    ptrData[1] = yPos;
    ptrData[2] = width;
    ptrData[3] = height;
    for (int h = 0; h < height; ++h) {
        for (int w = 0; w < width; ++w) {
            ptrData[(3 * ((h * width) + w)) + 4] = r;
            ptrData[(3 * ((h * width) + w)) + 5] = g;
            ptrData[(3 * ((h * width) + w)) + 6] = b;
        }
    }
    dataFull = true;
}

Simulation* inCsv(string filename) {
    ifstream inputFile(filename.c_str());
    int xRes;
    int yRes;
    int numObjects;
    string row;
    string col;
    
    //File input for x and y dimensions of window as well as number of objects
    try {
        //Ensures row is present
        if (!(inputFile >> row)) {
            string e = "Row appears to be missing: 0";
            throw e;
        }
        else {
            istringstream ss(row);
            //Checks xRes
            if (!(getline(ss, col, ','))) {
                string e = "Input file not properly formatted: xRes (0, 0)";
                throw e;
            }
            else {
                istringstream stoi(col);
                if (!(stoi >> xRes)) {
                    string e = "xRes value not properly formatted: (0, 0)";
                    throw e;
                }
            }
            //Checks yRes
            if (!(getline(ss, col, ','))) {
                string e = "Input file not properly formatted: yRes (0, 1)";
                throw e;
            }
            else {
                istringstream stoi(col);
                if (!(stoi >> yRes)) {
                    string e = "yRes value not properly formatted: (0, 1)";
                    throw e;
                }
            }
            //Checks numObjects
            if (!(getline(ss, col, ','))) {
                string e = "Input file not properly formatted: numObjects (0, 2)";
                throw e;
            }
            else {
                istringstream stoi(col);
                if (!(stoi >> numObjects)) {
                    string e = "numObjects value not properly formatted: (0, 2)";
                    throw e;
                }
            }
        }
    }
    catch (string exception) {
        cout << exception << endl;
        exit(1);
    }
    cout << "xRes: " << xRes << endl;
    cout << "yRes: " << yRes << endl;
    cout << "numObjects: " << numObjects << endl;
    cout << "================================" << endl;
    
    Color* tempColors[numObjects];
    Object* tempObjects[numObjects];
    //File input for widths, heights, colors, and positions of objects
    for (int i = 0; i < numObjects; ++i) {
        int width;
        int height;
        int r;
        int g;
        int b;
        int x;
        int y;
        try {
            //Ensures row is present
            if (!(inputFile >> row)) {
                string e = "Row appears to be missing: ";
                e += i;
                throw e;
            }
            else {
                istringstream ss(row);              
                //Checks x
                if (!(getline(ss, col, ','))) {
                    string e = "Input file not properly formatted: x (";
                    e += i;
                    e += ", 0)";
                    throw e;
                }
                else{
                    istringstream stoi(col);
                    if (!(stoi >> x)) {
                        cout << col << endl;
                        string e = "x value not properly formatted: (";
                        e += i;
                        e += ", 0)";
                        throw e;
                    }
                }
                //Checks y
                if (!(getline(ss, col, ','))) {
                    string e = "Input file not properly formatted: y (";
                    e += i;
                    e += ", 1)";
                    throw e;
                }
                else{
                    istringstream stoi(col);
                    if (!(stoi >> y)) {
                        cout << col << endl;
                        string e = "y value not properly formatted: (";
                        e += i;
                        e += ", 1)";
                        throw e;
                    }
                }
                //Checks r
                if (!(getline(ss, col, ','))) {
                    string e = "Input file not properly formatted: r (";
                    e += i;
                    e += ", 2)";
                    throw e;
                }
                else{
                    istringstream stoi(col);
                    if (!(stoi >> r)) {
                        cout << col << endl;
                        string e = "r value not properly formatted: (";
                        e += i;
                        e += ", 2)";
                        throw e;
                    }
                }                
                //Checks g
                if (!(getline(ss, col, ','))) {
                    string e = "Input file not properly formatted: g (";
                    e += i;
                    e += ", 3)";
                    throw e;
                }
                else{
                    istringstream stoi(col);
                    if (!(stoi >> g)) {
                        cout << col << endl;
                        string e = "g value not properly formatted: (";
                        e += i;
                        e += ", 3)";
                        throw e;
                    }
                }
                //Checks b
                if (!(getline(ss, col, ','))) {
                    string e = "Input file not properly formatted: b (";
                    e += i;
                    e += ", 4)";
                    throw e;
                }
                else{
                    istringstream stoi(col);
                    if (!(stoi >> b)) {
                        cout << col << endl;
                        string e = "b value not properly formatted: (";
                        e += i;
                        e += ", 4)";
                        throw e;
                    }
                }
                //Checks width
                if (!(getline(ss, col, ','))) {
                    string e = "Input file not properly formatted: width (";
                    e += i;
                    e += ", 5)";
                    throw e;
                }
                else{
                    istringstream stoi(col);
                    if (!(stoi >> width)) {
                        cout << col << endl;
                        string e = "width value not properly formatted: (";
                        e += i;
                        e += ", 5)";
                        throw e;
                    }
                }
                //Checks height
                if (!(getline(ss, col, ','))) {
                    string e = "Input file not properly formatted: height (";
                    e += i;
                    e += ", 6)";
                    throw e;
                }
                else{
                    istringstream stoi(col);
                    if (!(stoi >> height)) {
                        cout << col << endl;
                        string e = "height value not properly formatted: (";
                        e += i;
                        e += ", 6)";
                        throw e;
                    }
                }  
            }
        }
        catch (string exception) {
            cout << exception << endl;
            exit(1);
        }
        tempColors[i] = new Color(r, g, b);
        tempObjects[i] = new Object(x, y, tempColors[i], width, height);
        tempObjects[i]->buildData();
        cout << "Built data for object " << i << endl;
        cout << "OBJECT: " << i << endl;
        cout << "witdh: " << width << endl;
        cout << "height: " << height << endl;
        cout << "r: " << r << endl;
        cout << "g: " << g << endl;
        cout << "b: " << b << endl;
        cout << "x: " << x << endl;
        cout << "y: " << y << endl;
        cout << "================================" << endl;
    }
    inputFile.close();
    Simulation* simulation = new Simulation(xRes,
                                            yRes,
                                            numObjects,
                                            tempColors,
                                            tempObjects);
    return simulation;
}

void outCsv(string filename, Simulation* theSim) {
    //File output for objects
    ofstream outputFile(filename.c_str());
    try {
        if (outputFile.is_open()) {
            outputFile << theSim->getXRes() << ",";
            outputFile << theSim->getYRes() << ",";
            outputFile << theSim->getNumObjects() << endl;
            for (int i = 0; i < theSim->getNumObjects(); ++i) {
                outputFile << theSim->getObject(i)->getElt(0) << ",";
                outputFile << theSim->getObject(i)->getElt(1) << ",";
                outputFile << theSim->getObject(i)->getElt(2) << ",";
                outputFile << theSim->getObject(i)->getElt(3) << endl;
                for (int j = 4;
                     j < theSim->getObject(i)->getNumElts();
                     j += 3) {
                    for (int k = 0; k < 3; ++k) {
                        outputFile << theSim->getObject(i)->getElt(j + k);
                        if (k != 2) {
                            outputFile << ",";
                        }
                        else {
                            outputFile << endl;
                        }
                    }
                }
            }
        }
        else {
            string e = "Unable to open output file: ";
            e += filename;
            throw e;
        }
        outputFile.close();
    }
    catch (string exception) {
        cout << exception << endl;
        exit(1);
    }
}

int main(int argc, char* argv[]) {
    string outFilename;
    string inFilename;
    if (argc == 3) {
        inFilename = argv[1];
        outFilename = argv[2];
    }
    else {
        inFilename = "datagen.csv";
        outFilename = "input.csv";
    }
    //Gets input data and stores it as a pointer to simulation
    Simulation* sim = inCsv(inFilename);
    outCsv(outFilename, sim);
    //Deletes the simulation
    delete sim;
    return 0;  
}