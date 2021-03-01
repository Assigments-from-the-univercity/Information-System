//
// Created by Mark on 26.02.2021.
//

#ifndef INFORMATION_SYSTEM_TABLEDATAWORKER_H
#define INFORMATION_SYSTEM_TABLEDATAWORKER_H

#include "../../../Header.h" //если убрать, то конструктор базового класса не вызываеться. Почему???
#include "../FileWorker.h"
#include "../../../Basic Units/TypeOfNote.h"
#include "../../../Basic Units/Request.h"

class TableDataWorker : public FileWorker {
protected:
    int numberOfColumns;
    vector<TypeOfNote> types;

public:
    TableDataWorker(string fileName, int numberOfRecords, int numberOfColumns,
                    vector<TypeOfNote> types);

    virtual FILE* get(vector<Request> request){}

    virtual void add(vector<string> recordsData){}

    virtual void change(vector<string> recordsData){}

    virtual void deleteItem(string key){}
};


#endif //INFORMATION_SYSTEM_TABLEDATAWORKER_H
