//
// Created by Mark on 01.03.2021.
//

#include "FileWorker.h"

FileWorker::FileWorker(istream &fin, ostream &fout) : FileReader(fin), FileWriter(fout, FileReader::numberOfColumns) {
    //this->numberOfColumns = numberOfColumns;
}

void FileWorker::copyAll(int numberOfRecords, istream &from, ostream &to) {
    from.seekg(from.beg);
    for (int i = 0; i < numberOfRecords; ++i) {
        writeNext(readNext(from), to);
    }
}

void FileWorker::copyFromCurrentPosition(int numberOfRecords, istream &from, ostream &to) {
    for (int i = 0; i < numberOfRecords; ++i) {
        writeNext(readNext(from), to);
    }
}

void FileWorker::createFileIfNotExist(string fileName) {
    ofstream f1(fileName);
    f1.close();
}

void FileWorker::clearFile(string fileName) {
    remove(fileName.c_str());
    createFileIfNotExist(fileName);
}

void FileWorker::rewind(fstream &f) {
    f.seekp(f.beg);
}