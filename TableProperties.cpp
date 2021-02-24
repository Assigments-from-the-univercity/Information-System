//
// Created by Mark on 23.02.2021.
//

#include "Header.h"
#include "TableProperties.h"

void TableProperties::safeProperties(FILE *fp){
    rewind(fp);
    name.writeInFile(fp);
    description.writeInFile(fp);
    fwrite(&numberOfRecords, INT_SIZE, 1, fp);
    fwrite(&numberOfColumns, INT_SIZE, 1, fp);
    for (int i = 0; i < numberOfColumns; ++i) {
        typesOfColumns[i].writeInFile(fp);
        namesOfColumns[i].writeInFile(fp);
    }
}

void TableProperties::loadProperties(FILE *fp){
    rewind(fp);
    name.readFromFile(fp);
    description.readFromFile(fp);
    fread(&numberOfRecords, INT_SIZE, 1, fp);
    fread(&numberOfColumns, INT_SIZE, 1, fp);
    for (int i = 0; i < numberOfColumns; ++i) {
        typesOfColumns[i].readFromFile(fp);
        namesOfColumns[i].readFromFile(fp);
    }
}