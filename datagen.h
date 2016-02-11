using namespace std;

class Color {
    public:
        //Default constructor for Color
        Color();
        //Constructor for color with decimal input values
        Color(int red_, int green_, int blue_);
        //Constructor for grayscale color with decimal input values
        Color(int color);
        //Constructor for a color based on the color's name
        Color(string name);
        //Get function for red
        int getRed();
        //Set function for red
        void setRed(int color);
        //Get function for green
        int getGreen();
        //Set function for green
        void setGreen(int color);
        //Get function for blue
        int getBlue();
        //Set function for blue
        void setBlue(int color);
        //Assignment operator for Color
        Color& operator= (const Color &rhs);
        //Copy constructor for Color
        Color(const Color &other);
        
    private:
        int red;
        int green;
        int blue;
};

class Object {
    public:
        //Default constructor for Object
        Object();
        //Constructor for object with only position specified
        Object(int xPos_, int yPos_);
        //Constructor for object with only position and color specified
        Object(int xPos_, int yPos_, Color* ptrColor_);
        //Constructor for object with only color, width and height specified
        Object(Color* ptrColor_, int width_, int height_);
        //Constructor for object with only color specified
        Object(Color* ptrColor_);
        //Constructor for object with position, width, and height specified
        Object(int xPos_, int yPos_, int width_, int height_);
        //Constructor for object with position, width, height, and color
        //specified
        Object(int xPos_, int yPos_, Color* ptrColor_, int width_, int height_);
        //Destructor for Object
        ~Object();
        //Assignment operator for Object
        Object& operator= (const Object &rhs);
        //Copy constructor for Object
        Object(const Object &other);
        
        //FUNCTIONS USED IN CALCULATION
        //Function to define the constants used in calculation (Default values)
        void setConstants();
        //Function to define the constants used in calculation (Input values)
        void setConstants(double density_);
        
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
        //Function to build the data array
        void buildData();
        
        //SET AND GET FUNCTIONS FOR PHYSICAL PROPERTIES
        //Get function for mass
        double getMass();
        //Set function for mass (calculated based on density and area)
        void setMass();
        //DENSITY
        //Get function for density
        double getDensity();
        //Set function for density
        void setDensity(double density_);
        //Get function for xc
        double xcGet();
        //Set function for xc (calculated based on width and xi)
        void xcSet();
        //Get function for yc
        double ycGet();
        //Set function for yc (calculated based on height and yi)
        void ycSet();
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

class Simulation {
    public:
        //Default constructor for Simulation
        Simulation();
        //Constructor for Simulation with inputs
        Simulation(int xRes_,
                   int yRes_,
                   int numObjects_, 
                   Color** colors_,
                   Object** objects_);
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
        
        //Functions used in calculation
        //Initializes the xi and yi positions of all objects
        void iPosInit();
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
        //Returns the x component of the gravitational force acting between two objects
        double gForceX(Object* obj1, Object* obj2);
        //Returns the x component of the gravitational force acting between two objects
        double gForceY(Object* obj1, Object* obj2);
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
        
        //Constants useful for calculations
        //G - Gravitational constant in (N * m^2)/(kg)
        double c_G;
        //Size to use for the length or height of a pixel, in meters
        double pixelSize;
        //Time interval between calculations, in seconds
        double timeInterval;
};

//FUNCTIONS NOT BELONGING TO ANY CLASS

//Function to take in .csv data
Simulation* inCsv(string filename);
//Function to write csv output data
void outCsv(string filename, Simulation* theSim);