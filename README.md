# PyxDyn
### Overview
PyxDyn is a project with the final goal of creating a simple 2D physics engine, written in Python and C++.

## datagen.cpp
datagen.cpp is the C++ code that, when compiled, runs as a program which generates the data for play.py to use.
It takes in csv data (default: datagen.csv) describing objects and then generates a csv data (default: input.csv) used by play.py.

At the time of writing, all necessary "cells" of the datagen.csv file are integers.

## datagen.csv
The first line must contain 3 pieces of information, in this order:
1. The width of the room to create, in pixels
2. The height of the room to create, in pixels
3. The number of objects to create

For example,
```
1024,768,2
```

All following lines are object definitions.  Currently every object is a rectangle, and each object definition in datagen.csv is a row of 7 cells, which are as follows:
1. The x position of the object to create, in pixels
2. The y position of the object to create, in pixels
3. The red component of the RGB color code describing the object's color
4. The green component of the RGB color code describing the object's color
5. The blue component of the RGB color code describing the object's color
6. The width of the object, in pixels
7. The height of the object, in pixels

For example,
```
30,40,0,0,255,8,2
170,150,0,255,0,3,3
```
would define a 8x2 blue rectangle at (30,40) and a 3x3 green square at (170,150).

When run through the compiled datagen.cpp, a datagen.csv file containing the two object definition lines described above as well as the header above that:
```
1024,768,2
30,40,0,0,255,8,2
170,150,0,255,0,3,3
```
Would generate this input.csv file:
```
1024,768,2
30,40,8,2
0,0,255
0,0,255
0,0,255
0,0,255
0,0,255
0,0,255
0,0,255
0,0,255
0,0,255
0,0,255
0,0,255
0,0,255
0,0,255
0,0,255
0,0,255
0,0,255
170,150,3,3
0,255,0
0,255,0
0,255,0
0,255,0
0,255,0
0,255,0
0,255,0
0,255,0
0,255,0
```

**datagen.cpp** depends on the header file **datagen.h** as well as a file containing helper functions, **helpers.cpp**

At the point at which this readme is being updated (9 February 2016), it may seem trivial to use the C++ code for this function.  However the next major goal is for datagen.cpp to also perform calculations based on new object parameters in order for the input.csv file created to also contain the animation data that play.py can interpret, which requires significantly more calculation and will be much faster to perform in C++ than in Python.

## play.py
play.py is a python file used for visually displaying the data that datagen.cpp generates.
It takes a .csv file as input (default name: input.csv), with the first line describing some data about the following line, and so on, such that it can be parsed by the program. For this reason, input files must follow a specific format, as described below.

At the time of writing, all necessary "cells" of the input.csv file are integers.

### input.csv
If all previous code is run correctly, the first line will contain 3 pieces of information, in this order (Note: these are the same three pieces of information in the first line of datagen.csv):
1. The width of the room to create, in pixels
2. The height of the room to create, in pixels
3. The number of objects to create
For example,
```
1024,768,2
```

The second line begins the definition of the first object. Depending on the contents of the first line, this could be the only object, or it could be one of many. In the example above, there are two objects to be created.

The first line describing any object consists of the following 4 elements:
1. The x coordinate of the object's initial position, referenced from top-left
2. The y coordinate of the object's initial position, referenced from top-left
3. The width of the object, in pixels
4. The height of the object, in pixels
From this information, specifically the first two cells, the total number of pixels comprising the object can be calculated (width * height).
Given this line:
```
25,50,3,4
```
A **3**x**4** object is to be created, so there are **3 \* 4 = 12** pixels to define.

The next *n* lines, in this case **12**, define the color of each pixel, using the standard RGB color model. Thus, each line contains 3 cells, with the first representing the **R** value, the second that of **G**, and the third that of **B**. The pixels are defined beginning at the top left corner and travelling right until the end of that "row" is met, then continuing all the way at the left side of the following "row", 1 pixel down.
These lines:

```
0,255,0
255,0,0
255,255,255
255,255,255
255,0,0
255,255,255
255,0,0
255,0,0
0,0,255
255,255,255
255,0,0
255,255,255
```
Could generate a valid image, if they followed the object definition line above.  Really, any 12 lines could, as long as they each contained 3 integer values, ranging from 0 to 255, separated by commas.  In fact...
These lines would also be acceptable:
```
127
0
255
255
0
255
0
0
63
255
0
255
```
This is because the code also supports grayscale color definitions to save space. If a line defining the color of a pixel contains only 1 value and not 3, then the line is treated as if it contained that 1 value repeated 3 times.
So,
```
127
```
is, in the eyes of the program, equivalent to
```
127,127,127
```
After the 12th line of pixel data, the next line should be another object definition line, as long as there are more objects to define.  If not, the rest of the contents don't matter **(FOR NOW)** because the remaining functionality has yet to be written.

### Credits
Anyone from who I have borrowed code will be credited here.

### To Do
 - Add to datagen.cpp such that it can animate the motion of these objects
 - Add to datagen.cpp such that it supports things such as grayscale color definitions or lack of width/height description in datagen.csv
 - Add to datagen.cpp such that it supports the creation of objects of non-rectangular shapes and of multiple colors
 - Change "Object" class to "Particle" class
 - Create "Bond" class
 - "Object" class should then be created, representing network of particles interconnected by bonds
 - Maybe be more direct and use .bmp instead of .png once I learn more about that formatting