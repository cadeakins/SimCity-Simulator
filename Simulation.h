#ifndef SIMULATION_H
#define SIMULATION_H

#include "Region.h"
#include "Config.h"
#include <thread>
#include <chrono>
#include "DataManagement.h"
#include <deque>
using namespace std;

class Simulation {
    public:
        Simulation();   //Default constructor

        

        int GetCurrentTimeStep();   //Getter and Setter for currentTimeStep
        void SetCurrentTimeStep(int timeStep);

        bool GetNoChange();   //Getter and Setter for noChangeCounter
        void SetNoChange(bool noChange);

        void RunSimulation(Region& region, Config& config);   //Continuously runs until time limit reached or nothing has changed in two time steps
        void UpdateCity(Region& region, vector<Cell*> orderedCells);  //Iterates through each cell in Region and checks growth conditions, updates accordingly, returns true if change has NOT occured
        void SpreadPollution(Region& region, Cell* current); //Spreads pollution to neighbor cells
        vector<Cell*> findAdjacentCells(Region& region, Cell* centerCell); //Returns all adjacent Cells in a vector of cell pointers  

    private: 
        int currentTimeStep;
        bool noChange;
};


struct UpdateQueue {    //Simple struct to keep track of what needs updating
    Cell* current;
    int newPopulation;
    int newWorkers;
    int newGoods;
};
#endif