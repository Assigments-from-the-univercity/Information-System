//
// Created by Mark on 23.02.2021.
//

#include "Header.h"
#include "FileWorker.h"

FileWorker::FileWorker(string fileName) {
    string filePath = TABLE_FOLDER + '/' + fileName;
    this->fp = fopen(filePath.c_str(), REGIME_WRITEBLE.c_str());
}

/*FileWorker::FileWorker(TableProperties tableProperties) {
    this->fp = fopen(tableProperties.name.get().c_str(), "w+b");
}*/