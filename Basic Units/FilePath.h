//
// Created by Mark on 01.03.2021.
//

#ifndef INFORMATION_SYSTEM_FILEPATH_H
#define INFORMATION_SYSTEM_FILEPATH_H

#include <string>

class FilePath {
public:
    string fileName;
    string fileFolder;

    FilePath(string fileName, string fileFolder) {
        this->fileName = fileName;
        this->fileFolder = fileFolder;
    }
};


#endif //INFORMATION_SYSTEM_FILEPATH_H
