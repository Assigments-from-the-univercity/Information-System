//
// Created by Mark on 26.02.2021.
//

#ifndef INFORMATION_SYSTEM_PRINTER_H
#define INFORMATION_SYSTEM_PRINTER_H


#include <iostream>
#include "../Basic Units/TypeOfNote.h"
#include "../CSV Workers/CSVReader.h"

class Printer : public CSVReader {
private:
    int numberOfRecords;
    vector<string> names;
    vector<TypeOfNote> types;

    void printHeader();

    void printNextRecord();

public:
    Printer(istream &fin);

    void print();
};


#endif //INFORMATION_SYSTEM_PRINTER_H
