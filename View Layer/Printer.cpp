//
// Created by Mark on 26.02.2021.
//

#include "Printer.h"

void Printer::printHeader() {
    printf("%10s ", names[0].c_str());
    for (int i = 1; i < numberOfColumns; ++i) {
        printf("| %10s ", names[i].c_str());
    }
    cout << endl;
    cout << "==========";
    for (int i = 1; i < numberOfColumns; ++i) {
        cout << "=|===========";
    }
    cout << endl;
}

void Printer::printNextRecord() {
    vector<string> recordData = readNext();
    printf("%10s ", recordData[0].c_str());
    for (int i = 1; i < numberOfColumns; ++i) {
        printf("| %10s ", recordData[i].c_str());
    }
    cout << endl;
}

Printer::Printer(istream &fin) : CSVReader(fin) {
    getProperties(numberOfRecords, names, types);
}

void Printer::print() {
    printHeader();
    rewind();
    for (int i = 0; i < numberOfRecords; ++i) {
        printNextRecord();
    }
}
