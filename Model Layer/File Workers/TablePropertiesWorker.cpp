//
// Created by Mark on 23.02.2021.
//

#include "../../Header.h"
#include "TablePropertiesWorker.h"

void TablePropertiesWorker::safeState() {
    openForWriting();
    fwrite(&numberOfRecords, INT_SIZE, 1, getFp());
    fwrite(&numberOfColumns, INT_SIZE, 1, getFp());
    for (int i = 0; i < numberOfColumns; ++i) {
        types[i].writeInFile(getFp());
        names[i].writeInFile(getFp());
    }
    fflush(getFp());
}

void TablePropertiesWorker::loadState() {
    openForReading();
    fread(&numberOfRecords, INT_SIZE, 1, getFp());
    fread(&numberOfColumns, INT_SIZE, 1, getFp());
    for (int i = 0; i < numberOfColumns; ++i) {
        types[i].readFromFile(getFp());
        names[i].readFromFile(getFp());
    }
    fflush(getFp());
}

TablePropertiesWorker::TablePropertiesWorker(string fileName) : FileWorker(fileName + "dat", TABLES_FOLDER) {
    loadState();
}

void TablePropertiesWorker::setProperties(int numberOfRecords, int numberOfColumns, vector<TypeOfNote> types, vector<List> names) {
    this->numberOfRecords = numberOfRecords;
    this->numberOfColumns = numberOfColumns;
    this->types = types;
    this->names = names;

    safeState();
}

void TablePropertiesWorker::getProperties(int &numberOfRecords, int &numberOfColumns, vector<TypeOfNote> types, vector<List> names) {
    numberOfRecords = this->numberOfRecords;
    numberOfColumns = this->numberOfColumns;
    types = this->types;
    names = this->names;
}