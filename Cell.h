#ifndef CELL_H
#define CELL_H

class Cell {
    public:
        char GetCellType(); //Getters for private variable members
        int GetPopulation();
        int GetPollution();
        bool GetCanGrow();
        int GetRowIndex();
        int GetColIndex();

        void SetCellType(char cellType);    //Setters for private variable members
        void SetPopulation(int population);
        void SetPollution(int pollution);
        void SetCanGrow(bool canGrow);
        void SetRowIndex(int row);
        void SetColIndex(int col);

        Cell(); //Default constructor
        Cell(char cellType);    //Parameterized constructor 
        
    private:
        char cellType;
        int population;
        int pollution;
        bool canGrow;
        int rowIndex;
        int colIndex;
};

#endif