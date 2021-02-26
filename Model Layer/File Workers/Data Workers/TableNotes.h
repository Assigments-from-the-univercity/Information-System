//
// Created by Mark on 26.02.2021.
//

#ifndef INFORMATION_SYSTEM_TABLENOTES_H
#define INFORMATION_SYSTEM_TABLENOTES_H


#include "TableDataWorker.h"

class TableNotes : TableDataWorker {
public:
    TableNotes(List name, List folder, int NumberOfRecords, int NumberOfColumns,
               vector<TypeOfNote> types, vector<List> names);

    vector<vector<string>> getNext();

    void add(vector<string> recordsData);

    void change(vector<string> recordsData);

    void deleteItem(string key);
};


#endif //INFORMATION_SYSTEM_TABLENOTES_H
