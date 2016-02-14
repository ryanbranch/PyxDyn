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
    cout << "num objects: " << numObjects << endl;
    for (int i = 0; i < numObjects; ++i) {
        delete colors[i];
        delete objects[i];
    }
    delete[] colors;
    delete[] objects;
}

//FUNCTIONS USED IN CALCULATION
//Function to define the constants used in calculation (Default values)
void Simulation::setConstants() {
    //Constants useful for calculations
    //G - Gravitational constant in (N * m^2)/(kg)
    c_G = .0000000000667408;
    //Size to use for the width or height of a pixel, in meters
    //NOTE: This is huge, 1 million meters per pixel.  Keep that in mind.
    pixelSize = 1000000;
    //Density, in (kg)/(m^3)
    //NOTE: Based on my calculations, this will vary extremely with the scale of
    //      the objects being displayed.  So for a planet sized object it should
    //      be maybe something around 1*10^6.  Not sure about other scales.
    //density = 1000;
    //Time interval between calculations, in seconds (1x10^9)
    //NOTE: 100 million seconds = 3.168878 years.
    timeInterval = 100000000;
}
//Function to define the constants used in calculation (Input values)
//See default setConstants() for more information about values
void Simulation::setConstants(double c_G_,
                              double pixelSize_,
                              double timeInterval_) {
    if (c_G_ != 0) {
        c_G = c_G_;
    }
    if (pixelSize_ != 0) {
        pixelSize = pixelSize_;
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

//Get function for inFilename
string Simulation::getInFilename() {
    return inFilename;
}
//Set function for inFilename
void Simulation::setInFilename(string name) {
    inFilename = name;
}
//Get function for outFilename
string Simulation::getOutFilename() {
    return outFilename;
}
//Set function for outFilename
void Simulation::setOutFilename(string name) {
    outFilename = name;
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
    cout << "X DISTANCE BETWEEN: " << xDistBetween(obj1, obj2) << endl;
}
//Returns the fractional y component of any force acting between two objects
//A positive value implies that obj2 is below obj1
//A negative value implies that obj2 is above obj1
double Simulation::yComponent(Object* obj1, Object* obj2) {
    return ((yDistBetween(obj1, obj2)) / (distBetween(obj1, obj2)));
    cout << "Y DISTANCE BETWEEN: " << yDistBetween(obj1, obj2) << endl;
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
        Object* obj1 = objects[i];
        //NOTE: REMEMBER TO SET VARIABLES LIKE THIS AT THE START OF CALCULATION
        //      (Done first because they depend on the INITIAL position, etc.)
        obj1->xcSet(pixelSize);
        obj1->ycSet(pixelSize);
    }
    
    //In order to increase the efficiency of this program, we attempt to
    //eliminate any unnecessary recalculation of .  This is done by mapping
    //the total forces to a square grid with length numObjects and recognizing
    //that the after the total force from m to n is calculated, we can treat
    //the total force from n to m as the negative of the previously calculated
    //value.
    double* forceGrid = new double[2 * numObjects * numObjects];
    for (int i = 0; i < numObjects; ++i) {
        Object* obj1 = objects[i];
        double m1 = obj1->getMass();
        double* forces = new double[2 * numObjects];
        cout << "FORCES ARRAY: ";
        for (int h = 0; h < 4; ++h) {
            //NOTE: THIS ONE LINE BELOW: WHY DO I HAVE TO DO THAT HERE? SHOULDN'T IT INITIALIZE TO ZERO? BUT IT DOESN'T.  REMOVING THIS LINE BREAKS THE CODE.  THIS IS WHAT MAKES ME THINK THE CALCULATIONS MAY BE FLAWED.
            forces[h] = 0;
            cout << forces[h] << ", ";
        }
        cout << endl;
        for (int j = 0; j < numObjects; ++j) {
            Object* obj2 = objects[j];
            if (obj1 != obj2) {
                //If the relevant force has not already been calculated, do so
                //(Repeats only occur when i > j)
                if (i <= j) {
                    //NOTE: This entire section is very unorganized and most
                    //      importantly inefficient, with many unnecessary variable
                    //      creations/assignments, as well as unnecessarily calling
                    //      functions more times than needed.  When attempting to
                    //      speed things up, it will be a huge priority to
                    //      streamline this whole process.  The only reason I'm
                    //      writing it like this to begin with is so that I can
                    //      provide lots of console output for debugging.
                    double m2 = obj2->getMass();
                    cout << "Calculations between objects[" << i << "] ";
                    cout << "and objects[" << j << "]" << endl;
                    cout << "++++++++++++++++++++++++++++++++" << endl;
                    cout << "MASS OF OBJECT " << i << ": " << m1 << endl;
                    cout << "MASS OF OBJECT " << j << ": " << m2 << endl;
                    double dBetween = distBetween(obj1, obj2);
                    cout << "DISTANCE BETWEEN: " << dBetween << endl;
                    double xComp = xComponent(obj1, obj2);
                    double yComp = yComponent(obj1, obj2);
                    cout << "X COMPONENT: " << xComp << endl;
                    cout << "Y COMPONENT: " << yComp << endl;
                    cout << "X DISTANCE BETWEEN: " << xDistBetween(obj1, obj2) << endl;
                    cout << "Y DISTANCE BETWEEN: " << yDistBetween(obj1, obj2) << endl;
                    
                    
                    //F O R C E S
                    //NOTE: Eventually, when there are multiple forces, I want to
                    //      handle this as a vector of x forces and a vector of y
                    //      forces, writing values to each element as calculations
                    //      go through and then summing the vectors to a final
                    //      double value at the end for use in accelerations.
                    //GRAVITY
                    double fG = gForce(obj1, obj2);
                    double fGx = gForceX(obj1, obj2);
                    double fGy = gForceY(obj1, obj2);
                    cout << "FORCE DUE TO GRAVITY: " << fG << endl;
                    cout << "X FORCE DUE TO GRAVITY: " << fGx << endl;
                    cout << "Y FORCE DUE TO GRAVITY: " << fGy << endl;
                    //TOTAL
                    double fTx = fGx;
                    double fTy = fGy;
                    
                    forces[2 * j] = fTx;
                    forces[2* j + 1] = fTy;
                    cout << "TOTAL X FORCE: " << forces[2 * j] << endl;
                    cout << "TOTAL Y FORCE: " << forces[2 * j + 1] << endl;
                }
                else {
                    //I came up with these functions by hand.  It's much easier
                    //to visualize if drawn out as a grid of i rows by j cols,
                    //where the numerical position on the grid at any point is
                    //equal to (i * numObjects + j)
                    int n = numObjects;
                    forces[2 * j] = -1 * forceGrid[2 * ((i * n + j) -
                                                        ((n - 1) * ((i * n + j) %
                                                                    (n + 1))))];
                    forces[2 * j + 1] = -1 * forceGrid[2 * ((i * n + j) -
                                                            ((n - 1) * ((i * n + j) %
                                                                        (n + 1)))) + 1];
                }
            }
            else {
                cout << "No calculations necessary between object and itself." << endl;
                forces[2 * j] = 0;
                forces[2 * j + 1] = 0;
                cout << "TOTAL X FORCE: " << 0 << endl;
                cout << "TOTAL Y FORCE: " << 0 << endl;
            }
            cout << endl << endl;
        }
        cout << "FORCES ARRAY: ";
        for (int h = 0; h < 6; ++h) {
            cout << forces[h] << ", ";
        }
        ////Populates forceGrid and determines total force
        cout << endl;
        cout << endl << "===ADDING FORCES TOGETHER===" << endl << endl;
        
        double totalX = 0;
        double totalY = 0;
        for (int j = 0; j < (numObjects); ++j) {
            forceGrid[2 * ((numObjects * i) + j)] = forces[2 * j];
            forceGrid[2 * ((numObjects * i) + j) + 1] = forces[2 * j + 1];
            totalX += forces[2 * j];
            totalY += forces[(2 * j) + 1];
        }
        cout << "TOTAL TOTAL X FORCE: " << totalX << endl;
        cout << "TOTAL TOTAL Y FORCE: " << totalY << endl << endl;
        
        //ACCELERATIONS
        double ax = totalX / m1;
        double ay = totalY / m1;
        cout << "X ACCELERATION: " << ax << endl;
        cout << "Y ACCELERATION: " << ay << endl;
        
        //V E L O C I T I E S
        //INITIAL
        cout << "INITIAL X VELOCITY: " << obj1->vxiGet() << endl;
        cout << "INITIAL Y VELOCITY: " << obj1->vyiGet() << endl;
        //CHANGE
        double vxDelta = ax * timeInterval;
        double vyDelta = ay * timeInterval;
        cout << "CHANGE IN X VELOCITY: " << vxDelta << endl;
        cout << "CHANGE IN Y VELOCITY: " << vyDelta << endl;
        //FINAL
        obj1->vxfSet(obj1->vxiGet() + vxDelta);
        obj1->vyfSet(obj1->vyiGet() + vyDelta);
        cout << "FINAL X VELOCITY: " << obj1->vxfGet() << endl;
        cout << "FINAL Y VELOCITY: " << obj1->vyfGet() << endl;
        
        //P O S I T I O N S
        //INITIAL
        cout << "INITIAL X POSITION: " << obj1->xiGet() << endl;
        cout << "INITIAL Y POSITION: " << obj1->yiGet() << endl;
        //CHANGE
        double xDelta = obj1->vxfGet() * timeInterval;
        double yDelta = obj1->vyfGet() * timeInterval;
        cout << "CHANGE IN X POSITION: " << vxDelta << endl;
        cout << "CHANGE IN Y POSITION: " << vyDelta << endl;
        //FINAL
        obj1->xfSet(obj1->xiGet() + xDelta);
        obj1->yfSet(obj1->yiGet() + yDelta);
        cout << "FINAL X POSITION: " << obj1->xfGet() << endl;
        cout << "FINAL Y POSITION: " << obj1->yfGet() << endl;
        cout << endl;
        
        //deletes forces array
        delete[] forces;
    }
    //deletes forceGrid array
    //delete[] forceGrid;
    
    ofstream outputFile(outFilename.c_str(), ofstream::app);
    try {
        if (outputFile.is_open()) {
            for (int i = 0; i < numObjects; ++i) {
                Object* obj1 = objects[i];
                //NOTE: REMEMBER TO SET VARIABLES LIKE THIS AT THE END OF CALCULATION
                //      (Done last because they update INITIAL values for next iter)
                obj1->xiSet(obj1->xfGet());
                obj1->yiSet(obj1->yfGet());
                obj1->vxiSet(obj1->vxfGet());
                obj1->vyiSet(obj1->vyfGet());
                obj1->xPosSet(round(obj1->xiGet() / pixelSize));
                obj1->yPosSet(round(obj1->yiGet() / pixelSize));
                outputFile << obj1->xPosGet() << ",";
                outputFile << obj1->yPosGet();
                if (i == (numObjects - 1)) {
                    outputFile << endl;
                }
                else {
                    outputFile << ",";
                }
            }    
        }
        else {
            string e = "Unable to open output file: ";
            e += outFilename;
            throw e;
        }
        outputFile.close();
    }
    catch (string exception) {
        cout << exception << endl;
        exit(1);
    }

    //NOTE: Things like forces should be calculated between the object and every
    //      other object but itself.  Do this by iterating through the objects
    //      array and calculating for all pointers where the object pointer at
    //      the current index is not equal to obj (because that signifies that
    //      the object pointer at the current index IS obj
    //NOTE: I believe I have now taken this into account, but the problem is
    //      that some info is unnecessarily re-calculated, for example, the
    //      force of object 2 on object 1 is the same as the other way around.
    //      I'll need to think of a smart way to handle this.
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
    delete ptrColor;
    delete[] ptrData;
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

//FUNCTIONS USED IN CALCULATION
//Function to define the constants used in calculation (Default values)
void Object::setConstants() {
    //Density, in (kg)/(m^3)
    //NOTE: Based on my calculations, this will vary extremely with the scale of
    //      the objects being displayed.  So for a planet sized object it should
    //      be maybe something around 1*10^6.  Not sure about other scales.
    density = 1000;
}
//Function to define the constants used in calculation (Input values)
void Object::setConstants(double density_) {
    //See default setConstants() for more information about values
    density = density_;
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
void Object::setMass(double sizeOfPixel) {
    //cout << "width = " << width << endl;
    //cout << "height = " << height << endl;
    //cout << "density = " << density << endl;
    mass = (double(width * height) * pow(sizeOfPixel, 2) * density);
    //cout << "mass = " << mass << endl;
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
void Object::xcSet(double sizeOfPixel) {
    xc = xi + ((double(width) / 2) * sizeOfPixel);
    cout << "set xc to " << xc << endl;
}

//Get function for yc
double Object::ycGet() {
    return yc;
}
//Set function for yc (calculated based on height and yi)
void Object::ycSet(double sizeOfPixel) {
    yc = yi + ((double(height) / 2) * sizeOfPixel);
    cout << "set yc to " << yc << endl;
}

//Get function for xi
double Object::xiGet() {
    return xi;
}
//Set function for xi
void Object::xiSet(double xi_) {
    xi = xi_;
    //cout << "set xi to " << xi << endl;
}

//Get function for yi
double Object::yiGet() {
    return yi;
}
//Set function for yi
void Object::yiSet(double yi_) {
    yi = yi_;
    //cout << "set yi to " << yi << endl;
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
    double pixelSize;
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
            //Checks 
            if (!(getline(ss, col, ','))) {
                string e = "Input file not properly formatted: pixelSize (0, 3)";
                throw e;
            }
            else {
                istringstream stoi(col);
                if (!(stoi >> pixelSize)) {
                    string e = "pixelSize value not properly formatted: (0, 3)";
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
    
    //NOTE: This also means that I should maybe bring density back to being a
    //      member of simulation instead of object.  I'm not quite sure yet
    
    //NOTE: these should be [numObjects]
    Color* tempColors[3];
    Object* tempObjects[3];
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
            ostringstream estream;
            if (!(inputFile >> row)) {
                string e = "Row appears to be missing: ";
                estream << e << i;
                throw estream.str();
            }
            else {
                istringstream ss(row);              
                //Checks x
                if (!(getline(ss, col, ','))) {
                    string e = "Input file not properly formatted: x (";
                    estream << e << i;
                    e += ", 0)";
                    throw estream.str();
                }
                else{
                    istringstream stoi(col);
                    if (!(stoi >> x)) {
                        cout << col << endl;
                        string e = "x value not properly formatted: (";
                        estream << e << i;
                        e += ", 0)";
                        throw estream.str();
                    }
                }
                //Checks y
                if (!(getline(ss, col, ','))) {
                    string e = "Input file not properly formatted: y (";
                    estream << e << i;
                    e += ", 1)";
                    throw estream.str();
                }
                else{
                    istringstream stoi(col);
                    if (!(stoi >> y)) {
                        cout << col << endl;
                        string e = "y value not properly formatted: (";
                        estream << e << i;
                        e += ", 1)";
                        throw estream.str();
                    }
                }
                //Checks r
                if (!(getline(ss, col, ','))) {
                    string e = "Input file not properly formatted: r (";
                    estream << e << i;
                    e += ", 2)";
                    throw estream.str();
                }
                else{
                    istringstream stoi(col);
                    if (!(stoi >> r)) {
                        cout << col << endl;
                        string e = "r value not properly formatted: (";
                        estream << e << i;
                        e += ", 2)";
                        throw estream.str();
                    }
                }                
                //Checks g
                if (!(getline(ss, col, ','))) {
                    string e = "Input file not properly formatted: g (";
                    estream << e << i;
                    e += ", 3)";
                    throw estream.str();
                }
                else{
                    istringstream stoi(col);
                    if (!(stoi >> g)) {
                        cout << col << endl;
                        string e = "g value not properly formatted: (";
                        estream << e << i;
                        e += ", 3)";
                        throw estream.str();
                    }
                }
                //Checks b
                if (!(getline(ss, col, ','))) {
                    string e = "Input file not properly formatted: b (";
                    estream << e << i;
                    e += ", 4)";
                    throw estream.str();
                }
                else{
                    istringstream stoi(col);
                    if (!(stoi >> b)) {
                        cout << col << endl;
                        string e = "b value not properly formatted: (";
                        estream << e << i;
                        e += ", 4)";
                        throw estream.str();
                    }
                }
                //Checks width
                if (!(getline(ss, col, ','))) {
                    string e = "Input file not properly formatted: width (";
                    estream << e << i;
                    e += ", 5)";
                    throw estream.str();
                }
                else{
                    istringstream stoi(col);
                    if (!(stoi >> width)) {
                        cout << col << endl;
                        string e = "width value not properly formatted: (";
                        estream << e << i;
                        e += ", 5)";
                        throw estream.str();
                    }
                }
                //Checks height
                if (!(getline(ss, col, ','))) {
                    string e = "Input file not properly formatted: height (";
                    estream << e << i;
                    e += ", 6)";
                    throw estream.str();
                }
                else{
                    istringstream stoi(col);
                    if (!(stoi >> height)) {
                        cout << col << endl;
                        string e = "height value not properly formatted: (";
                        estream << e << i;
                        e += ", 6)";
                        throw estream.str();
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
        //Sets object values for constants, such as density.  If there is
        //density input, this should take in arguments
        tempObjects[i]->setConstants();
        //Sets initial values for mass, velocity, and position
        tempObjects[i]->setMass(pixelSize);
        tempObjects[i]->xiSet(x * pixelSize);
        tempObjects[i]->yiSet(y * pixelSize);
        tempObjects[i]->vxiSet(0);
        tempObjects[i]->vyiSet(0);
        cout << "Built data for object " << i << endl;
        cout << "OBJECT: " << i << endl;
        cout << "witdh: " << width << endl;
        cout << "height: " << height << endl;
        cout << "mass: " << tempObjects[i]->getMass() << endl;
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
    simulation->setInFilename(filename);
    /*
    //Attempting to fix memory leaks for this function
    for (int i = 0; i < numObjects; ++i) {
        delete tempColors[i];
        tempColors[i] = 0;
        delete tempObjects[i];
        tempObjects[i] = 0;
    }
    */
    return simulation;
}

//Function to write csv output data
void outCsv(Simulation* theSim) {
    //File output for objects
    ofstream outputFile(theSim->getOutFilename().c_str());
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
            e += theSim->getOutFilename();
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
    //NOTE: Add in a system so that numFrames can be generated from input file.
    //      also timeInterval. These should be high priority because very easy.
    int numFrames = 1;
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
    sim->setOutFilename(outFilename);
    sim->setConstants();
    
    //Sets initial position and velocity values for all objects
    
    //Populates initial output data
    outCsv(sim);
    
    //Runs numFrames iterations of the simulation
    for (int i = 0; i < numFrames; ++i) {
        sim->deltaPos();
    }
    
    //Deletes the simulation
    delete sim;
    sim = 0;
    return 0;  
}