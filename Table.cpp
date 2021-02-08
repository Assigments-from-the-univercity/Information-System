//
// Created by mark on 07.02.21.
//

#include "Table.h"

void Table::setProperties() {
    fread(&properties.numberOfNotes, INT_SIZE, 1, fpProp);
    fwrite(&properties.numberOfProperties, INT_SIZE, 1, fpProp);
    fwrite(&properties.sizeOfVector, INT_SIZE, 1, fpProp);
    fwrite(&properties.values, properties.sizeOfVector, 1, fpProp);
}

Table::Table() {}

Table::Table(char name[]) {
    setTable(name);
}

void Table::setTable(char name[]) {
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



    strcpy(this->name, name);
//    char* tableName = makeNewCharArray("", name, ".dat");
//    string nameString(name);
//    string fileName = nameString + ".dat";
//    string filePropName = nameString + "-prop.dat";
//
//    char tableName[fileName.size() + 1];
//    strcpy(tableName, fileName.c_str());
//    tableName[fileName.size()] = '\0';
//
//    char tablePropName[filePropName.size() + 1];
//    strcpy(tablePropName, filePropName.c_str());
//    tablePropName[filePropName.size()] = '\0';

    fp = fopen(fileName, "r+b");
//    char* tablePropName = makeNewCharArray("", name, "-prop.dat");
    fpProp = fopen(propFileName, "r+b");
    setProperties();
}

void Table::printNotes(vector<Table::Request> request) {
    //TODO
}

void Table::addNote(vector<NoteValue> noteProperties) {
    //TODO
}