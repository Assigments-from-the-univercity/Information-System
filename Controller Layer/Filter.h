//
// Created by Mark on 01.03.2021.
//

#ifndef INFORMATION_SYSTEM_FILTER_H
#define INFORMATION_SYSTEM_FILTER_H


#include "../CSV Workers/CSVWorker.h"
#include "../Basic Units/TypeOfNote.h"

class Filter : CSVWorker {
private:
    int numberOfColumns;
    vector<TypeOfNote> types;

    bool isAppropriate();
public:
    Filter();
};


#endif //INFORMATION_SYSTEM_FILTER_H
