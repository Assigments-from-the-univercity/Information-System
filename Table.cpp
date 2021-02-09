//
// Created by mark on 07.02.21.
//

#include "Table.h"

void Table::setProperties() {
    fread(&properties.numberOfNotes, INT_SIZE, 1, fpProp);
    fread(&properties.numberOfProperties, INT_SIZE, 1, fpProp);
    Table::Field field;
    for (int i = 0; i < properties.numberOfProperties; ++i) {
        fread(&field, sizeof(Table::Field), 1, fpProp);
        properties.values.push_back(field);
    }
}

Table::Table() {}

Table::Table(char name[]) {
    setTable(name);
}

void Table::setTable(char name[]) {
    strcpy(this->name, name);

    string stringName(name);
    string folderName = "tables/";
    string propName = "-prop";
    string sourceType = ".dat";

    string newFile = folderName + stringName + sourceType;
    string newPropFile = folderName + stringName + propName + sourceType;

    char fileName[newFile.length() + 1];
    strcpy(fileName, newFile.c_str());

    char propFileName[newPropFile.length() + 1];
    strcpy(propFileName, newPropFile.c_str());

    fp = fopen(fileName, "r+b");
    fpProp = fopen(propFileName, "r+b");
    setProperties();
}

void Table::printNotes(vector<Table::Request> request) {
    //TODO
}

void Table::addNote(vector<NoteValue> noteProperties) {
    //TODO
}