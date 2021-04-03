//
// Created by Mark on 13.03.2021.
//

#include "DATReader.h"

void DATReader::getProperties(int &numberOfRecords, vector<string> &names, vector<TypeOfNote> &types) {
    rewind(this->fin);

    numberOfRecords = this->numberOfRecords;

    int i;
    fread(&i, sizeof(int), 1, fin);
    fread(&i, sizeof(int), 1, fin);

    // setting column's names
    names = readNext();

    // setting types
    vector<string> s = readNext();
    types.clear();
    TypeOfNote typeOfCurrentNote;
    for (int i = 0; i < numberOfColumns; ++i) {
        typeOfCurrentNote.setType(s[i]);
        types.push_back(typeOfCurrentNote);
    }
}

vector<string> DATReader::readNext() {
    return readNext(fin);
}

FILE *DATReader::getFin() {
    return fin;
}

vector<string> DATReader::readNext(FILE *from) {
    vector<string> recordData;
    List list;

    for (int i = 0; i < numberOfColumns; ++i) {
        list.readFromFile(fin);
        recordData.push_back(list.get());
    }

    return recordData;
}

DATReader::DATReader(FILE *fin) {
    this->fin = fin;

    rewind(this->fin);
    fread(&numberOfColumns, sizeof(int), 1, fin);
    fread(&numberOfRecords, sizeof(int), 1, fin);
}

int DATReader::getNumberOfColumns() {
    return numberOfColumns;
}

int DATReader::getNumberOfRecords() {
    return numberOfRecords;
}
