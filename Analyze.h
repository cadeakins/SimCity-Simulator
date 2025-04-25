#ifndef ANALYZE_H
#define ANALYZE_H

#include "Region.h"
#include "Config.h"

struct Analytics { //For keeping track of data in an area
    int residentialPopulation;
    int commercialPopulation;
    int industrialPopulation;

    int residentialPollution;
    int commercialPollution;
    int industrialPollution;
};

struct Point {
    int row;
    int col;
};


struct Coords { //For running the AnalyzeArea function
    Point topLeft;
    Point topRight;
    Point botLeft;
};  



void RunAnalytics(Region& region);      //Runs the analyze phase
Analytics AnalyzeArea(Region& region, Coords coords);    //Returns information about a rectangular area
bool CheckValidArea(Region& region, Coords coords);





#endif