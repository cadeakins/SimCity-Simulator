#ifndef DATAMANAGEMENT_H
#define DATAMANGEMENT_H

#include <iostream>
#include <fstream>
#include <string>
#include "Config.h"
#include "Region.h"
#include <cstdlib>
#include <cmath>
#include "Cell.h"
using namespace std;


Config OpenConfig();    //Opens user inputted config.txt file, validates file, and reads its contents into a Config class object

Region OpenRegion(Config inputConfig);  //Opens region.csv file, validates file, and reads its contents into a Region class object

vector<Cell*> FormatCells(Region& region);  //Formats the region into R - C - I for faster updating of Cells and ordering

#endif