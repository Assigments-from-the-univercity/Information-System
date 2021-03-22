//
// Created by mark on 07.02.21.
//

#include "Table.h"
#include "../CSV Workers/CSVWriter.h"
#include "../DAT Workers/DATWriter.h"
#include "../DAT Workers/DATReader.h"

Table::Table(string tableName) {
    this->tableName = tableName;
    path = folder + tableName + extension;
}

Table::Table(string tableName, vector<string> names, vector<TypeOfNote> types) {
    this->tableName = tableName;
    path = folder + tableName + extension;
    createTable(tableName, names, types);
}

void Table::createTable(string tableName, vector<string> names, vector<TypeOfNote> types) {
    string path = folder + tableName + extension;
    FILE *f = fopen(path.c_str(), "w+b");
    DATWriter datWriter(f, names, types);
}

void Table::get(ostream &fout) {
    //создаём объекты для доступа к файлу
    FILE *f = fopen(path.c_str(), "rb");

    int numberOfRecords;
    vector<string> names;
    vector<TypeOfNote> types;

    DATReader datReader(f);
    datReader.getProperties(numberOfRecords, names, types);
    CSVWriter csvWriter(fout, datReader.getNumberOfColumns());

    //печатаем заголовок
    csvWriter.setProperties(names, types);

    //печатаем сами записи
    for (int i = 0; i < datReader.getNumberOfRecords(); ++i) {
        csvWriter.writeNext(datReader.readNext());
    }
}

void Table::getProperties(vector<string> &names, vector<TypeOfNote> &types) {
    //создаём объекты для доступа к файлу
    FILE *f = fopen(path.c_str(), "rb");

    int numberOfRecords;
    names.clear();
    types.clear();

    DATReader datReader(f);
    datReader.getProperties(numberOfRecords, names, types);
}

void Table::add(vector<string> recordData) {
    //создаём объекты для доступа к файлу
    FILE *f = fopen(path.c_str(), "r+b");

    int numberOfRecords;
    vector<string> names;
    vector<TypeOfNote> types;

    DATReader datReader(f);
    datReader.getProperties(numberOfRecords, names, types);
    DATWriter datWriter(f, datReader.getNumberOfColumns());

    //добавляем запись
    for (int i = 0; i < numberOfRecords; ++i) {
        if (!strcmp(datReader.readNext()[0].c_str(), recordData[0].c_str())) {
            return;
        }
    }
    fseek(datWriter.getFout(), 0, SEEK_END);
    datWriter.writeNext(recordData);

    //печатаем правильный заголовок
    numberOfRecords++;
    datWriter.setProperties(numberOfRecords, names, types);
}

void Table::change(vector<string> recordData) {
    //создаём объекты для доступа к файлу
    string pathTemp = folder + "TEMP.dat";
    FILE *fin = fopen(path.c_str(), "rb");
    FILE *fout = fopen(pathTemp.c_str(), "w+b");

    int numberOfRecords;
    vector<string> names;
    vector<TypeOfNote> types;

    DATReader datReader(fin);
    datReader.getProperties(numberOfRecords, names, types);
    DATWriter datWriter(fout, datReader.getNumberOfColumns());

    //печатаем заголовок
    datWriter.setProperties(numberOfRecords, names, types);

    //печатаем сами записи
    vector<string> currentRecord;
    for (int i = 0; i < numberOfRecords; ++i) {
        currentRecord = datReader.readNext();
        if (strcmp(currentRecord[0].c_str(), recordData[0].c_str())) {
            datWriter.writeNext(currentRecord);
        } else {
            datWriter.writeNext(recordData);
        }
    }

    fclose(fin);
    fclose(fout);

    copy("TEMP", tableName);
    remove(pathTemp.c_str());
}

void Table::deleteItem(string key) {
    //создаём объекты для доступа к файлу
    string pathTemp = folder + "TEMP.dat";
    FILE *fin = fopen(path.c_str(), "rb");
    FILE *fout = fopen(pathTemp.c_str(), "w+b");

    int numberOfRecords;
    vector<string> names;
    vector<TypeOfNote> types;

    DATReader datReader(fin);
    datReader.getProperties(numberOfRecords, names, types);
    DATWriter datWriter(fout, datReader.getNumberOfColumns());

    //печатаем пробный заголовок (если запись удаляем - этот изменим) - чтоз зарезервировать место
    datWriter.setProperties(numberOfRecords, names, types);

    //печатаем сами записи
    vector<string> currentRecord;
    bool isDeleted = false;
    for (int i = 0; i < numberOfRecords; ++i) {
        currentRecord = datReader.readNext();
        if (strcmp(currentRecord[0].c_str(), key.c_str())) {
            datWriter.writeNext(currentRecord);
        } else {
            //datWriter.writeNext(currentRecord);
            isDeleted = true;
        }
    }

    if (isDeleted) {
        //печатаем правильный заголовок
        datWriter.setProperties(numberOfRecords - 1, names, types);

        fclose(fin);
        fclose(fout);

        copy("TEMP", tableName);
        remove(pathTemp.c_str());
    }
    /*remove(path.c_str());
    rename(pathTemp.c_str(), path.c_str());*/
}

void Table::copy(string fromFileName, string toFileName) {
    //создаём объекты для доступа к файлу
    string pathFrom = folder + fromFileName + extension;
    string pathTo = folder + toFileName + extension;
    FILE *fin = fopen(pathFrom.c_str(), "rb");
    FILE *fout = fopen(pathTo.c_str(), "wb");

    int numberOfRecords;
    vector<string> names;
    vector<TypeOfNote> types;

    DATReader datReader(fin);
    datReader.getProperties(numberOfRecords, names, types);
    DATWriter datWriter(fout, datReader.getNumberOfColumns());

    //печатаем заголовок
    datWriter.setProperties(numberOfRecords, names, types);

    for (int i = 0; i < numberOfRecords; ++i) {
        datWriter.writeNext(datReader.readNext());
    }

    fclose(fin);
    fclose(fout);
}
