//
// Created by Mark on 26.02.2021.
//

#ifndef INFORMATION_SYSTEM_TABLENOTES_H
#define INFORMATION_SYSTEM_TABLENOTES_H


#include "TableDataWorker.h"

class TableNotes : TableDataWorker {
private:
    const string TEMP_FILE_NAME = "Data/Tables/tempCopy.dat";

    void deleteTableFile();

    void renameTempFile();

public:
    TableNotes(string name, int numberOfRecords, int numberOfColumns,
               vector<TypeOfNote> types, vector<List> names);

    vector<vector<string>> get();

    void add(vector<string> recordsData);

    void change(vector<string> recordsData);

    void deleteItem(string key);
};


#endif //INFORMATION_SYSTEM_TABLENOTES_H
