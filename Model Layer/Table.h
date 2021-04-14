//
// Created by mark on 07.02.21.
//

#ifndef INFORMATION_SYSTEM_TABLE_H
#define INFORMATION_SYSTEM_TABLE_H


#include <ostream>
#include <vector>
#include <iostream>
#include <cstring>
#include "../Basic Units/TypeOfNote.h"
#include "../CSV Workers/CSVWriter.h"
#include "../DAT Workers/DATWriter.h"
#include "../DAT Workers/DATReader.h"

/**
 * This class represent (a part of) the model layer.
 * This class works with <sheetName>.dat and <sheetName>-prop.dat - files,
 * that have tables data and table properties.
 *
 * Template of <sheetName>-prop.dat :
 *  numberOfNotes (int)
 *  numberOfProperties (int)
 *  values (vector<TypeOfNote>)
 *
 * Template of <sheetName>.dat :
 *  note1 (TableProperties)
 *  note2 (TableProperties)
 *  note3 (TableProperties)
 *  ...
 *  note_i (TableProperties)
 */

const static string folder = "tables\\";
const static string extension = ".dat";

class Table {
private:
    string tableName;
    string path;

    static void copy(string fromFileName, string toFileName);

public:
    Table(string tableName);

    Table(string tableName, vector<string> names, vector<TypeOfNote> types);

    static void createTable(string tableName, vector<string> names, vector<TypeOfNote> types);

    void get(ostream &fout);

    void getProperties(vector<string> &names, vector<TypeOfNote> &types);

    void add(vector<string> recordData);

    void change(vector<string> recordData);

    void deleteItem(string key);
};


#endif //INFORMATION_SYSTEM_TABLE_H
