#ifndef OBJECT_H
#define OBJECT_H

#include "Color.h"

using namespace std;

//CLASS HEADER:
class Object {
    public:
        //Default constructor for Object
        Object();
        //Constructor for object with position, width, height, color, and
        //density specified
        Object(int xPos_,
               int yPos_,
               Color* ptrColor_,
               int width_,
               int height_,
               double density_,
               int id_);
        //Destructor for Object
        ~Object();
        //Assignment operator for Object
        Object& operator= (const Object &rhs);
        //Copy constructor for Object
        Object(const Object &other);
        
        //FUNCTIONS USED IN CALCULATION
        //Function to define the constants used in calculation (Default values)
        void setDefaultConstants();

        //SET AND GET FUNCTIONS FOR DISPLAY PROPERTIES
        //Get function for ptrColor
        Color* getPtrColor();
        //Set function for ptrColor
        void setPtrColor(Color* ptrColor_);
        //Function to get the x position on the screen, in pixels
        int xPosGet();
        //Function to set the x position on the screen, in pixels
        void xPosSet(int pos_);
        //Function to get the y position on the screen, in pixels
        int yPosGet();
        //Function to set the y position on the screen, in pixels
        void yPosSet(int pos_);
        //Returns the number of elements that the data array does (or will) hold
        int getNumElts();
        //Returns the element of dataPtr at the specified index
        int getElt(int index);
        
        //Returns the last object with which the object collided;
        int getLastCollided();
        //Sets the last object with which the object collided();
        void setLastCollided(int lastCollided_);
        //Gets the object id
        int getObjectID();
        //Sets the object id
        int setObjectID(int id_);
        //Gets the x velocity following the object's last collision
        double vxColGet();
        //Sets the x velocity following the object's last collision
        double vxColSet(double vxCol_);
        //Gets the y velocity following the object's last collision
        double vyColGet();
        //Sets the y velocity following the object's last collision
        double vyColSet(double vyCol_);
        
        //Function to build the data array
        void buildData();
        
        //SET AND GET FUNCTIONS FOR PHYSICAL PROPERTIES
        
        //WIDTH/HEIGHT
        //Get function for width
        double getWidth();
        //Set function for width
        void setWidth(double width_);
        //Get function for height
        double getHeight();
        //Set function for height
        void setHeight(double height_);
        
        //MASS
        //Get function for mass
        double getMass();
        //Set function for mass (calculated based on density and area)
        void setMass(double sizeOfPixel);
        
        //DENSITY
        //Get function for density
        double getDensity();
        //Set function for density
        void setDensity(double density_);
        
        //POSITION
        //Get function for xc
        double xcGet();
        //Set function for xc (calculated based on width and xi)
        void xcSet(double sizeOfPixel);
        //Get function for yc
        double ycGet();
        //Set function for yc (calculated based on height and yi)
        void ycSet(double sizeOfPixel);
        //Get function for xi
        double xiGet();
        //Set function for xi
        void xiSet(double xi_);
        //Get function for yi
        double yiGet();
        //Set function for yi
        void yiSet(double yi_);
        //Get function for xf
        double xfGet();
        //Set function for xf
        void xfSet(double xf_);
        //Get function for yf
        double yfGet();
        //Set function for yf
        void yfSet(double yf_);
        
        //VELOCITY
        //Get function for vxi
        double vxiGet();
        //Set function for vxi
        void vxiSet(double vxi_);
        //Get function for vyi
        double vyiGet();
        //Set function for vyi
        void vyiSet(double vyi_);
        //Get function for vxf
        double vxfGet();
        //Set function for vxf
        void vxfSet(double vxf_);
        //Get function for vyf
        double vyfGet();
        //Set function for vyf
        void vyfSet(double vyf_);
        
    private:
        //COLLISION INFORMATION
        int lastCollided;
        int id;
        double vxCol;
        double vyCol;
        
        //DISPLAY PROPERTIES
        int xPos;
        int yPos;
        Color* ptrColor;
        int width;
        int height;
        int* ptrData;
        bool dataFull;
        
        //PHYSICAL PROPERTIES
        double density; //in (kg)/(m^3)
        double mass; //in kg
        //xc and yc denote the coordinates of the centers of these objects, in m
        double xc;
        double yc;
        //initial and final x and y positions of top left corners, in meters
        double xi;
        double yi;
        double xf;
        double yf;
        //initial and final x and y velocities, in m/s
        double vxi;
        double vyi;
        double vxf;
        double vyf;
};

//DEFINITIONS:

//Default constructor for Object
Object::Object() : 
               xPos(0),
               yPos(0),
               ptrColor(new Color()),
               width(1),
               height(1),
               ptrData(new int[7]),
               dataFull(false), 
               density(1000),
               id(-1) {
        lastCollided = -1;
    }

//Constructor for object with position, width, height, and color specified
Object::Object(int xPos_,
               int yPos_,
               Color* ptrColor_,
               int width_,
               int height_,
               double density_,
               int id_) :
               xPos(xPos_),
               yPos(yPos_),
               ptrColor(new Color(*ptrColor_)),
               width(width_),
               height(height_),
               ptrData(new int[(3 * width_ * height_) + 4]),
               dataFull(false),
               density(density_), 
               id(id_)  {
        lastCollided = -1;
    }

//Destructor for Object
Object::~Object(){
    delete ptrColor;
    delete[] ptrData;
}

//FUNCTIONS USED IN CALCULATION
//Function to define the constants used in calculation to their default values
void Object::setDefaultConstants() {
    //Density, in (kg)/(m^3)
    //NOTE: Based on my calculations, this will vary extremely with the scale of
    //      the objects being displayed.  So for a planet sized object it should
    //      be maybe something around 1*10^6.  Not sure about other scales.
    density = 1000;
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

//Returns the last object with which the object collided;
int Object::getLastCollided(){
    return lastCollided;
}
//Sets the last object with which the object collided();
void Object::setLastCollided(int lastCollided_) {
    lastCollided = lastCollided_;
}

//Gets the object id
int Object::getObjectID() {
    return id;
}
//Sets the object id
int Object::setObjectID(int id_) {
    id = id_;
}

//Gets the x velocity following the object's last collision
double Object::vxColGet() {
    return vxCol;
}
//Sets the x velocity following the object's last collision
double Object::vxColSet(double vxCol_) {
    vxCol = vxCol_;
}

//Gets the y velocity following the object's last collision
double Object::vyColGet() {
    return vyCol;
}
//Sets the y velocity following the object's last collision
double Object::vyColSet(double vyCol_) {
    vyCol = vyCol_;
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



//WIDTH/HEIGHT

//Get function for width
double Object::getWidth() {
    return width;
}
//Set function for width
void Object::setWidth(double width_) {
    width = width_;
}

//Get function for height
double Object::getHeight() {
    return height;
}
//Set function for height
void Object::setHeight(double height_) {
    height = height_;
}



//MASS

//Get function for mass
double Object::getMass() {
    return mass;
}
//Set function for mass (calculated based on density and area)
void Object::setMass(double sizeOfPixel) {
    mass = (double(width * height) * pow(sizeOfPixel, 2) * density);
}



//DENSITY

//Get function for density
double Object::getDensity() {
    return density;
}
//Set function for density
void Object::setDensity(double density_) {
    density = density_;
}



//POSITION

//Get function for xc
double Object::xcGet() {
    return xc;
}
//Set function for xc (calculated based on width and xi)
void Object::xcSet(double sizeOfPixel) {
    xc = xi + ((double(width) / 2) * sizeOfPixel);
}

//Get function for yc
double Object::ycGet() {
    return yc;
}
//Set function for yc (calculated based on height and yi)
void Object::ycSet(double sizeOfPixel) {
    yc = yi + ((double(height) / 2) * sizeOfPixel);
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



//VELOCITY

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

#endif //OBJECT_H