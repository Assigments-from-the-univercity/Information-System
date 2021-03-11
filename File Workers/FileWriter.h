//
// Created by Mark on 11.03.2021.
//

#ifndef INFORMATION_SYSTEM_FILEWRITER_H
#define INFORMATION_SYSTEM_FILEWRITER_H

#include <istream>
#include <vector>
#include "../Basic Units/TypeOfNote.h"

class FileWriter {
private:
    ostream &fout;
    int numberOfColumns;

public:
    FileWriter(ostream &fout, int numberOfColumns);

    FileWriter(ostream &fout, int numberOfColumns, vector<string> names, vector<TypeOfNote> types); //TODO untested

    void setProperties(vector<string> names, vector<TypeOfNote> types);

    void writeNext(vector<string> recordData);

    ostream &getFout();

    void writeNext(vector<string> recordData, ostream &to);
};


#endif //INFORMATION_SYSTEM_FILEWRITER_H
