//
// Created by mark on 07.02.21.
//

#include "Manifest.h"

void Manifest::safeState() {
    openForWriting();
    tableProperties.numberOfRecords = tables.size();
    fwrite(&tableProperties.numberOfRecords, INT_SIZE, 1, fp);
    for (int i = 0; i < tableProperties.numberOfRecords; ++i) {
        fwrite(&tables[i], sizeof(TableProperties), 1, fp);
    }
    fflush(fp);
}

void Manifest::loadState() {
    openForReading();
    fread(&tableProperties.numberOfRecords, INT_SIZE, 1, fp);
    TableProperties table;
    tables.clear();
    for (int i = 0; i < size; ++i) {
        fread(&table, sizeof(TableProperties), 1, fp);
        tables.push_back(table);
    }
}

Manifest::Manifest() : FileWorker("manifest.dat", "") {

}

vector<TableProperties> Manifest::getTables() {
    return tables;
}

void Manifest::printTables() {
    int size = tables.size();
    cout << "The list of available tables:" << endl;
    for (int i = 0; i < size; i++) {
        cout << "Name: " << tables[i].name << "\nDescription: " << tables[i].description << endl << endl;
    }
    if (size == 0) {
        cout << "There are no available tables" << endl;
    }
    cout << "hint: use \"cd <name of table>\" to go to the table." << endl;
}

void Manifest::addTable(TableProperties tableProperties) {
    tables.push_back(tableProperties);

    safeState();
    loadState();
    createNewFiles(tableProperties.name);
}