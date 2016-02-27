#include <iostream>
#include <cstring>
#include <string>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <cmath>
#include "datagen.h"
#include "helpers.cpp"
#include "Simulation.h"
#include "Object.h"
#include "Color.h"

using namespace std;

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
    double timeInterval;
    int numIterations;
    string debugString;
    bool debug;
    
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
            //Checks pixelSize
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
            //Checks timeInterval
            if (!(getline(ss, col, ','))) {
                string e = "Input file not properly formatted: timeInterval (0, 4)";
                throw e;
            }
            else {
                istringstream stoi(col);
                if (!(stoi >> timeInterval)) {
                    string e = "timeInterval value not properly formatted: (0, 4)";
                    throw e;
                }
            }
            //Checks numIterations
            if (!(getline(ss, col, ','))) {
                string e = "Input file not properly formatted: numIterations (0, 5)";
                throw e;
            }
            else {
                istringstream stoi(col);
                if (!(stoi >> numIterations)) {
                    string e = "numIterations value not properly formatted: (0, 5)";
                    throw e;
                }
            }
            //Checks debugString
            if (!(getline(ss, col, ','))) {
                string e = "Input file not properly formatted: debugString (0, 6)";
                throw e;
            }
            else {
                istringstream stoi(col);
                if (!(stoi >> debugString)) {
                    string e = "debugString value not properly formatted: (0, 6)";
                    throw e;
                }
                else {
                    if (lowercase(debugString) == "true" ||
                        lowercase(debugString) == "debug" ||
                        lowercase(debugString) == "y") {
                        debug = true;
                    }
                    else if (lowercase(debugString) == "false" ||
                             lowercase(debugString) == "nodebug" ||
                             lowercase(debugString) == "n") {
                        debug = false;
                    }
                    else {
                        string e = "debugString value not recodnized: ";
                        e += debugString;
                        throw e;
                    }
                }
            }
        }
    }
    catch (string exception) {
        cout << exception << endl;
        exit(1);
    }
    if (debug) {
        cout << "xRes: " << xRes << endl;
        cout << "yRes: " << yRes << endl;
        cout << "numObjects: " << numObjects << endl;
        cout << "pixelSize: " << pixelSize << endl;
        cout << "timeInterval: " << timeInterval << endl;
        cout << "debugString: " << debugString << endl;
        cout << "================================" << endl;
    }
    
    Color** tempColors = new Color*[numObjects];
    Object** tempObjects = new Object*[numObjects];
    //File input for widths, heights, colors, and positions of objects
    for (int i = 0; i < numObjects; ++i) {
        int width;
        int height;
        int r;
        int g;
        int b;
        int x;
        int y;
        double density;
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
                //Checks density
                if (!(getline(ss, col, ','))) {
                    string e = "Input file not properly formatted: density (";
                    estream << e << i;
                    e += ", 7)";
                    throw estream.str();
                }
                else{
                    istringstream stoi(col);
                    if (!(stoi >> density)) {
                        cout << col << endl;
                        string e = "density value not properly formatted: (";
                        estream << e << i;
                        e += ", 7)";
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
        tempObjects[i] = new Object(x, y, tempColors[i], width, height, density);
        tempObjects[i]->buildData();
        //Sets object values for constants, such as density.  If there is
        //density input, this should take in arguments
        //tempObjects[i]->setDefaultConstants();
        //Sets initial values for mass, velocity, and position
        tempObjects[i]->setMass(pixelSize);
        tempObjects[i]->xiSet(x * pixelSize);
        tempObjects[i]->yiSet(y * pixelSize);
        tempObjects[i]->vxiSet(0);
        tempObjects[i]->vyiSet(0);
        
        if (debug) {
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
    }
    inputFile.close();
    Simulation* simulation = new Simulation(xRes,
                                            yRes,
                                            numObjects,
                                            tempColors,
                                            tempObjects,
                                            pixelSize,
                                            timeInterval,
                                            numIterations,
                                            debug);
    simulation->setInFilename(filename);
    
    //Attempting to fix memory leaks for this function
    delete[] tempColors;
    delete[] tempObjects;
    
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
    bool debug = false;
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
    for (int i = 0; i < sim->getNumIterations(); ++i) {
        sim->deltaPos();
    }
    
    //Deletes the simulation
    delete sim;
    sim = 0;
    return 0;  
}