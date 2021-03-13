//
// Created by Mark on 23.02.2021.
//

#include "../../Header.h"
#include "FileWorker.h"

CSVWorker::CSVWorker(string fileName, string fileFolder) {
    name.put(fileName);
    folder.put(fileFolder);
    openForReading();
    if (fp == NULL){
        cout << "file " + fileName + " (in folder " + fileFolder + ") is not exist." << endl;
        openForWriting();
    }
}

void CSVWorker::openForReading() {
    string filePath = folder.get() + name.get();
    fp = fopen(filePath.c_str(), "r+b");
}

void CSVWorker::openForWriting() {
    string filePath = folder.get() + name.get();
    fp = fopen(filePath.c_str(), "w+b");
}

FILE *CSVWorker::getFp() {
    return fp;
}

string CSVWorker::getName() {
    return name.get();
}
