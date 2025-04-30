#include "DataManagement.h"
using namespace std;

//GET CONFIG FILE
//VALIDATE
//OPEN CONFIG FILE
Config OpenConfig() {   //Function to open a given config.txt file and convert it into a Config class object
    ifstream myFile;
    string name;
    bool valid = false;

    while (!valid) {    //Will keep prompting user to enter file name until valid file is found
        cout << "Please enter name of config.txt file you want to open: ";
        cin >> name;
        myFile.open(name);

        if(myFile.is_open()) {
            valid = true;   //If file is found, while loop exits
        }
        else {
            cout << "File failed to open, try again." << endl;
        }
    }

    Config inputConfig;

    int index = 0;
    string fileInputLine;   //Temp string to hold line taken from textfile
    int i;

    getline(myFile, fileInputLine);    //Intaking region layout
    index = fileInputLine.find(":");
    if (index != string::npos) {    //Checking if the config file is formatted correctly
        inputConfig.SetRegion(fileInputLine.substr(index + 1));  //Creates substring of region file name and inserts it into Config class
    } else {
        cout << "Region layout in config file not formatted correctly" << endl;
    }


    getline(myFile, fileInputLine);    //Intaking time limit
    index = fileInputLine.find(":");
    if (index != string::npos) {    //Checking if the config file is formatted correctly
        int time = stoi(fileInputLine.substr(index + 1));
        inputConfig.SetTime(time);  //Creates substring of region file name and inserts it into Config class
    } else {
        cout << "Time limit in config file not formatted correctly" << endl;
    }



    getline(myFile, fileInputLine);    //Intaking refresh rate
    index = fileInputLine.find(":");
    if (index != string::npos) {    //Checking if the config file is formatted correctly
        int refreshRate = stoi(fileInputLine.substr(index + 1));
        inputConfig.SetRefreshRate(refreshRate);  //Creates substring of region file name and inserts it into Config class
    } else {
        cout << "Refresh rate in config file not formatted correctly" << endl;
    }



    myFile.close();
    
    //Intake wind direction
    int windDirection = 0;
    cout << endl;
    cout << "What direction should the wind blow?" << endl;
    cout << "1. North\t\t 2. East\t\t 3. South\t\t 4. West" << endl;
    cout << "Enter 1-4: ";
    cin >> windDirection;

    while (cin.fail() || windDirection > 4 || windDirection <= 0) { //Check if choice is valid
        cin.clear();
        cin.ignore(10000, '\n');    //If user accidentally enters character, this avoids an infinite loop bug
        cout << "Invalid option. Please choose an option 1-4" << endl;
        cout << "Enter 1-4: ";
        cin >> windDirection;
    }

    inputConfig.SetWindDirection(windDirection);

    return inputConfig;
}

Region OpenRegion(Config inputConfig) { //Opens region.csv file, validates file, and reads its contents into a Region class object
    ifstream myFile;
    string inputRegionName = inputConfig.GetRegion();

    vector<vector<Cell>> region;    //2D Vector that will be put into region class

    myFile.open(inputRegionName);

    if(!myFile.is_open()) {
        cout << "region.csv file failed to open. Please edit your config.txt file." << endl;
        exit(2);
    }


    string inputLine = "";

    int rows = -1; //Because loop will count empty line
    int cols = 0; 

    while (!myFile.eof()) {     //While we haven't reached the end of the csv file
        getline(myFile, inputLine); //Reads whole line from csv file

        vector<Cell> row;   //What will be added to the region 2D vector

        for (char inputCell : inputLine) {  //Iterate through the input line storing in the char inputCell  
            if (inputCell != ',') {     //Ignores ,
                Cell currentCell(inputCell);
                row.push_back(currentCell); //Add to row vector
                cols++;
            }
            
        } 
        region.push_back(row);  //Adds row to region
        rows++; //Everytime a row is pushed back, adds one more row layer to vector
    }

    myFile.close();
    cols = ceil(cols / rows);

    Region inputRegion(region, rows, cols); //ADD REGION VECTOR TO THIS 
    return inputRegion;
}





vector<Cell*> FormatCells(Region& region) {  //Formats the region into R - C - I for faster updating of Cells and ordering
    vector<vector<Cell>>& regVec = region.GetRegion(); //Passes region 2D vector by reference
    vector<Cell*> residentialVect;   //Vector for keeping track of residential
    vector<Cell*> orderedVector;    //Final vector to be returned
    for (int i = 0; i < region.GetRows(); i++) {
        for (int j = 0; j < region.GetCols(); j++) {
            if (regVec[i][j].GetCellType() == 'R') {        //Put residentials in separate vector to concatinate later
                residentialVect.push_back(&regVec[i][j]);
                regVec[i][j].SetRowIndex(i);
                regVec[i][j].SetColIndex(j);
            } 
            else if (regVec[i][j].GetCellType() == 'C') {     //Then put commercial in front of industrial in final vector
                orderedVector.insert(orderedVector.begin(), &regVec[i][j]);
                regVec[i][j].SetRowIndex(i);
                regVec[i][j].SetColIndex(j);
            }
            else if (regVec[i][j].GetCellType() == 'I') {
                orderedVector.push_back(&regVec[i][j]); //Puts industrial at back to order commercial and industrial
                regVec[i][j].SetRowIndex(i);
                regVec[i][j].SetColIndex(j);
            }
            else {
                regVec[i][j].SetRowIndex(i);
                regVec[i][j].SetColIndex(j);
                
            }
        } 
    }

    orderedVector.insert(orderedVector.begin(), residentialVect.begin(), residentialVect.end());

    return orderedVector;
}