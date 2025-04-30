#ifndef REGION_H
#define REGION_H

#include <vector>
#include "Cell.h"
#include <iostream>
using namespace std;

class Region {
    public: 
        vector<vector<Cell>>& GetRegion();    //Getters, GetRegion returns a reference so the whole array is not copied
        int GetRows();
        int GetCols();

        void SetAvailableWorkers(int availableWorkers); //Setter and Getter for availableWorkers
        int GetAvailableWorkers();

        void SetAvailableGoods(int availableGoods); //Setter and Getter for availableGoods
        int GetAvailableGoods();

        Region(); //Default constructor
        Region(vector<vector<Cell>> inputVector, int rows, int cols); //Parameterized constructor

        void PrintRegion(); //Outputs region
        void PrintPollution(); //Outputs pollution in region


        

    private:
        vector<vector<Cell>> region;  //2D Vector of Cells to represent the region during the simulation process
        int rows;
        int cols;
        int availableWorkers;
        int availableGoods;
};

#endif