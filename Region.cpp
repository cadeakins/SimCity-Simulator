#include "Region.h"



vector<vector<Cell>>& Region::GetRegion() {    //Getters, GetRegion returns a reference so the whole array is not copied
    return region;
}



Region::Region(vector<vector<Cell>> inputVector, int rows, int cols) { //Parameterized constructor
    region = inputVector;
    this->rows = rows;
    this->cols = cols;
    availableGoods = 0;
    availableWorkers = 0;
}


void Region::PrintRegion() { //Outputs region
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (region[i][j].GetPopulation() == 0) {
                cout << region[i][j].GetCellType() << " ";
            }
            else {
                cout << region[i][j].GetPopulation() << " ";
            }
        } 
        cout << endl;  
    }
    cout << "---------------------------------------------------------------------------------" << endl;
}


void Region::PrintPollution() { //Outputs pollution in region
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (region[i][j].GetPollution() == 0) {
                cout << region[i][j].GetCellType() << "  ";
            }
            else {
                cout << region[i][j].GetPollution() << "  ";
            }
        } 
        cout << endl;  
    }
    cout << "---------------------------------------------------------------------------------" << endl;
}


int Region::GetCols() {
    return cols;
}

int Region::GetRows() {
    return rows;
}


void Region::SetAvailableWorkers(int availableWorkers) { //Setter and Getter for availableWorkers
    this->availableWorkers = availableWorkers;
} 
int Region::GetAvailableWorkers() {
    return availableWorkers;
}

void Region::SetAvailableGoods(int availableGoods) {  //Setter and Getter for availableGoods
    this->availableGoods = availableGoods;
}

int Region::GetAvailableGoods() {
    return availableGoods;
}
