//
// Created by Mark on 26.02.2021.
//

#ifndef INFORMATION_SYSTEM_TABLEDATAWORKER_H
#define INFORMATION_SYSTEM_TABLEDATAWORKER_H

#include "../../Header.h" //если убрать, то конструктор базового класса не вызываеться. Почему???
#include "FileWorker.h"
#include "../../Basic Units/TypeOfNote.h"
#include "../../Basic Units/Request.h"

class TableDataWorker : public FileWorker {
private:
    const string TEMP_FILE_NAME = "Data/Tables/tempCopy.dat";

    int numberOfColumns;
    vector<TypeOfNote> types;

    void deleteTableFile();

    void renameTempFile();

    vector<string> readNextRecord(FILE *fp);

    void writeNextRecord(vector<string> recordData, FILE *fp);

    void writeNextRecordInCSV(vector<string> recordData, ofstream &fout);

    bool isAppropriate(vector<string> recordData, vector<Request> request);

public:
    TableDataWorker(string fileName, int numberOfRecords, int numberOfColumns,
                    vector<TypeOfNote> types);

    std::ofstream* get(vector<Request> request);

    void add(vector<string> recordsData);

    void change(vector<string> recordsData);

    void deleteItem(string key);
};


#endif //INFORMATION_SYSTEM_TABLEDATAWORKER_H
