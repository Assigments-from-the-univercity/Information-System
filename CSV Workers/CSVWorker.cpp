//
// Created by Mark on 01.03.2021.
//

#include "CSVWorker.h"

CSVWorker::CSVWorker(istream &fin, ostream &fout) : CSVReader(fin), CSVWriter(fout, CSVReader::numberOfColumns) {
    //this->numberOfColumns = numberOfColumns;
}

void CSVWorker::copyAll(int numberOfRecords, istream &from, ostream &to) {
    from.seekg(from.beg);
    for (int i = 0; i < numberOfRecords; ++i) {
        writeNext(readNext(from), to);
    }
}

void CSVWorker::copyFromCurrentPosition(int numberOfRecords, istream &from, ostream &to) {
    for (int i = 0; i < numberOfRecords; ++i) {
        writeNext(readNext(from), to);
    }
}

void CSVWorker::createFileIfNotExist(string fileName) {
    ofstream f1(fileName);
    f1.close();
}

void CSVWorker::clearFile(string fileName) {
    remove(fileName.c_str());
    createFileIfNotExist(fileName);
}

void CSVWorker::rewind(fstream &f) {
    f.seekp(f.beg);
}