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

void Table::setTable(char name[]){
    strcpy(this->name, name);
    char* tableName = makeNewCharArray("", name, ".dat");
    fp = fopen(tableName, "r+b");
    char* tablePropName = makeNewCharArray("", name, "-prop.dat");
    fp = fopen(tablePropName, "r+b");
    setProperties();
}

void Table::printNotes(vector<RequestDouble> requestDouble, vector<RequestString> requestString) {
    //TODO
}

void Table::addNote(vector<NoteValue> noteProperties) {
    //TODO
}