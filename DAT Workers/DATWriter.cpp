//
// Created by Mark on 13.03.2021.
//

#include "DATWriter.h"
#include "../Basic Units/List.h"

void DATWriter::setProperties(int numberOfRecords, vector<string> names, vector<TypeOfNote> types) {
    rewind(fout);

    // settint number of columns
    fwrite(&numberOfColumns, sizeof(int), 1, fout);

    // settint number of records
    fwrite(&numberOfRecords, sizeof(int), 1, fout);

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

void DATWriter::writeNext(vector<string> recordData) {
    writeNext(recordData, fout);
}

void DATWriter::writeNext(vector<string> recordData, FILE *to) {
    if (numberOfColumns != recordData.size()) {
        return;
    }
    List list;
    for (int i = 0; i < numberOfColumns; ++i) {
        list.put(recordData[i]);
        list.writeInFile(to);
    }
    fflush(to);
}

FILE *DATWriter::getFout() {
    return fout;
}

DATWriter::DATWriter(FILE *fout, int numberOfColumns) {
    this->fout = fout;
    this->numberOfColumns = numberOfColumns;
}

DATWriter::DATWriter(FILE *fout, int numberOfColumns, vector<string> names, vector<TypeOfNote> types) {
    this->fout = fout;
    this->numberOfColumns = numberOfColumns;
    setProperties(0, names, types);
}
