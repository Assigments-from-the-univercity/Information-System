//
// Created by Mark on 11.03.2021.
//

#include "FileReader.h"

istream &FileReader::getFin() {
    return fin;
}

vector<string> FileReader::readNext(istream &from) {
    vector<string> recordData;
    string propLine;
    string propData;
    char propChar = 0;

    from >> propLine;
    int sizeOfPropLine = propLine.size();
    for (int i = 0; i < sizeOfPropLine; ++i) {
        propChar = propLine[i];
        if (propChar == ';') {
            recordData.push_back(propData);
            propData = "";
            continue;
        }
        propData += propChar;
    }
    return recordData;
}

vector<string> FileReader::readNext() {
    return readNext(fin);
}

void FileReader::rewindToVeryBeginning() {
    fin.clear();
    fin.seekg(fin.beg);
}

void FileReader::rewind() {
    rewindToVeryBeginning();
    string s;
    fin >> s;
    fin >> s;

}

void FileReader::getProperties(int &numberOfRecords, vector<string> &names, vector<TypeOfNote> &types) {
    // setting column's names
    names = readNext();

    // setting types
    vector<string> s = readNext();
    types.clear();
    TypeOfNote typeOfCurrentNote;
    for (int i = 0; i < numberOfColumns; ++i) {
        typeOfCurrentNote.setType(s[i]);
        types.push_back(typeOfCurrentNote);
    }

    // setting numberOfRecords
    numberOfRecords = 0;
    for (string str; getline(getFin(), str); ++numberOfRecords) {}
    numberOfRecords--;

    rewind();
}

FileReader::FileReader(istream &fin) : fin(fin) {
    rewindToVeryBeginning();

    numberOfColumns = 0;
    string s;
    fin >> s;
    int size = s.size();
    for (int i = 0; i < size; ++i) {
        if (s[i] == ';') {
            numberOfColumns++;
        }
    }
    rewindToVeryBeginning();
}