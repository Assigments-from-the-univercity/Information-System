//
// Created by Mark on 13.03.2021.
//

#ifndef INFORMATION_SYSTEM_DATWRITER_H
#define INFORMATION_SYSTEM_DATWRITER_H

#include <cstdio>
#include "../Basic Units/TypeOfNote.h"

using namespace std;

class DATWriter {
private:
    FILE *fout;
    int numberOfColumns;

private:
    void setProperties(int numberOfRecords, vector<string> names, vector<TypeOfNote> types);

    void writeNext(vector<string> recordData);

    void writeNext(vector<string> recordData, FILE *to);

    FILE *getFout();

public:
    DATWriter(FILE *fout, int numberOfColumns);

    DATWriter(FILE *fout, int numberOfColumns, vector<string> names, vector<TypeOfNote> types);
};


#endif //INFORMATION_SYSTEM_DATWRITER_H
