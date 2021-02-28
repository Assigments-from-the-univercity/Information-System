//
// Created by Mark on 26.02.2021.
//

#include "TableDataWorker.h"

TableDataWorker::TableDataWorker(string fileName, int numberOfRecords, int numberOfColumns,
                                 vector<TypeOfNote> types)
                                 : FileWorker(fileName, TABLES_FOLDER) {
    this->numberOfRecords = numberOfRecords;
    this->numberOfColumns = numberOfColumns;
    this->types = types;
}
