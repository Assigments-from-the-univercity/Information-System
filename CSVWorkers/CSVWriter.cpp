//
// Created by Mark on 11.03.2021.
//

#include "CSVWriter.h"

ostream &CSVWriter::getFout() {
    return fout;
}

void
CSVWriter::setProperties(int numberOfRecords, vector<string> names, vector<TypeOfNote> types) {
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

void CSVWriter::writeNext(vector<string> recordData, ostream &to) {
    if (numberOfColumns != recordData.size()) {
        return;
    }
    for (int i = 0; i < numberOfColumns; ++i) {
        to << recordData[i] << ';';
    }
    to.flush();
    to << endl;
}

void CSVWriter::writeNext(vector<string> recordData) {
    writeNext(recordData, fout);
}

CSVWriter::CSVWriter(ostream &fout, int numberOfColumns) : fout(fout) {
    this->numberOfColumns = numberOfColumns;
}