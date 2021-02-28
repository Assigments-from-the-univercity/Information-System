//
// Created by Mark on 26.02.2021.
//

#include "TableNotes.h"

TableNotes::TableNotes(string name, int numberOfRecords, int numberOfColumns,
                       vector<TypeOfNote> types, vector<List> names)
                       : TableDataWorker(name, numberOfRecords, numberOfColumns, types, names) {}

vector<vector<string>> TableNotes::get() {

}

void TableNotes::add(vector<string> recordsData) {
    List list;
    openForReading();

    for (int i = 0; i < numberOfColumns; ++i) {
        list.put(recordsData[i]);
        list.writeInFile(getFp());
    }
}

void TableNotes::change(vector<string> recordsData) {
    List list;
    openForWriting();
    FILE *fpOfCopy = fopen(TEMP_FILE_NAME.c_str(), "w+b");

    for (int i = 0; i < numberOfRecords; ++i) {
        list.readFromFile(getFp());
        if (recordsData[0] == list.get()) {
            for (int j = 1; j < numberOfColumns; ++j) {
                list.put(recordsData[i]);
                list.writeInFile(fpOfCopy);
            }
        }
        else {
            for (int j = 1; j < numberOfColumns; ++j) {
                list.readFromFile(getFp());
                list.writeInFile(fpOfCopy);
            }
        }
    }

    deleteTableFile();
    renameTempFile();
}

void TableNotes::deleteItem(string key) {
    List list;
    openForWriting();
    FILE *fpOfCopy = fopen(TEMP_FILE_NAME.c_str(), "w+b");

    for (int i = 0; i < numberOfRecords; ++i) {
        list.readFromFile(getFp());
        if (key == list.get()) {
            for (int j = 1; j < numberOfColumns; ++j) {
                list.readFromFile(getFp());
            }
        }
        else {
            for (int j = 1; j < numberOfColumns; ++j) {
                list.readFromFile(getFp());
                list.writeInFile(fpOfCopy);
            }
        }
    }

    deleteTableFile();
    renameTempFile();
}

void TableNotes::deleteTableFile() {
    string oldFile = "Data/Tables/" + getName() + ".dat";
    remove(oldFile.c_str());
}

void TableNotes::renameTempFile() {
    string originalName = "Data/Tables/" + getName() + ".dat";
    rename(TEMP_FILE_NAME.c_str(), originalName.c_str());
}
