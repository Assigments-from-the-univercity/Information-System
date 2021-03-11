//
// Created by Mark on 11.03.2021.
//

#ifndef INFORMATION_SYSTEM_SORTER_H
#define INFORMATION_SYSTEM_SORTER_H

#include "../CSVWorkers/CSVWorker.h"
#include "../Basic Units/SortRequest.h"
#include "../Basic Units/TypeOfNote.h"

class Sorter : public CSVWorker {
private:
    int numberOfRecords;
    string bufferName = "buffer.csv";
    string subBufferName = "subBuffer.csv";
    string subFile1 = "set1.csv";
    string subFile2 = "set2.csv";
    fstream buffer;
    vector<string> names;
    vector<SortRequest> sortRequest;
    vector<TypeOfNote> types;

    void sortNextLevel(int level);

    void mergeTwoFiles(fstream &set1, int sizeSet1, fstream &set2, int sizeSet2);

    bool firsIsBigger(vector<string> firstRecord, vector<string> secondRecord);

public:
    Sorter(istream &fin, ostream &fout, vector<SortRequest> sortRequest);

    void sort();
};


#endif //INFORMATION_SYSTEM_SORTER_H
