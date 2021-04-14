//
// Created by Mark on 11.03.2021.
//

#ifndef INFORMATION_SYSTEM_CSVREADER_H
#define INFORMATION_SYSTEM_CSVREADER_H


#include <istream>
#include <vector>
#include "../Basic Units/TypeOfNote.h"

using namespace std;

class CSVReader {
private:
    istream &fin;

protected:
    int numberOfColumns;

    istream &getFin();

    vector<string> readNext(istream &from);

    void rewindToVeryBeginning();

    void rewind();

public:
    CSVReader(istream &fin);

    void getProperties(int &numberOfRecords, vector<string> &names,
                       vector<TypeOfNote> &types);

    vector<string> readNext();
};


#endif //INFORMATION_SYSTEM_CSVREADER_H
