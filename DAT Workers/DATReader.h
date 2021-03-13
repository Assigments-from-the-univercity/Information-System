//
// Created by Mark on 13.03.2021.
//

#ifndef INFORMATION_SYSTEM_DATREADER_H
#define INFORMATION_SYSTEM_DATREADER_H

#include <cstdio>
#include "../Basic Units/TypeOfNote.h"

using namespace std;

class DATReader {
private:
    FILE *fin;
    int numberOfColumns;

protected:
    int numberOfRecords;

    void getProperties(int &numberOfRecords, vector<string> &names,
                       vector<TypeOfNote> &types);

    vector<string> readNext();

    FILE *getFin();

    vector<string> readNext(FILE *from);

public:
    DATReader(FILE *fin);
};


#endif //INFORMATION_SYSTEM_DATREADER_H
