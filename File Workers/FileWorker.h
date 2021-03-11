//
// Created by Mark on 01.03.2021.
//

#ifndef INFORMATION_SYSTEM_FILEWORKER_H
#define INFORMATION_SYSTEM_FILEWORKER_H

#include <fstream>
#include <vector>
#include "FileReader.h"
#include "FileWriter.h"

using namespace std;

class FileWorker : public FileReader, public FileWriter {
public:
    FileWorker(istream &fin, ostream &fout);

    void copyAll(int numberOfRecords, istream &from, ostream &to);

    void copyFromCurrentPosition(int numberOfRecords, istream &from, ostream &to);

    void createFileIfNotExist(string fileName);

    void clearFile(string fileName);

    void rewind(fstream &f);
};


#endif //INFORMATION_SYSTEM_FILEWORKER_H
