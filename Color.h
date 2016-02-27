#ifndef COLOR_H
#define COLOR_H

#include "helpers.cpp"

using namespace std;

//CLASS HEADER
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

//DEFINITIONS:

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


#endif //COLOR_H