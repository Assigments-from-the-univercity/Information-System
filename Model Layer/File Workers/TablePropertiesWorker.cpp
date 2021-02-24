//
// Created by Mark on 23.02.2021.
//

#include "../../Header.h"
#include "TablePropertiesWorker.h"

void TablePropertiesWorker::safeState() {

}

void TablePropertiesWorker::loadState() {

}

//TODO set correct path to file
TablePropertiesWorker::TablePropertiesWorker(string fileName) : FileWorker(fileName, TABLES_FOLDER) {
    loadState();
}

void TablePropertiesWorker::setProperties(int numberOfColumns, vector<TypeOfNote> types, vector<List> names) {
    this->numberOfColumns = numberOfColumns;
    this->types = types;
    this->names = names;

    safeState();
}

void TablePropertiesWorker::getProperties(int &numberOfColumns, vector<TypeOfNote> types, vector<List> names) {
    numberOfColumns = this->numberOfColumns;
    types = this->types;
    names = this->names;
}