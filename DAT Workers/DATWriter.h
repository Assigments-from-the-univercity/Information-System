//
// Created by Mark on 13.03.2021.
//

#ifndef INFORMATION_SYSTEM_DATWRITER_H
#define INFORMATION_SYSTEM_DATWRITER_H


#include <cstdio>
#include <vector>
#include <iostream>
#include "../Basic Units/TypeOfNote.h"
#include "../Basic Units/List/List.h"

using namespace std;

class DATWriter {
private:
    FILE *fout;
    int numberOfColumns;

public:
    DATWriter(FILE *fout, int numberOfColumns);

    DATWriter(FILE *fout, vector<string> names, vector<TypeOfNote> types);

    void setProperties(int numberOfRecords, vector<string> names, vector<TypeOfNote> types);

    void writeNext(vector<string> recordData);

    void writeNext(vector<string> recordData, FILE *to);

    FILE *getFout();
};


#endif //INFORMATION_SYSTEM_DATWRITER_H
