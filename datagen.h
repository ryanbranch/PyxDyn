#ifndef DATAGEN_H
#define DATAGEN_H

#include "Simulation.h"

using namespace std;

//FUNCTIONS NOT BELONGING TO ANY CLASS

//Function to take in .csv data
Simulation* inCsv(string filename);
//Function to write csv output data
void outCsv(Simulation* theSim);

#endif //DATAGEN_H