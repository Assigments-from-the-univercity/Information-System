//
// Created by Mark on 23.02.2021.
//

#include "../Model Layer/Header.h"
#include "TypeOfNote.h"

string TypeOfNote::getType(int order) {
    return names[order];
}

void TypeOfNote::writeInFile(FILE *fp) {
    fwrite(&type, sizeof(TypeOfNote), 1, fp);
}

void TypeOfNote::readFromFile(FILE *fp) {
    fread(&type, sizeof(TypeOfNote), 1, fp);
}