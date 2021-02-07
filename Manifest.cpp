//
// Created by mark on 07.02.21.
//

#include "Manifest.h"

void Manifest::createNewFiles(char name[NAME_SIZE]) {
    string stringName(name);
    string folderName = "tables/";
    string propName = "-prop";
    string sourceType = ".dat";

    string newFile = folderName + stringName + sourceType;
    string newPropFile = folderName + stringName + propName + sourceType;

    char fileName[newFile.length() + 1];
    strcpy(fileName, newFile.c_str());

    char propFileName[newPropFile.length() + 1];
    strcpy(propFileName, newPropFile.c_str());

    FILE *fpNew = fopen(fileName, "w+b");
    fpNew = fopen(propFileName, "w+b");
}

void Manifest::refreshManifest() {
    fp = fopen(FILE_NAME, "w+b");
    int size = tables.size();
    fwrite(&size, INT_SIZE, 1, fp);
    for (int i = 0; i < size; ++i) {
        fwrite(&tables[i], sizeof(TableProperties), 1, fp);
    }
    fflush(fp);
    fp = fopen(FILE_NAME, "r+b");
}

void Manifest::updateData() {
    rewind(fp);
    int size = 0;
    fread(&size, INT_SIZE, 1, fp);
    TableProperties table;
    tables.clear();
    for (int i = 0; i < size; ++i) {
        fread(&table, sizeof(TableProperties), 1, fp);
        tables.push_back(table);
    }
}

Manifest::Manifest() {
    fp = fopen(FILE_NAME, "r+b");
    if (fp == NULL) {
        cout << "Файл \"manifest.dat\" створений заново." << endl;

        refreshManifest();

        remove("tables");
        std::filesystem::create_directory("tables");
    }
    updateData();
}

vector<Manifest::TableProperties> Manifest::getTables() {
    return tables;
}

void Manifest::printTables() {
    int size = tables.size();
    cout << "список доступних таблиць:" << endl;
    for (int i = 0; i < size; i++) {
        cout << "Ім'я: " << tables[i].name << "\nОпис: " << tables[i].description << endl << endl;
    }
    if (size == 0) {
        cout << "немає доступних таблиць." << endl;
    }
    cout << "hint: use \"cd <name of table>\" to go to the table." << endl;
}

void Manifest::addTable(TableProperties tableProperties) {
    tables.push_back(tableProperties);

    refreshManifest();
    updateData();
    createNewFiles(tableProperties.name);
}