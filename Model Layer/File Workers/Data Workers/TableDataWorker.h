//
// Created by Mark on 26.02.2021.
//

#ifndef INFORMATION_SYSTEM_TABLEDATAWORKER_H
#define INFORMATION_SYSTEM_TABLEDATAWORKER_H


#include "../FileWorker.h"
#include "../../../Basic Units/TypeOfNote.h"

class TableDataWorker : FileWorker {
protected:
    int numberOfColumns;
    vector<TypeOfNote> types;
    vector<List> names;

public:
    void virtual add(vector<string> recordsData){}

    void virtual change(vector<string> recordsData){}

    void virtual deleteItem(string key){}
};


#endif //INFORMATION_SYSTEM_TABLEDATAWORKER_H
