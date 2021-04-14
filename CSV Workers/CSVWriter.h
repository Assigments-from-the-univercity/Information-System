//
// Created by Mark on 11.03.2021.
//

#ifndef INFORMATION_SYSTEM_CSVWRITER_H
#define INFORMATION_SYSTEM_CSVWRITER_H


#include <istream>
#include <vector>
#include "../Basic Units/TypeOfNote.h"

class CSVWriter {
private:
    ostream &fout;
    int numberOfColumns;

public:
    CSVWriter(ostream &fout, int numberOfColumns);

    void setProperties(vector<string> names, vector<TypeOfNote> types);

    void writeNext(vector<string> recordData);

    ostream &getFout();

    void writeNext(vector<string> recordData, ostream &to);
};


#endif //INFORMATION_SYSTEM_CSVWRITER_H
