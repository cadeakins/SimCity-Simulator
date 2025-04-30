#include "Simulation.h"

Simulation::Simulation() {    //Default Constructor
    currentTimeStep = 0;
    noChange = false;
}

void Simulation::RunSimulation(Region& region, Config& config) { //Handles the simulation phase

    for (int i = 0; i < 20; i++) {  //Blank space
        cout << endl;
    }
    region.PrintRegion();   //Initial region without available workers or goods
    cout << "\t\t     Initial Region State " << endl;
    cout << "---------------------------------------------------------------------------------" << endl;
    cout << endl;

    chrono::seconds waitTime = chrono::seconds(config.GetRefreshRate());
    vector<Cell*> formattedCells = FormatCells(region);

    //While loop that keeps running as long as time limit is not reached and things have changed the last turn
    while (currentTimeStep != config.GetTime() && !noChange) {      //Checks if time limit is reached or if nothings changed in 2 consecutive turns
        this_thread::sleep_for(waitTime);   //Pauses program for refreshRate time in seconds


        for (int i = 0; i < 20; i++) {  //Blank space
            cout << endl;
        }


        region.PrintRegion();   //Outputs region, available goods, and workers
        cout << "Available Workers: " << region.GetAvailableWorkers() << "\t\t" << "Available Goods: " << region.GetAvailableGoods() << endl;
        cout << "\t\t     Timestep: " << currentTimeStep << endl;
        cout << "---------------------------------------------------------------------------------" << endl;




        UpdateCity(region, formattedCells); ////Growth checker and updater
        SimulateWind(region, config);
    }
}













int Simulation::GetCurrentTimeStep() {
    return currentTimeStep;
}

void Simulation::SetCurrentTimeStep(int timeStep) {
    currentTimeStep = timeStep;
}


bool Simulation::GetNoChange() {
    return noChange;
}
void Simulation::SetNoChange(bool noChange) {
    this->noChange = noChange;
}



void Simulation::UpdateCity(Region& region, vector<Cell*> orderedCells) {  //Iterates through each cell in Region and checks growth conditions, updates accordingly, returns true if change has NOT occured
    vector<Cell*> adjCells;
    bool alreadyGrown;  //To have only growth of 1 every time step
    vector<UpdateQueue> updateQueue;        //Cell*   Population    Workers    Goods 
    noChange = true;    //Nothing has happened until something happens


    //Adding workers is at end of loop, subtracting is during for loop


    for (Cell* current : orderedCells) {
        switch (current->GetCellType()) {               //TODO Create happiness level conditions 
            case 'R':   //Residential case
                if (current->GetHappinessLevel() < 20 && current->GetPopulation() != 0) {    //If happiness level is low enough, residents move out
                    int currentPopulation = current->GetPopulation();
                    current->SetPopulation(currentPopulation - 1);

                    if (region.GetAvailableWorkers() != 0) {     //If there are available workers, -1 them. If not, remove a commercial population
                        int currentWorkers = region.GetAvailableWorkers();
                        region.SetAvailableWorkers(currentWorkers - 1);
                
                    } else {
                        for (Cell* orderIterator : orderedCells) {  //Find a commercial Cell with population of atleast 1 and reduce by 1
                            if (orderIterator->GetCellType() == 'C' && orderIterator->GetPopulation() > 0) {
                                int currentCommercialPopulation = orderIterator->GetPopulation();
                                orderIterator->SetPopulation(currentCommercialPopulation - 1);
                                break;
                            }
                        }
                    }
                }


                if (current->GetHappinessLevel() > 50) {    //If happiness level is less than 50, no new residents will move in
                    if (current->GetPopulation() == 0) {    //Pop = 0 case
                        adjCells = findAdjacentCells(region, current);


                        for (int i = 0; i < adjCells.size() && !alreadyGrown; i++) { //Iterate through adjacent cells, checks if already set to increase population in next time step
                            if (adjCells[i]->GetCellType() == 'T' || adjCells[i]->GetCellType() == '#') {   //If there is a powerline next to 0 pop res, +1 pop
                                updateQueue.push_back({current, 1, 1, 0});  //Workers & Pop += 1
                                alreadyGrown = true;
                                noChange = false;
                            }

                            if (adjCells[i]->GetPopulation() >= 1) {
                                updateQueue.push_back({current, 1, 1, 0}); //Workers & Pop += 1
                                alreadyGrown = true;
                                noChange = false;
                            }
                        }
                    }


                else if (current->GetPopulation() == 1) {   //Pop = 1 case
                    adjCells = findAdjacentCells(region, current);
                    int adjCount = 0;   //Keep track of how many adjacent meet growth criteria

                    for (int i = 0; i < adjCells.size() && !alreadyGrown; i++) { //Iterate through adjacent cells, checks if already set to increase population in next time step

                        if (adjCells[i]->GetPopulation() >= 1) {
                            adjCount += 1;  //Only increase population if 2 adj cells have pop of atleast 1

                            if(adjCount >= 2) {
                                updateQueue.push_back({current, 1, 1, 0}); //Workers & Pop += 1
                                alreadyGrown = true;
                                noChange = false;
                            }
                        }
                    }
                }


                else if (current->GetPopulation() == 2) {   //Pop = 2 case
                    adjCells = findAdjacentCells(region, current);
                    int adjCount = 0;   //Keep track of how many adjacent meet growth criteria

                    for (int i = 0; i < adjCells.size() && !alreadyGrown; i++) { //Iterate through adjacent cells, checks if already set to increase population in next time step

                        if (adjCells[i]->GetPopulation() >= 2) {
                            adjCount += 1;  //Only increase population if 2 adj cells have pop of atleast 2

                            if(adjCount >= 4) {
                                updateQueue.push_back({current, 1, 1, 0});
                                alreadyGrown = true;
                                noChange = false;
                            }
                        }
                    }


                }
                else if (current->GetPopulation() == 3) {   //Pop = 3 case
                    adjCells = findAdjacentCells(region, current);
                    int adjCount = 0;   //Keep track of how many adjacent meet growth criteria

                    for (int i = 0; i < adjCells.size() && !alreadyGrown; i++) { //Iterate through adjacent cells, checks if already set to increase population in next time step

                        if (adjCells[i]->GetPopulation() >= 3) {
                            adjCount += 1;  //Only increase population if 2 adj cells have pop of atleast 1

                            if(adjCount >= 6) {
                                updateQueue.push_back({current, 1, 1, 0});
                                alreadyGrown = true;
                                noChange = false;
                            }
                        }
                    }


                }
                else if (current->GetPopulation() == 4) {   //Pop = 4 case
                    adjCells = findAdjacentCells(region, current);
                    int adjCount = 0;   //Keep track of how many adjacent meet growth criteria

                    for (int i = 0; i < adjCells.size() && !alreadyGrown; i++) { //Iterate through adjacent cells, checks if already set to increase population in next time step

                        if (adjCells[i]->GetPopulation() >= 4) {
                            adjCount += 1;  //Only increase population if 2 adj cells have pop of atleast 1

                            if(adjCount >= 8) {
                                updateQueue.push_back({current, 1, 1, 0});
                                alreadyGrown = true;
                                noChange = false;
                            }
                        }
                    }


                }
            }
            
                break;







            case 'C':   //Commercial case, priority over industrial, consumes goods and workers
                alreadyGrown = false;
                if (current->GetPopulation() == 0) {    //Pop = 0 case
                    adjCells = findAdjacentCells(region, current);
                    int adjCount = 0;


                    for (int i = 0; i < adjCells.size(); i++) {
                        if (adjCells[i]->GetPopulation() >= 1) {
                            adjCount++;
                        }
                    }

                    for (int i = 0; i < adjCells.size() && !alreadyGrown; i++) { //Iterate through adjacent cells, checks if already set to increase population in next time step
                        if ((adjCells[i]->GetCellType() == 'T' || adjCells[i]->GetCellType() == '#')) {   //If there is a powerline next to 0 pop res, +1 pop
                            if (region.GetAvailableGoods() >= 1 && region.GetAvailableWorkers() >= 1) {
                                updateQueue.push_back({current, 1, 0, 0});                      //Pop + 1, Workers - 1, Goods - 1
                                region.SetAvailableWorkers(region.GetAvailableWorkers() - 2);
                                region.SetAvailableGoods(region.GetAvailableGoods() - 1); 
                                alreadyGrown = true;
                                noChange = false;
                            }
                        }

                        if (adjCount >= 1 && region.GetAvailableWorkers() >= 1 && region.GetAvailableGoods() >= 1) {    //Adjacent to at least one other cell with pop >= 1
                            updateQueue.push_back({current, 1, 0, 0});                      //Pop + 1, Workers - 1, Goods - 1
                            region.SetAvailableWorkers(region.GetAvailableWorkers() - 2);
                            region.SetAvailableGoods(region.GetAvailableGoods() - 1); 
                            alreadyGrown = true;
                            noChange = false;
                        }

                    }
                }


                else if (current->GetPopulation() == 1) {   //Pop = 1 case
                    adjCells = findAdjacentCells(region, current);
                    int adjCount = 0;

                    for (int i = 0; i < adjCells.size(); i++) {
                        if (adjCells[i]->GetPopulation() >= 1) {
                            adjCount++;
                        }
                    }
                    
                    for (int i = 0; i < adjCells.size() && !alreadyGrown; i++) { //Iterate through adjacent cells, checks if already set to increase population in next time step
                        if (adjCount >= 2 && region.GetAvailableWorkers() >= 1 && region.GetAvailableGoods() >= 1) {   //Adjacency case
                            updateQueue.push_back({current, 1, 0, 0});  
                            region.SetAvailableWorkers(region.GetAvailableWorkers() - 2); //Pop + 1, Workers - 1, Goods - 1
                            region.SetAvailableGoods(region.GetAvailableGoods() - 1);
                            alreadyGrown = true;
                            noChange = false;
                        }
                    }

                    

                }

                break; 










            case 'I':   //Industrial case, consumes workers
                alreadyGrown = false;
                if (current->GetPopulation() == 0) {    //Pop = 0 case
                    adjCells = findAdjacentCells(region, current);
                    

                    for (int i = 0; i < adjCells.size() && !alreadyGrown; i++) { //Iterate through adjacent cells, checks if already set to increase population in next time step
                        if (adjCells[i]->GetCellType() == 'T' || adjCells[i]->GetCellType() == '#') {   //If there is a powerline next to 0 pop res, +1 pop
                                if (region.GetAvailableWorkers() >= 2) {
                                updateQueue.push_back({current, 1, 0, 1});  
                                region.SetAvailableWorkers(region.GetAvailableWorkers() - 3);   //Pop + 1, Workers - 2, Goods +1 not sure why subtracting 3 works but subtracting two doesnt, but this functions as expected
                                SpreadPollution(region, current);   //Updates pollution
                                alreadyGrown = true;
                                noChange = false;
                                }
                        }

                        if ((adjCells[i]->GetPopulation() >= 1) && (region.GetAvailableWorkers() >= 2)) {   //Adjacency case
                            updateQueue.push_back({current, 1, 0, 1});  
                            region.SetAvailableWorkers(region.GetAvailableWorkers() - 3); //Pop + 1, Workers - 2, Goods + 1
                            SpreadPollution(region, current);   //Updates pollution
                            alreadyGrown = true;
                            noChange = false;
                        }
                    }
                }

                else if (current->GetPopulation() == 1) {   //Pop = 1 case
                    adjCells = findAdjacentCells(region, current);
                    int adjCount = 0;

                    for (int i = 0; i < adjCells.size(); i++) {     //Sees how many cells adjacent have population of at least 1
                        if (adjCells[i]->GetPopulation() >= 1) {
                            adjCount++;
                        }
                    }

                    for (int i = 0; i < adjCells.size() && !alreadyGrown; i++) { //Iterate through adjacent cells, checks if already set to increase population in next time step
                        if (adjCount >= 2 && (region.GetAvailableWorkers() >= 2)) {   //Adjacency case
                            updateQueue.push_back({current, 1, 0, +1});  
                            region.SetAvailableWorkers(region.GetAvailableWorkers() - 3); //Pop + 1, Workers - 2, Goods + 1
                            SpreadPollution(region, current);   //Updates pollution
                            alreadyGrown = true;
                            noChange = false;
                        }
                    }
                        
                }


                else if (current->GetPopulation() == 2) {   //Population = 2 case
                    adjCells = findAdjacentCells(region, current);
                    int adjCount = 0;

                    for (int i = 0; i < adjCells.size(); i++) {     //Sees how many cells adjacent have population of at least 1
                        if (adjCells[i]->GetPopulation() >= 2) {
                            adjCount++;
                        }
                    }

                    for (int i = 0; i < adjCells.size() && !alreadyGrown; i++) { //Iterate through adjacent cells, checks if already set to increase population in next time step
                        if (adjCount >= 4 && (region.GetAvailableWorkers() >= 2)) {   //Adjacency case
                            updateQueue.push_back({current, 1, 0, 1});  
                            region.SetAvailableWorkers(region.GetAvailableWorkers() - 3); //Pop + 1, Workers - 2, Goods + 1
                            SpreadPollution(region, current);   //Updates pollution
                            alreadyGrown = true;
                            noChange = false;
                        }
                    }
                        

                }
                    break;


        }
    }

    for(UpdateQueue updater : updateQueue) {
        int updatedPopulation = updater.current->GetPopulation() + updater.newPopulation;   //Adds population to sum
        int updatedWorkers = region.GetAvailableWorkers() + updater.newWorkers;      //Adds available workers to sum
        int updatedGoods = region.GetAvailableGoods() + updater.newGoods;       //Adds available goods to sum


        updater.current->SetPopulation(updatedPopulation);      //Updates actual values based on sums
        region.SetAvailableWorkers(updatedWorkers);
        region.SetAvailableGoods(updatedGoods);
    }
    currentTimeStep++;  //Update time step
}



void Simulation::SpreadPollution(Region& region, Cell* current) {
    vector<Cell*> adjCells = findAdjacentCells(region, current);    //Adjacent cells
    int currentPollution;

    for (int i = 0; i < adjCells.size(); i++) {     //Adds one to the pollution of all adjacent cells
        currentPollution = adjCells[i]->GetPollution() + 1;
        adjCells[i]->SetPollution(currentPollution);
    }

    currentPollution = current->GetPollution() + 1; //Updates current Cell's pollution since findAdjacentCells exludes the center
    current->SetPollution(currentPollution);
}













vector<Cell*> Simulation::findAdjacentCells(Region& region, Cell* centerCell) { //Returns all adjacent Cells in a vector of cell pointers
    vector<Cell*> adjCells;
    deque<int> rowBounds{-1,0,1};  //Assumed center case 
    deque<int> colBounds{-1,0,1};


    //Check for high edge case on row and col   (if row = rows or if col = cols)
    if (centerCell->GetRowIndex() == region.GetRows() - 1) {
        rowBounds.pop_back();  //Dont go past row limits of map
    }

    if (centerCell->GetColIndex() == region.GetCols() - 1) {
        colBounds.pop_back();  //Dont go past col limits of map
    }
    

    //Check for low edge case on row and col  (if row/col is = 0)
    if (centerCell->GetRowIndex() == 0) {
        rowBounds.pop_front();
    }

    if (centerCell->GetColIndex() == 0) {
        colBounds.pop_front();
    }


    int tempRowIndex;
    int tempColIndex;
    vector<vector<Cell>>& regVec = region.GetRegion();

    for (int i = 0; i < rowBounds.size(); i++) {
        tempRowIndex = (centerCell->GetRowIndex() + rowBounds.at(i));  // n +- 1 depending on bounds check
        for (int j = 0; j < colBounds.size(); j++) {
            tempColIndex = (centerCell->GetColIndex() + colBounds.at(j));

            if (tempRowIndex == centerCell->GetRowIndex() && tempColIndex == centerCell->GetColIndex()) {   //Dont count the centerCell
                continue;
            }
            adjCells.push_back(&regVec[tempRowIndex][tempColIndex]);
        } 
    }

    return adjCells;
}



void Simulation::SimulateWind(Region& region, Config& config) {
    vector<vector<Cell>>& regVec = region.GetRegion(); //Passes region 2D vector by reference

    for (int i = 0; i < region.GetRows(); i++) {        //Iterates through whole region
        for (int j = 0; j <  region.GetCols(); j++) {
            if (regVec[i][j].GetPollution() >= 2) {     //Only spread wind if pollution is greater than or equal to 2
                int currentPollution = regVec[i][j].GetPollution(); //For updating pollution level
                switch (config.GetWindDirection()) {
                    case 1: //North Wind
                        if (i != 0) {     //Check if update would be in bounds
                            regVec[i-1][j].SetPollution(currentPollution + 1);
                        }
                    break;

                    case 2: //East Wind
                        if (j != (region.GetCols() - 1)) {
                            regVec[i][j+1].SetPollution(currentPollution + 1);
                        }
                    break;

                    case 3: //South Wind
                        if (i != region.GetRows() - 1) {
                            regVec[i+1][j].SetPollution(currentPollution + 1);
                        }
                    break;

                    case 4: //West Wind
                        if (j != 0) {
                            regVec[i][j-1].SetPollution(currentPollution + 1);
                        }

                    break;
                }
            }
        }
    }
}