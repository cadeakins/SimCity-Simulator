#include "Cell.h"

char Cell::GetCellType() { //Getters for private variable members
    return cellType;
}
int Cell::GetPopulation() {
    return population;
}
int Cell::GetPollution() {
    return pollution;
}
bool Cell::GetCanGrow() {
    return canGrow;
}

void Cell::SetCellType(char cellType){     //Setters for private variable members
    this->cellType = cellType;
}
void Cell::SetPopulation(int population) {
    this->population = population;
}
void Cell::SetPollution(int pollution) {
    this-> pollution = pollution;
}
void Cell::SetCanGrow(bool canGrow) {
    this->canGrow = canGrow;
}


Cell::Cell() {
    cellType = ' ';
    population = 0;
    pollution = 0;
    canGrow = false;
    happinessLevel = 100;
}

Cell::Cell(char cellType) {
    this->cellType = cellType;
    population = 0;
    pollution = 0;
    canGrow = false;
}


void Cell::SetRowIndex(int row) {
    rowIndex = row;
}
void Cell::SetColIndex(int col) {
    colIndex = col;
}


int Cell::GetRowIndex() {
    return rowIndex;
}
int Cell::GetColIndex() {
    return colIndex;
}


void Cell::SetHappinessLevel(int happinessLevel) {
    this->happinessLevel = happinessLevel;
}

int Cell::GetHappinessLevel() {
    return happinessLevel;
}
