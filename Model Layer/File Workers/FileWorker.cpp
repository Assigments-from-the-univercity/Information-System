//
// Created by Mark on 23.02.2021.
//

#include "../../Header.h"
#include "FileWorker.h"

FileWorker::FileWorker(string fileName, string fileFolder) {
    tableProperties.name.put(fileName);
    tableProperties.folder.put(fileFolder);
    openForReading();
    if (fp == NULL){
        cout << "file " + fileName + " (in folder " + fileFolder + ") is not exist." << endl;
        openForWriting();
    }
}

void FileWorker::openForReading() {
    string filePath = tableProperties.folder.get() + '/' + tableProperties.name.get();
    fp = fopen(filePath.c_str(), REGIME_WRITEBLE.c_str());
}

void FileWorker::openForWriting() {
    string filePath = tableProperties.folder.get() + '/' + tableProperties.name.get();
    fp = fopen(filePath.c_str(), REGIME_WRITEBLE.c_str());
}