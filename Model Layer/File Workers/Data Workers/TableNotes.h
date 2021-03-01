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

    vector<string> readNextRecord(FILE *fp);

    void writeNextRecord(vector<string> recordData, FILE *fp);

    void writeNextRecordInCSV(vector<string> recordData, ofstream &fout);

    bool isAppropriate(vector<string> recordData, vector<Request> request);

public:
    TableNotes(string name, int numberOfRecords, int numberOfColumns,
               vector<TypeOfNote> types);

    FILE* get(vector<Request> request);

    void add(vector<string> recordData);

    void change(vector<string> recordData);

    void deleteItem(string key);
};


#endif //INFORMATION_SYSTEM_TABLENOTES_H
