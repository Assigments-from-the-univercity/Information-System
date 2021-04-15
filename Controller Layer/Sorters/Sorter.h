//
// Created by Mark on 11.03.2021.
//

#ifndef INFORMATION_SYSTEM_SORTER_H
#define INFORMATION_SYSTEM_SORTER_H


#include <math.h>
#include <string.h>
#include "../../CSV Workers/CSVWorker.h"
#include "../../Basic Units/Sort Request/SortRequest.h"
#include "../../Basic Units/TypeOfNote.h"
#include "Sortable.h"

class Sorter : public Sortable {
private:
    int numberOfRecords;
    vector<string> names;
    vector<SortRequest> sortRequest;
    vector<TypeOfNote> types;

    void sortNextLevel(int level, fstream &buffer);

    void mergeTwoFiles(fstream &set1, int sizeSet1, fstream &set2, int sizeSet2, fstream &buffer);

public:
    Sorter(istream &fin, ostream &fout);

    void sort(vector<SortRequest> sortRequest);
};


#endif //INFORMATION_SYSTEM_SORTER_H
