//
// Created by Mark on 11.03.2021.
//

#include "FileWriter.h"

ostream &FileWriter::getFout() {
    return fout;
}

void
FileWriter::setProperties(vector<string> names, vector<TypeOfNote> types) {
    // setting column'typesInString names
    writeNext(names);

    // setting types
    vector<string> typesInString;
    TypeOfNote typeOfCurrentNote;
    for (int i = 0; i < numberOfColumns; ++i) {
        typeOfCurrentNote = types[i];
        typesInString.push_back(typeOfCurrentNote.getType());
    }
    writeNext(typesInString);
}

void FileWriter::writeNext(vector<string> recordData, ostream &to) {
    if (numberOfColumns != recordData.size()) {
        return;
    }
    for (int i = 0; i < numberOfColumns; ++i) {
        to << recordData[i] << ';';
    }
    to.flush();
    to << endl;
}

void FileWriter::writeNext(vector<string> recordData) {
    writeNext(recordData, fout);
}

FileWriter::FileWriter(ostream &fout, int numberOfColumns) : fout(fout) {
    this->numberOfColumns = numberOfColumns;
}

FileWriter::FileWriter(ostream &fout, int numberOfColumns, vector<string> names, vector<TypeOfNote> types) : fout(fout) {
    this->numberOfColumns = numberOfColumns;
    setProperties(names, types);
}
