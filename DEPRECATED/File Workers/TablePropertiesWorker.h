//
// Created by Mark on 23.02.2021.
//

#ifndef INFORMATION_SYSTEM_TABLEPROPERTIESWORKER_H
#define INFORMATION_SYSTEM_TABLEPROPERTIESWORKER_H

#include "FileWorker.h"
#include "../../Basic Units/TypeOfNote.h"

class TablePropertiesWorker : public FileWorker {
private:
    int numberOfColumns;
    vector<TypeOfNote> types;
    vector<List> names;

    void safeState();

    void loadState();

public:
    TablePropertiesWorker(string fileName);

    void setProperties(int numberOfRecords, int numberOfColumns, vector<TypeOfNote> types, vector<List> names);

    void getProperties(int &numberOfRecords, int &numberOfColumns, vector<TypeOfNote> &types, vector<List> &names);
};


#endif //INFORMATION_SYSTEM_TABLEPROPERTIESWORKER_H
