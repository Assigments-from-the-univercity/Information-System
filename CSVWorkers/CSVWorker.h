//
// Created by Mark on 01.03.2021.
//

#ifndef INFORMATION_SYSTEM_CSVWORKER_H
#define INFORMATION_SYSTEM_CSVWORKER_H

#include <fstream>
#include <vector>
#include "CSVReader.h"
#include "CSVWriter.h"

using namespace std;

class CSVWorker : public CSVReader, public CSVWriter {
protected:
    void copyAll(int numberOfRecords, istream &from, ostream &to);

    void copyFromCurrentPosition(int numberOfRecords, istream &from, ostream &to);

    void createFileIfNotExist(string fileName);

    void clearFile(string fileName);

    void rewind(fstream &f);

public:
    CSVWorker(istream &fin, ostream &fout);
};


#endif //INFORMATION_SYSTEM_CSVWORKER_H
