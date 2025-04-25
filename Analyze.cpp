#include "Analyze.h"


void RunAnalytics(Region& region) {
    for (int i = 0; i < 20; i++) {  //Blank space
        cout << endl;
    }

    region.PrintRegion();   //Final Region

    Point topLeft{0,0};
    Point topRight{0, region.GetCols() - 1};
    Point botLeft{region.GetRows() - 1, 0};

    Coords wholeMapCoords{topLeft,topRight,botLeft};
    Analytics wholeRegion = AnalyzeArea(region, wholeMapCoords);
    //Analyze whole region and output pop per region, and pollution 
    cout << "\t\t              Final Region " << endl;
    cout << "\t\tPopulation \t | \t\t Pollution" << endl;
    cout << "Residential:\t" << wholeRegion.residentialPopulation << "\t\t\t\t" << wholeRegion.residentialPollution << endl;
    cout << "Industrial:\t" << wholeRegion.industrialPopulation << "\t\t\t\t" << wholeRegion.industrialPollution << endl;
    cout << "Commercial:\t" << wholeRegion.commercialPopulation << "\t\t\t\t" << wholeRegion.commercialPollution << endl;


    cout << "---------------------------------------------------------------------------------" << endl;
    
    

    int choice = 0;
    while (choice != 2) {
        cout << "\t\t     Analyze Menu " << endl;
        cout << "1. Analyze Rectangular Area\t\t 2. Quit" << endl;
        cout << "Enter Choice: ";
        cin >> choice;

        while (choice > 2 || choice <= 0) { //Check if choice is valid
            cout << "Invalid option. Please choose either 1 or 2" << endl;
            cout << "Enter Choice: ";
            cin >> choice;
        }

        switch (choice) {
            case 1:  {   //Analyze Rectangular Area
                int topLeftRow, topLeftCol, topRightRow, topRightCol, botLeftRow, botLeftCol;
                bool validCoords = false;
                Coords inputCoords;
                
                cout << endl;
                cout << "This will analyze a rectangular area of your choosing" << endl;
                cout << endl;

                while (!validCoords) {
                    cout << "Please enter coordinates just as two numbers separated by a space, ex: 2 3" << endl;
                    cout << endl;
                    
                    cout << "Enter top-left coordinate (row col): ";
                    cin >> topLeftRow;
                    cin >> topLeftCol;
                    cout << endl;

                    cout << "Enter top-right coordinate (row col): ";
                    cin >> topRightRow;
                    cin >> topRightCol;
                    cout << endl;

                    cout << "Enter bottom-left coordinate (row col): ";
                    cin >> botLeftRow;
                    cin >> botLeftCol;
                    cout << endl;
                
                    

                    Point topLeft{topLeftRow,topLeftCol};
                    Point topRight{topRightRow, topRightCol};
                    Point botLeft{botLeftRow, botLeftCol};

                    inputCoords = {topLeft, topRight, botLeft};


                    validCoords = CheckValidArea(region, inputCoords);
                    if (!validCoords) {
                        cout << "Invalid coords, please try again" << endl;
                        cout << endl;
                    }
                }

                Analytics regionData = AnalyzeArea(region, inputCoords);
                cout << "\t\tPopulation \t | \t\t Pollution" << endl;
                cout << "Residential:\t" << regionData.residentialPopulation << "\t\t\t\t" << regionData.residentialPollution << endl;
                cout << "Industrial:\t" << regionData.industrialPopulation << "\t\t\t\t" << regionData.industrialPollution << endl;
                cout << "Commercial:\t" << regionData.commercialPopulation << "\t\t\t\t" << regionData.commercialPollution << endl;
                break;
            }

            case 2: 
                cout << "Thank you for playing!" << endl;
                break;
        };



        
    }
    
    }
   






Analytics AnalyzeArea(Region& region, Coords coords) {     //Returns information about a rectangular area
    Analytics areaData{0,0,0,0,0,0};
    vector<vector<Cell>> regVec = region.GetRegion();


    for (int i = coords.topLeft.row; i < coords.botLeft.row; i++) {
        for (int j = coords.topLeft.col; j < coords.topRight.col; j++) {
            if (regVec[i][j].GetCellType() == 'R') {    //Residential cell located
                areaData.residentialPopulation += regVec[i][j].GetPopulation();
                areaData.residentialPollution += regVec[i][j].GetPollution(); 
            }

            else if (regVec[i][j].GetCellType() == 'C') {   //Commercial cell located
                areaData.commercialPopulation += regVec[i][j].GetPopulation();
                areaData.commercialPollution += regVec[i][j].GetPollution();
            }

            else if (regVec[i][j].GetCellType() == 'I') { //Industrial cell located
                areaData.industrialPopulation += regVec[i][j].GetPopulation();
                areaData.industrialPollution += regVec[i][j].GetPollution();
            }
        }
    }
    //Return Analytics 
    return areaData;
}


bool CheckValidArea(Region& region, Coords coords) {        //Sees if area is valid
    bool isRectangle = true;  //Assumed true until proven false
    bool inBounds = true;

    //Check if coords are rectangular         
    if (coords.topLeft.col != coords.botLeft.col) {     //Can't be diagonal parallelogram, only rectangle
        isRectangle = false;
    }

    if (coords.topLeft.row != coords.topRight.row) {
        isRectangle = false;
    }



    if (coords.topLeft.col != coords.botLeft.col) {     //Can't have area of 0
        isRectangle = false;
    }

    if (coords.botLeft.row <= coords.topLeft.row) {
        isRectangle = false;
    }

    
    //Check if coords are in bounds
    if (coords.topLeft.col < 0 || coords.topLeft.row < 0) {    //Low Case
        inBounds = false;
    }

    if (coords.topRight.col >= region.GetCols() || coords.botLeft.row >= region.GetRows()) {   //High case
        inBounds = false;
    }
    


    bool isValid = false;
    if(isRectangle && inBounds) {   //If it is both a rectangle and in bounds, good to go
        isValid = true;
    }


    return isValid;
}