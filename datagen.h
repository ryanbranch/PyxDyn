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
        //Get function for ptrColor
        Color* getPtrColor();
        //Set function for ptrColor
        void setPtrColor(Color* ptrColor_);
        //Returns the number of elements that the data array does (or will) hold
        int getNumElts();
        //Returns the element of dataPtr at the specified index
        int getElt(int index);
        //Function to build the data array
        void buildData();
    private:
        int xPos;
        int yPos;
        Color* ptrColor;
        int width;
        int height;
        int* ptrData;
        bool dataFull;
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
    private:
        int xRes;
        int yRes;
        int numObjects;
        Color** colors;
        Object** objects;
};