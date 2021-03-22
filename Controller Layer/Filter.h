//
// Created by Mark on 01.03.2021.
//

#ifndef INFORMATION_SYSTEM_FILTER_H
#define INFORMATION_SYSTEM_FILTER_H


#include "../CSV Workers/CSVWorker.h"
#include "../Basic Units/TypeOfNote.h"
#include "../Basic Units/FilterRequest.h"

class Filter : CSVWorker {
private:
    int numberOfRecords;
    vector<string> names;
    vector<TypeOfNote> types;
    vector<FilterRequest> request;
    string bufferName = "buffer.csv";
    fstream buffer;

    bool isAppropriate(vector<string> recordData);

public:
    Filter(istream &fin, ostream &fout);

    void filtrate(vector<FilterRequest> request);
};


#endif //INFORMATION_SYSTEM_FILTER_H
