#include <iostream>
#include <string>
#include "helpers.cpp"
//#include "shapegen.cpp"

using namespace std;

class Color {
    public:
        //Default constructor for Color
        Color() {
            rgb[0] = 0;
            rgb[1] = 0;
            rgb[2] = 0;
            type = "RGB";
        }
        
        //Constructor for color with decimal input values
        Color(int red, int green, int blue) {
            rgb[0] = red;
            rgb[1] = green;
            rgb[2] = blue;
            type = "RGB";
        }
        
        //Constructor for grayscale color with decimal input values
        Color(int color) {
            for (int i = 0; i < 3; i++) {
                rgb[i] = color;
            }
        }
        
        //Constructor for a color based on the color's name
        Color(string name) {
            if (lowercase(name) == "black") {
                rgb[0] = 0;
                rgb[1] = 0;
                rgb[2] = 0;
            }
            else if (lowercase(name) == "white") {
                rgb[0] = 255;
                rgb[1] = 255;
                rgb[2] = 255;
            }
            else if (lowercase(name) == "red") {
                rgb[0] = 255;
                rgb[1] = 0;
                rgb[2] = 0;
            }
            else if (lowercase(name) == "green") {
                rgb[0] = 0;
                rgb[1] = 255;
                rgb[2] = 0;
            }
            else if (lowercase(name) == "blue") {
                rgb[0] = 0;
                rgb[1] = 0;
                rgb[2] = 255;
            }
            else if ((lowercase(name) == "grey") ||
                     (lowercase(name) == "gray") {
                rgb[0] = 128;
                rgb[1] = 128;
                rgb[2] = 128;
            }
        }
        
        //Get function for rgb
        int* getRGB() {
            return rgb;
        }
        
        //Set function for rgb
        void setRGB(int red, int green, int blue) {
            rgb[0] = red;
            rgb[1] = green;
            rgb[2] = blue;
        }
        
        //Get function for red
        int getRed() {
            return rgb[0];
        }
        
        //Set function for red
        void setRed(int color) {
            rgb[0] = color;
        }
        
        //Get function for green
        int getGreen() {
            return rgb[1];
        }
        
        //Set function for green
        void setGreen(int color) {
            rgb[1] = color;
        }
        
        //Get function for blue
        int getBlue() {
            return rgb[2];
        }
        
        //Set function for blue
        void setBlue(int color) {
            rgb[2] = color;
        }
        
        //Assignment operator for Color
        Color& operator= (const Color &rhs) {
            rgb[0] = rhs.rgb[0];
            rgb[1] = rhs.rgb[1];
            rgb[2] = rhs.rgb[2];
        }
        
        //Copy constructor for Color
        Color(const Color &other) {
            rgb[0] = other.rgb[0];
            rgb[1] = other.rgb[1];
            rgb[2] = other.rgb[2];
        }
        
    private:
        int rgb[];
        string type;
};

class Object {
    public:
        //Default constructor for Object
        Object() {
            pos[0] = 0;
            pos[1] = 0;
            color = Color();
            width = 1;
            height = 1;
        }
        
        //Constructor for object with only position specified
        Object(int pos_[]) {
            pos[0] = pos_[0];
            pos[1] = pos_[1];
            color = Color();
            width = 1;
            height = 1;
        }
        
        //Constructor for object with only width and height specified
        Object(int width_, int height_) : width(width_), height(height_) {
            pos[0] = 0;
            pos[1] = 0;
            color = Color();
        }
        
        //Constructor for object with only color specified
        Object(Color color_) {
            color = color_;
            pos[0] = 0;
            pos[1] = 0;
            width = 1;
            height = 1;
        }
        
        //Constructor for object with position, width, and height specified
        Object(int pos_[], int width_, int height_) :
               width(width_), height(height_) {
            pos[0] = pos_[0];
            pos[1] = pos_[1];
            color = Color();
        }
        
        //Constructor for object with position, width, height, and color
        //specified
        Object(int pos_[], int width_, int height_, Color color_) :
               width(width_), height(height_) {
            pos[0] = pos_[0];
            pos[1] = pos_[1];
            color = color_;
        }
        
        //Get function for Color
        Color getColor() {
            return color;
        }
        
        //Set function for Color
        void setColor(Color color_) {
            color = color_;
        }
        
    private:
        int pos[];
        Color color;
        int width;
        int height;
        int data[];
        
        //Function to build the data array
        void buildData() {
            data
        }
};

int main() {
    
    return 0;
}