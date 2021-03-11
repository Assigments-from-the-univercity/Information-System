//
// Created by Mark on 11.03.2021.
//

#ifndef INFORMATION_SYSTEM_FILEREADER_H
#define INFORMATION_SYSTEM_FILEREADER_H

#include <istream>
#include <vector>
#include "../Basic Units/TypeOfNote.h"

using namespace std;

class FileReader {
private:
    istream &fin;

public:
    FileReader(istream &fin);

    void getProperties(int &numberOfRecords, vector<string> &names,
                       vector<TypeOfNote> &types);

    vector<string> readNext();

    int numberOfColumns;

    istream &getFin();

    vector<string> readNext(istream &from);

    void rewindToVeryBeginning();

    void rewind();
};


#endif //INFORMATION_SYSTEM_FILEREADER_H
