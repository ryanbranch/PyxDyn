#include <iostream>
#include <cstring>
#include <string>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <cmath>
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

//Function to define the constants used in calculation (Default values)
void Simulation::setConstants() {
    //Constants useful for calculations
    //G - Gravitational constant in (N * m^2)/(kg)
    c_G = 667408000000;
    //Size to use for the width or height of a pixel, in meters
    //NOTE: This is huge, 1 million meters per pixel.  Keep that in mind.
    pixelSize = 1000000;
    //Density, in (kg)/(m^3)
    //NOTE: Based on my calculations, this will vary extremely with the scale of
    //      the objects being displayed.  So for a planet sized object it should
    //      be maybe something around 1*10^6.  Not sure about other scales.
    density = 1000;
    //Time interval between calculations, in seconds (1x10^9)
    //NOTE: 1 billion seconds = 31.68878 years.
    timeInterval = 1000000000;
}
//Function to define the constants used in calculation (Input values)
//See default setConstants() for more information about values
void Simulation::setConstants(double c_G_,
                              double pixelSize_,
                              double density_,
                              double timeInterval_) {
    if (c_G_ != 0) {
        c_G = c_G_;
    }
    if (pixelSize_ != 0) {
        pixelSize = pixelSize_;
    }
    if (density_ != 0) {
        density = density_;
    }
    if (timeInterval != 0) {
        timeInterval = timeInterval_;
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

//FUNCTIONS USED IN CALCULATION

//Initializes the xi and yi positions of all objects
void Simulation::iPosInit() {
    for (int i = 0; i < numObjects; ++i){
        Object* obj = objects[i];
        obj->xiSet(double(obj->xPosGet()) * pixelSize);
        obj->yiSet(double(obj->yPosGet()) * pixelSize);
    }
}

//Returns the x-coordinate distance between two objects measured from the center
//A positive value implies that obj2 is to the right of obj1
//A negative value implies that obj2 is to the left of obj1
double Simulation::xDistBetween(Object* obj1, Object* obj2) {
    return (obj2->xcGet() - obj1->xcGet());
}
//Returns the y-coordinate distance between two objects measured from the center
//A positive value implies that obj2 is below obj1
//A negative value implies that obj2 is above obj1
double Simulation::yDistBetween(Object* obj1, Object* obj2) {
    return (obj2->ycGet() - obj1->ycGet());
}
//Returns the distance between two objects, measured from the center
double Simulation::distBetween(Object* obj1, Object* obj2) {
    return sqrt(pow(xDistBetween(obj1, obj2), 2) +
                pow(yDistBetween(obj1, obj2), 2));
}
//Returns the fractional x component of any force acting between two objects
//A positive value implies that obj2 is to the right of obj1
//A negative value implies that obj2 is to the left of obj1
double Simulation::xComponent(Object* obj1, Object* obj2) {
    return ((xDistBetween(obj1, obj2)) / (distBetween(obj1, obj2)));
}
//Returns the fractional y component of any force acting between two objects
//A positive value implies that obj2 is below obj1
//A negative value implies that obj2 is above obj1
double Simulation::yComponent(Object* obj1, Object* obj2) {
    return ((yDistBetween(obj1, obj2)) / (distBetween(obj1, obj2)));
}
//Returns the gravitational force between two objects, from the center
double Simulation::gForce(Object* obj1, Object* obj2) {
    return((c_G * obj1->getMass() * obj2->getMass())/
           (pow(distBetween(obj1, obj2), 2))); 
}
//Returns the x component of the gravitational force acting between two objects
//A positive value implies that obj2 is to the right of obj1
//A negative value implies that obj2 is to the left of obj1
double Simulation::gForceX(Object* obj1, Object* obj2) {
    return (xComponent(obj1, obj2) * gForce(obj1, obj2));
}
//Returns the x component of the gravitational force acting between two objects
//A positive value implies that obj2 is above obj1
//A negative value implies that obj2 is below obj1
double Simulation::gForceY(Object* obj1, Object* obj2) {
    return (yComponent(obj1, obj2) * gForce(obj1, obj2));
}
//Returns the acceleration based on force and mass inputs
double Simulation::accel(double force, double mass) {
    return (force / mass);
}
//Returns the change in velocity on time interval based on acceleration
double Simulation::deltaVel(double accel) {
    return accel * timeInterval;
}
//Updates the final x velocity of an object based on change in velocity
double Simulation::updateVelX(double deltaVel, Object* obj) {
    obj->vxfSet(obj->vxiGet() + deltaVel);
    return obj->vxfGet();
}
//Updates the final y velocity of an object based on change in velocity
double Simulation::updateVelY(double deltaVel, Object* obj) {
    obj->vyfSet(obj->vyiGet() + deltaVel);
    return obj->vyfGet();
}
//Returns the change in position on time interval based on acceleration
double Simulation::deltaPos(double vel) {
    return vel * timeInterval;
}
//Updates the final x position of an object based on change in position
double Simulation::updatePosX(double deltaPos, Object* obj) {
    obj->xfSet(obj->xiGet() + deltaPos);
    return obj->xfGet();
}
//Updates the final y position of an object based on change in position
double Simulation::updatePosY(double deltaPos, Object* obj) {
    obj->yfSet(obj->yiGet() + deltaPos);
    return obj->yfGet();
}

//Calculates and applies the change in position for all objects
void Simulation::deltaPos() {
    for (int i = 0; i < numObjects; ++i) {
        Object* obj = objects[i];
        //NOTE: REMEMBER TO SET VARIABLES LIKE THIS AT THE START OF CALCULATION
        //      (Done first because they depend on the INITIAL position, etc.)
        obj->xcSet();
        obj->ycSet();
        
        //NOTE: REMEMBER TO SET VARIABLES LIKE THIS AT THE END OF CALCULATION
        //      (Done last because they update INITIAL values for next iter)
        obj->xiSet(obj->xfGet());
        obj->yiSet(obj->yfGet());
        obj->vxiSet(obj->vxfGet());
        obj->vyiSet(obj->vyfGet());
    }
        
    //NOTE: Things like forces should be calculated between the object and every
    //      other object but itself.  Do this by iterating through the objects
    //      array and calculating for all pointers where the object pointer at
    //      the current index is not equal to obj (because that signifies that
    //      the object pointer at the current index IS obj
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

//Function to get the x position on the screen, in pixels
int Object::xPosGet() {
    return xPos;
}
//Function to set the x position on the screen, in pixels
void Object::xPosSet(int pos_) {
    xPos = pos_;
}
//Function to get the y position on the screen, in pixels
int Object::yPosGet() {
    return yPos;
}
//Function to set the y position on the screen, in pixels
void Object::yPosSet(int pos_) {
    yPos = pos_;
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

//SET AND GET FUNCTIONS FOR OBJECT PHYSICAL PROPERTIES
//Get function for mass
double Object::getMass() {
    return mass;
}
//Set function for mass (calculated based on density and area)
void Object::setMass() {
    mass = (double(width * height) * density);
}

//Get function for density
double Object::getDensity() {
    return density;
}
//Set function for density
void Object::setDensity(double density_) {
    density = density_;
}

//Get function for xc
double Object::xcGet() {
    return xc;
}
//Set function for xc (calculated based on width and xi)
void Object::xcSet() {
    xc = xi + (double(width) / 2);
}

//Get function for yc
double Object::ycGet() {
    return yc;
}
//Set function for yc (calculated based on height and yi)
void Object::ycSet() {
    yc = yi + (double(height) / 2);
}

//Get function for xi
double Object::xiGet() {
    return xi;
}
//Set function for xi
void Object::xiSet(double xi_) {
    xi = xi_;
}

//Get function for yi
double Object::yiGet() {
    return yi;
}
//Set function for yi
void Object::yiSet(double yi_) {
    yi = yi_;
}

//Get function for xf
double Object::xfGet() {
    return xf;
}
//Set function for xf
void Object::xfSet(double xf_) {
    xf = xf_;
}

//Get function for yf
double Object::yfGet() {
    return yf;
}
//Set function for yf
void Object::yfSet(double yf_) {
    yf = yf_;
}

//Get function for vxi
double Object::vxiGet() {
    return vxi;
}
//Set function for vxi
void Object::vxiSet(double vxi_) {
    vxi = vxi_;
}

//Get function for vyi
double Object::vyiGet() {
    return vyi;
}
//Set function for vyi
void Object::vyiSet(double vyi_) {
    vyi = vyi_;
}

//Get function for vxf
double Object::vxfGet() {
    return vxf;
}
//Set function for vxf
void Object::vxfSet(double vxf_) {
    vxf = vxf_;
}

//Get function for vyf
double Object::vyfGet() {
    return vyf;
}
//Set function for vyf
void Object::vyfSet(double vyf_) {
    vyf = vyf_;
}

//FUNCTIONS NOT BELONGING TO ANY CLASS

//Function to take in .csv data
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

//Function to write csv output data
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
    sim->setConstants();
    outCsv(outFilename, sim);
    //Deletes the simulation
    delete sim;
    return 0;  
}