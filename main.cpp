#include <iostream>
#include "DataManagement.h"
#include "Simulation.h"
#include "Analyze.h"

using namespace std;

int main () {
    string file = "README.txt";
    Config inputConfig = OpenConfig();
    Region region = OpenRegion(inputConfig);

    vector<vector<Cell>>regVec = region.GetRegion();

    vector<Cell*> ordered = FormatCells(region);

    Simulation newGame;
    newGame.RunSimulation(region, inputConfig);
    RunAnalytics(region);

    


    

    
    return 0;
}