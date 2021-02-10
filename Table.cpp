//
// Created by mark on 07.02.21.
//

#include "Table.h"
#include <iomanip>
#include <string>

void Table::getProperties() {
    fread(&properties.numberOfNotes, INT_SIZE, 1, fpProp);
    fread(&properties.numberOfProperties, INT_SIZE, 1, fpProp);
    Table::Field field;
    for (int i = 0; i < properties.numberOfProperties; ++i) {
        fread(&field, sizeof(Table::Field), 1, fpProp);
        properties.values.push_back(field);
    }
}

void Table::setProperties() {
    openFpPropForWriting();

    fwrite(&properties.numberOfNotes, INT_SIZE, 1, fpProp);
    fwrite(&properties.numberOfProperties, INT_SIZE, 1, fpProp);
    for (int i = 0; i < properties.numberOfProperties; ++i) {
        fwrite(&properties.values[i], sizeof(Table::Field), 1, fpProp);
    }

    fflush(fpProp);

    openFpPropForReading();
}

void Table::printHeader() {
    printf("%3s ", "id");
    for (int i = 0; i < properties.numberOfProperties; ++i) {
        printf("| %10s ", properties.values[i].name);
    }
    cout << endl;
    cout << "===";
    for (int i = 0; i < properties.numberOfProperties; ++i) {
        cout << "=|===========";
    }
    cout << endl;
}

void Table::printNote(vector<NoteValue> noteProperties, int id) {
    printf("%3d ", id);
    for (int i = 0; i < noteProperties.size(); ++i) {
        printf("| %10s ", noteProperties[i].value);
    }
    cout << endl;
}

void Table::openFpForReading() {
    string stringName(name);
    string folderName = "tables/";
    string sourceType = ".dat";
    string newFile = folderName + stringName + sourceType;

    char fileName[newFile.length() + 1];
    strcpy(fileName, newFile.c_str());

    fp = fopen(fileName, "r+b");
}

void Table::openFpForWriting() {
    string stringName(name);
    string folderName = "tables/";
    string sourceType = ".dat";
    string newFile = folderName + stringName + sourceType;

    char fileName[newFile.length() + 1];
    strcpy(fileName, newFile.c_str());

    fp = fopen(fileName, "w+b");
}

void Table::openFpPropForReading() {
    string stringName(name);
    string folderName = "tables/";
    string propName = "-prop";
    string sourceType = ".dat";

    string newPropFile = folderName + stringName + propName + sourceType;

    char propFileName[newPropFile.length() + 1];
    strcpy(propFileName, newPropFile.c_str());

    fpProp = fopen(propFileName, "r+b");
}

void Table::openFpPropForWriting() {
    string stringName(name);
    string folderName = "tables/";
    string propName = "-prop";
    string sourceType = ".dat";

    string newPropFile = folderName + stringName + propName + sourceType;

    char propFileName[newPropFile.length() + 1];
    strcpy(propFileName, newPropFile.c_str());

    fpProp = fopen(propFileName, "w+b");
}

void Table::writeNoteInFile(vector<NoteValue> noteProperties) {
    for (int i = 0; i < properties.numberOfProperties; ++i) {
        fwrite(&noteProperties[i], sizeof(NoteValue), 1, fp);
    }
    fflush(fp);
}

vector<Table::NoteValue> Table::readNextNote() {
    //TODO
    vector<NoteValue> result;
    NoteValue value;
    for (int i = 0; i < properties.numberOfProperties; ++i) {
        fwrite(&value, sizeof(NoteValue), 1, fp);
        result.push_back(value);
    }
    return result;
}

Table::Table() {}

Table::Table(char name[]) {
    setTable(name);
}

void Table::setTable(char name[]) {
    strcpy(this->name, name);

    openFpForReading();
    openFpPropForReading();

    getProperties();
}

void Table::printNotes(vector<Table::Request> request) {
    printHeader();

    vector<NoteValue> noteProperties;
    rewind(fp);

    for (int i = 0; i < properties.numberOfNotes; ++i) {
        noteProperties = readNextNote();
        for (int j = 0; j < properties.numberOfProperties; ++j) {
            if (request[j].state != Request::State::IGNORE) {
                if (properties.values[j].type == TypeOfNote::STRING) {
                    double value = stod(noteProperties[j].value), target = stod(request[j].value);
                    switch (request[j].state){
                        case Request::State::LESS:
                            if (value < target){
                                break;
                            } else {
                                continue;
                            }
                        case Request::State::MORE:
                            if (value > target){
                                break;
                            } else {
                                continue;
                            }
                        case Request::State::NOT_MORE:
                            if (value <= target){
                                break;
                            } else {
                                continue;
                            }
                        case Request::State::NOT_LESS:
                            if (value >= target){
                                break;
                            } else {
                                continue;
                            }
                        case Request::State::EQUAL:
                            if (value == target){
                                break;
                            } else {
                                continue;
                            }
                        default: continue;
                    }
                } else if (properties.values[j].type == TypeOfNote::DOUBLE) {
                    string value = noteProperties[j].value, target = request[j].value;
                    switch (request[j].state){
                        case Request::State::EQUAL:
                            if (value == target){
                                break;
                            } else {
                                continue;
                            }
                        case Request::State::INCLUDED:
                            if (value.find(target)){
                                break;
                            } else {
                                continue;
                            }
                        default: continue;
                    }
                }
            }
            if (j == properties.numberOfProperties - 1) {
                printNote(noteProperties, i + 1);
            }
        }
    }
}

void Table::addNote(vector<NoteValue> noteProperties) {
    writeNoteInFile(noteProperties);
    properties.numberOfNotes++;
    setProperties();
    getProperties();
    cout << "line is added: " << endl;

    printHeader();
    printNote(noteProperties, properties.numberOfNotes);
}