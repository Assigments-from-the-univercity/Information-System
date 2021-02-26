//
// Created by Mark on 26.02.2021.
//

#ifndef INFORMATION_SYSTEM_PRINTER_H
#define INFORMATION_SYSTEM_PRINTER_H


#include "../Basic Units/TypeOfNote.h"

class Printer {
private:
    int numberOfRecords;
    int numberOfColumns;
    vector<TypeOfNote> types;
    vector<string> names;
    int current;
    vector<vector<string>> data;

    void printHeader();

    void printRecord();

public:
    Printer(int numberOfRecords, int numberOfColumns, vector<TypeOfNote> types,
            vector<string> names, vector<vector<string>> data);
};


#endif //INFORMATION_SYSTEM_PRINTER_H
