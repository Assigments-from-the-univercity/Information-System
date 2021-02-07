//
// Created by mark on 07.02.21.
//

#include "Table.h"

void Table::setProperties() {
    //TODO load properties from file
}

Table::Table() {}

Table::Table(char name[]) {
    setTable(name);
}

void Table::setTable(char name[]){
    strcpy(this->name, name);
    //TODO set up *fp for working with file
    //TODO set up *fpProp for working with file
    setProperties();
}

void Table::printNotes(vector<RequestDouble> requestDouble, vector<RequestString> requestString) {
    //TODO
}

void Table::addNote(vector<NoteValue> noteProperties) {
    //TODO
}