//
// Created by Mark on 13.03.2021.
//

#ifndef INFORMATION_SYSTEM_DATREADER_H
#define INFORMATION_SYSTEM_DATREADER_H

#include <cstdio>
#include <vector>
#include "../Basic Units/TypeOfNote.h"
#include "../Basic Units/List/List.h"

using namespace std;

class DATReader {
private:
    FILE *fin;
    int numberOfColumns;
    int numberOfRecords;

public:
    DATReader(FILE *fin);

    void getProperties(int &numberOfRecords, vector<string> &names,
                       vector<TypeOfNote> &types);

    vector<string> readNext();

    FILE *getFin();

    vector<string> readNext(FILE *from);

    int getNumberOfColumns();

    int getNumberOfRecords();
};


#endif //INFORMATION_SYSTEM_DATREADER_H
