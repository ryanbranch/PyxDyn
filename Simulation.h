#ifndef SIMULATION_H
#define SIMULATION_H

#include "Object.h"
#include "Color.h"

using namespace std;

//CLASS HEADER
class Simulation {
    public:
        //Default constructor for Simulation
        Simulation();
        //Constructor for Simulation with inputs
        Simulation(int xRes_,
                   int yRes_,
                   int numObjects_, 
                   Color** colors_,
                   Object** objects_,
                   double pixelSize_,
                   double timeInterval,
                   int numIterations,
                   bool debugMode_);
        //Destructor for Simulation
        ~Simulation();
        //FUNCTIONS USED IN CALCULATION
        //Function to define the constants used in calculation (Default values)
        void setConstants();
        //Function to define the constants used in calculation (Input values)
        void setConstants(double c_G_,
             double pixelSize_,
             double timeInterval_);
        //Get function for xRes
        int getXRes();
        //Get function for yRes
        int getYRes();
        //Get function for numObjects
        int getNumObjects();
        //Get function for colors
        Color* getColor(int i);
        //Get function for objects
        Object* getObject(int i);
        //Get function for inFilename
        string getInFilename();
        //Set function for inFilename
        void setInFilename(string name);
        //Get function for outFilename
        string getOutFilename();
        //Set function for outFilename
        void setOutFilename(string name);
        //Get function for debugMode
        bool getDebugMode();
        //Set function for debugMode
        void setDebugMode(bool mode);
        //Get function for pixelSize
        double getPixelSize();
        //Set function for pixelSize
        void setPixelSize(int size);
        //Get function for timeInterval
        double getTimeInterval();
        //Set function for timeInterval
        void setTimeInterval(int time);
        //Get function for numIterations
        int getNumIterations();
        //Set function for numIterations
        void setNumIterations(int num);
        
        //Functions used in calculation
        //Initializes the xi and yi positions of all objects
        void iPosInit();
        
        //Returns the furthest distance at which 2 objects could possibly collide
        double collisionDistance(Object* obj1, Object* obj2);
        //Checks whether a collision is ocurring between two objects
        bool checkCollision(Object* obj1, Object* obj2);
        
        //Returns the x-coordinate distance between two objects measured from the center
        double xDistBetween(Object* obj1, Object* obj2);
        //Returns the y-coordinate distance between two objects measured from the center
        double yDistBetween(Object* obj1, Object* obj2);
        //Returns the distance between two objects, measured from the center
        double distBetween(Object* obj1, Object* obj2);
        //Returns the fractional x component of any force acting between two objects
        double xComponent(Object* obj1, Object* obj2);
        //Returns the fractional y component of any force acting between two objects
        double yComponent(Object* obj1, Object* obj2);
        
        //Returns the gravitational force between two objects, from the center
        double gForce(Object* obj1, Object* obj2);
        //Returns the acceleration based on force and mass inputs
        double accel(double force, double mass);
        //Returns the change in velocity on time interval based on acceleration
        double deltaVel(double accel);
        //Updates the final x velocity of an object based on change in velocity
        double updateVelX(double deltaVel, Object* obj);
        //Updates the final y velocity of an object based on change in velocity
        double updateVelY(double deltaVel, Object* obj);
        //Returns the change in position on time interval based on acceleration
        double deltaPos(double vel);
        //Updates the final x position of an object based on change in position
        double updatePosX(double deltaPos, Object* obj);
        //Updates the final y position of an object based on change in position
        double updatePosY(double deltaPos, Object* obj);
        //Calculates and applies the change in position for all objects
        void deltaPos();
    private:
        int xRes;
        int yRes;
        int numObjects;
        Color** colors;
        Object** objects;
        string outFilename;
        string inFilename;
        int numIterations;
        bool debugMode;
        int collidedNum;
        int collidedRef;
        
        //Constants useful for calculations
        //G - Gravitational constant in (N * m^2)/(kg)
        double c_G;
        //Size to use for the length or height of a pixel, in meters
        double pixelSize;
        //Time interval between calculations, in seconds
        double timeInterval;
};

//DEFINITIONS:

//Default constructor for Simulation
Simulation::Simulation() {
    
}
//Constructor for Simulation with inputs
Simulation::Simulation(int xRes_,
                       int yRes_,
                       int numObjects_, 
                       Color** colors_,
                       Object** objects_,
                       double pixelSize_,
                       double timeInterval_,
                       int numIterations_,
                       bool debugMode_) :
                       xRes(xRes_),
                       yRes(yRes_),
                       numObjects(numObjects_),
                       colors(new Color*[numObjects_]),
                       objects(new Object*[numObjects_]),
                       pixelSize(pixelSize_),
                       timeInterval(timeInterval_),
                       numIterations(numIterations_),
                       debugMode(debugMode_),
                       collidedNum(0),
                       collidedRef(0) {
    for (int i = 0; i < numObjects_; ++i) {
        colors[i] = colors_[i];
        objects[i] = objects_[i];
    }
}

//Destructor for Simulation
Simulation::~Simulation() {
    //Run destructor for any colors or objects
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

//Get function for debugMode
bool Simulation::getDebugMode() {
    return debugMode;
}
//Set function for debugMode
void Simulation::setDebugMode(bool mode) {
    debugMode = mode;
}

//Size to use for the width or height of a pixel, in meters
//Get function for pixelSize
double Simulation::getPixelSize() {
    return pixelSize;
}
//Set function for pixelSize
void Simulation::setPixelSize(int size) {
    pixelSize = size;
}

//Time interval between calculations, in seconds
//Get function for timeInterval
double Simulation::getTimeInterval() {
    return timeInterval;
}
//Set function for timeInterval
void Simulation::setTimeInterval(int time) {
    timeInterval = time;
}

//Number of iterations to perform calculations for.  Essentially, how many
//animation frames to generate
//Get function for numIterations
int Simulation::getNumIterations() {
    return numIterations;
}
//Set function for numIterations
void Simulation::setNumIterations(int num) {
    numIterations = num;
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

//Returns the furthest distance at which 2 objects could possibly collide
double Simulation::collisionDistance(Object* obj1, Object* obj2) {
    return sqrt(pow((obj1->getHeight() + obj2->getHeight()), 2) +
                pow((obj1->getWidth() + obj2->getWidth()), 2));
}

bool Simulation::checkCollision(Object* obj1, Object* obj2) {
    bool collides = false;
    
    //If statements are structured in this way so that collision directionality
    //can be known and examined for potential future debugging purposes.
    
    double distX = xDistBetween(obj1, obj2);
    double distY = yDistBetween(obj1, obj2);
    double distW = (((obj1->getWidth() + obj2->getWidth()) / 2) * pixelSize);
    double distH = (((obj1->getHeight() + obj2->getHeight()) / 2) * pixelSize);
    
    
    //cout << "distX: " << distX << endl;
    //cout << "distW: " << distW << endl;
    //cout << "distY: " << distY << endl;
    //cout << "distH: " << distH << endl;
    //cout << ((distX <= distW) && (distY <= distH)) << endl;
    
    //Object 1 right is to the right of Object 2 left AND dist is low enough
    //(Also handles if they are exactly aligned)
    if (((obj1->xiGet() + (obj1->getWidth() * pixelSize)) >= (obj2->xiGet())) &&
        ((distX < distW) && (distY <= distH))){
        //cout << "obj1 RIGHT to the right of obj2 LEFT" << endl;
        collides = true;
    }
    //Object 1 left is to the left of Object 2 right AND dist is low enough
    else if (((obj1->xiGet()) < (obj2->xiGet() + (obj2->getWidth() * pixelSize))) && 
             ((distX < distW) && (distY <= distH))){
        //cout << "obj1 LEFT to the left of obj2 RIGHT" << endl;
        collides = true;
    }
    //Object 1 bottom is below Object 2 top AND dist is low enough
    //(Also handles if they are exactly aligned)
    else if (((obj1->yiGet() + (obj1->getHeight() * pixelSize)) >= (obj2->yiGet())) &&
             ((distX < distW) && (distY <= distH))){
        //cout << "obj1 BOTTOM below obj2 TOP" << endl;
        collides = true;
    }
    //Object 1 top is above Object 2 bottom AND dist is low enough
    else if (((obj1->yiGet()) < (obj2->yiGet() + (obj2->getHeight() * pixelSize))) && 
             ((distX < distW) && (distY <= distH))){
        //cout << "obj1 TOP above obj2 BOTTOM" << endl;
        collides = true;
    }
    
    if (collides) {
        obj1->setLastCollided(obj2->getObjectID());
        obj2->setLastCollided(obj1->getObjectID());
    }
    
    return collides;
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
    //eliminate any unnecessary force recalculations.  This is done by mapping
    //the total forces to an array with length numObjects^2, and recognizing
    //that the after the total force from m to n is calculated, we can treat
    //the total force from n to m as the negative of the previously calculated
    //value.
    //Calculates and applies the forces between all objects
    double* forceGrid = new double[2 * numObjects * numObjects];
    for (int i = 0; i < numObjects; ++i) {
        Object* obj1 = objects[i];
        double m1 = obj1->getMass();
        double* forces = new double[2 * numObjects];
        for (int j = 0; j < numObjects; ++j) {
            Object* obj2 = objects[j];
            if (obj1 != obj2) {
                //If the relevant force has not already been calculated, do so
                //(Repeats only occur when i > j)
                if (i <= j) {
                    //MASSES, DISTANCES, AND LOCATIONS
                    double m2 = obj2->getMass();
                    double dBetween = distBetween(obj1, obj2);
                    double xComp = xComponent(obj1, obj2);
                    double yComp = yComponent(obj1, obj2);
                    
                    //F O R C E S
                    //NOTE: Eventually, when there are multiple forces, I want to
                    //      handle this as a vector of x forces and a vector of y
                    //      forces, writing values to each element as calculations
                    //      go through and then summing the vectors to a final
                    //      double value at the end for use in accelerations.
                    //GRAVITY
                    double fG = gForce(obj1, obj2);
                    double fGx = xComp * fG;
                    double fGy = yComp * fG;
                    //TOTAL (CALCULATION)
                    double fTx = fGx; // + other x forces, when added
                    double fTy = fGy; // + other y forces, when added
                    //TOTAL (SAVING)
                    forces[2 * j] = fTx;
                    forces[2* j + 1] = fTy;

                    if (debugMode) {
                        cout << "Calculations between objects[" << i << "] ";
                        cout << "and objects[" << j << "]" << endl;
                        cout << "++++++++++++++++++++++++++++++++" << endl;
                        cout << "MASS OF OBJECT " << i << ": " << m1 << endl;
                        cout << "MASS OF OBJECT " << j << ": " << m2 << endl;
                        cout << "DISTANCE BETWEEN: " << dBetween << endl;
                        cout << "X COMPONENT: " << xComp << endl;
                        cout << "Y COMPONENT: " << yComp << endl;
                        cout << "FORCE DUE TO GRAVITY: " << fG << endl;
                        cout << "X FORCE DUE TO GRAVITY: " << fGx << endl;
                        cout << "Y FORCE DUE TO GRAVITY: " << fGy << endl;
                        cout << "TOTAL X FORCE: " << forces[2 * j] << endl;
                        cout << "TOTAL Y FORCE: " << forces[2 * j + 1] << endl;
                    }
                }
                else {
                    //I came up with these functions by hand.  It's much easier
                    //to visualize if drawn out as a grid of i rows by j cols,
                    //where the numerical position on the grid at any point is
                    //equal to (i * numObjects + j)
                    int n = numObjects;
                    forces[2 * j] = -1 * forceGrid[2 * (j * n + i)];
                    forces[2 * j + 1] = -1 * forceGrid[2 * (j * n + i) + 1];
                    
                    if (debugMode) {
                        cout << "Calculations between objects[" << i << "] ";
                        cout << "and objects[" << j << "]" << endl;
                        cout << "++++++++++++++++++++++++++++++++" << endl;
                        cout << "Skipping calculations because objects[" << j;
                        cout << "] to objects[" << i << "] was done." << endl;
                        cout << "TOTAL X FORCE: " << forces[2 * j] << endl;
                        cout << "TOTAL Y FORCE: " << forces[2 * j + 1] << endl;
                    }
                }
            }
            else {
                forces[2 * j] = 0;
                forces[2 * j + 1] = 0;
                
                if (debugMode) {
                    cout << "Calculations between objects[" << i << "] ";
                    cout << "and objects[" << j << "]" << endl;
                    cout << "No calculations needed from self to self." << endl;
                    cout << "TOTAL X FORCE: " << 0 << endl;
                    cout << "TOTAL Y FORCE: " << 0 << endl;
                }
            }
        }
        if (debugMode) {
            cout << "FORCES ARRAY: ";
            for (int j = 0; j < (2 * numObjects); ++j) {
                cout << forces[j] << ", ";
            }
        }
        //Populates forceGrid and determines total force from an object to
        //all other objects
        double totalX = 0;
        double totalY = 0;
        for (int j = 0; j < (numObjects); ++j) {
            forceGrid[2 * ((numObjects * i) + j)] = forces[2 * j];
            forceGrid[2 * ((numObjects * i) + j) + 1] = forces[2 * j + 1];
            totalX += forces[2 * j];
            totalY += forces[(2 * j) + 1];
        }
        if (debugMode) {
            cout << "TOTAL, TOTAL X FORCE: " << totalX << endl;
            cout << "TOTAL, TOTAL Y FORCE: " << totalY << endl;
        }
        
        //ACCELERATIONS
        double ax = totalX / m1;
        double ay = totalY / m1;
        
        //V E L O C I T I E S
        //CHANGE
        double vxDelta = ax * timeInterval;
        double vyDelta = ay * timeInterval;
        //FINAL
        obj1->vxfSet(obj1->vxiGet() + vxDelta);
        obj1->vyfSet(obj1->vyiGet() + vyDelta);
        
        //P O S I T I O N S
        //CHANGE
        double xDelta = obj1->vxfGet() * timeInterval;
        double yDelta = obj1->vyfGet() * timeInterval;
        //FINAL
        obj1->xfSet(obj1->xiGet() + xDelta);
        obj1->yfSet(obj1->yiGet() + yDelta);
        
        if (debugMode) {
            cout << "X ACCELERATION: " << ax << endl;
            cout << "Y ACCELERATION: " << ay << endl;
            cout << "INITIAL X VELOCITY: " << obj1->vxiGet() << endl;
            cout << "INITIAL Y VELOCITY: " << obj1->vyiGet() << endl;
            cout << "CHANGE IN X VELOCITY: " << vxDelta << endl;
            cout << "CHANGE IN Y VELOCITY: " << vyDelta << endl;
            cout << "FINAL X VELOCITY: " << obj1->vxfGet() << endl;
            cout << "FINAL Y VELOCITY: " << obj1->vyfGet() << endl;
            cout << "INITIAL X POSITION: " << obj1->xiGet() << endl;
            cout << "INITIAL Y POSITION: " << obj1->yiGet() << endl;
            cout << "CHANGE IN X POSITION: " << vxDelta << endl;
            cout << "CHANGE IN Y POSITION: " << vyDelta << endl;
            cout << "FINAL X POSITION: " << obj1->xfGet() << endl;
            cout << "FINAL Y POSITION: " << obj1->yfGet() << endl;
            cout << endl;
        }
        
        //deletes forces array
        delete[] forces;
    }
    //deletes forceGrid array
    //delete[] forceGrid;    
    
    //Calculates and applies any changes in velocity due to collision
    for (int i = 0; i < numObjects; ++i) {
        Object* obj1 = objects[i];
        double m1 = obj1->getMass();
        for (int j = 0; j < numObjects; ++j) {
            Object* obj2 = objects[j];
            //Since we only need to calculate collisions between any given pair
            //of objects once and not twice, and can ignore equality since self
            //collision isn't a thing, we examine all cases where i < j.
            //We only have to test if collidedNum is equal to collidedRef.
            //We also only need to test if the two objects' last collisions were with eachother
            if ((i < j) &&
               (((obj1->getLastCollided() != 
                 obj2->getObjectID()) ||
                 (obj1->getObjectID() != 
                 obj2->getLastCollided())) ||
                ((obj1->getLastCollided() == -1) || 
                  (obj2->getLastCollided() == -1)))) {
                                 
                                 
                //cout << obj1->getLastCollided() << "    " << obj2->getLastCollided() << endl;
                
                
                //MASSES, DISTANCES, AND LOCATIONS
                double m2 = obj2->getMass();
                double dBetween = distBetween(obj1, obj2);
                //if ((dBetween < collisionDistance(obj1, obj2)) && checkCollision(obj1, obj2)) {
                if (checkCollision(obj1, obj2)) {
                    //Updates initial velocity variables
                    obj1->vxiSet(obj1->vxfGet());
                    obj1->vyiSet(obj1->vyfGet());                    
                    
                    //Computes new velocities, elastically
                    obj1->vxfSet((((m1 - m2) / (m1 + m2)) * obj1->vxiGet()) +
                                 (((2 * m2) / (m1 + m2)) * obj2->vxiGet()));
                    obj2->vxfSet((((2 * m1) / (m1 + m2)) * obj1->vxiGet()) -
                                 (((m1 - m2) / (m1 + m2)) * obj2->vxiGet()));
                    obj1->vyfSet((((m1 - m2) / (m1 + m2)) * obj1->vyiGet()) +
                                 (((2 * m2) / (m1 + m2)) * obj2->vyiGet()));
                    obj2->vyfSet((((2 * m1) / (m1 + m2)) * obj1->vyiGet()) -
                                 (((m1 - m2) / (m1 + m2)) * obj2->vyiGet()));
                                 
                    //cout << "COLLISION between objects[" << i << "] ";
                    //cout << "and objects[" << j << "]" << endl;
                                 
                if (debugMode) {
                        cout << "COLLISION between objects[" << i << "] ";
                        cout << "and objects[" << j << "]" << endl;
                        cout << "++++++++++++++++++++++++++++++++" << endl;
                        cout << "For objects[" << i << "]:" << endl;
                        cout << "INITIAL X VELOCITY: " << obj1->vxiGet() << endl;
                        cout << "INITIAL Y VELOCITY: " << obj1->vyiGet() << endl;
                        cout << "FINAL X VELOCITY: " << obj1->vxfGet() << endl;
                        cout << "FINAL Y VELOCITY: " << obj1->vyfGet() << endl;
                        cout << endl;
                        cout << "For objects[" << j << "]:" << endl;
                        cout << "INITIAL X VELOCITY: " << obj2->vxiGet() << endl;
                        cout << "INITIAL Y VELOCITY: " << obj2->vyiGet() << endl;
                        cout << "FINAL X VELOCITY: " << obj2->vxfGet() << endl;
                        cout << "FINAL Y VELOCITY: " << obj2->vyfGet() << endl;
                        cout << endl;
                    }
                }
            }
        }
    }
    
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
}


#endif //SIMULATION_H