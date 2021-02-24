//
// Created by mark on 07.02.21.
//

#include "Manifest.h"

void Manifest::safeState() {
    // I will use namesOfTables for standard
    openForWriting();
    //numberOfRecords = namesOfTables.size();
    fwrite(&numberOfRecords, INT_SIZE, 1, getFp());
    for (int i = 0; i < numberOfRecords; ++i) {
        fwrite(&namesOfTables[i], sizeof(List), 1, getFp());
        fwrite(&descriptionsOfTables[i], sizeof(List), 1, getFp());
    }
    fflush(getFp());
}

void Manifest::loadState() {
    openForReading();
    fread(&numberOfRecords, INT_SIZE, 1, getFp());
    List list;
    for (int i = 0; i < numberOfRecords; ++i) {
        fwrite(&list, sizeof(List), 1, getFp());
        namesOfTables.push_back(list);
        fwrite(&list, sizeof(List), 1, getFp());
        descriptionsOfTables.push_back(list);
    }
}

Manifest::Manifest() : FileWorker(MANIFEST_NAME, MANIFEST_FOLDER) {
    loadState();
}

vector<string> Manifest::getTables() {
    vector<string> tablesNames;
    for (int i = 0; i < numberOfRecords; ++i) {
        tablesNames.push_back(namesOfTables[i].get());
    }
    return tablesNames;
}

void Manifest::addTable(string fileName, string fileProperties) {
    List list;

    list.put(fileName);
    namesOfTables.push_back(list);
    list.put(fileProperties);
    descriptionsOfTables.push_back(list);

    numberOfRecords++;

    safeState();
}