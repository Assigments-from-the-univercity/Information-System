//
// Created by Mark on 23.02.2021.
//

#include "TypeOfNote.h"

string TypeOfNote::getType(int order) {
    return names[order];
}

string TypeOfNote::getType() {
    if (type == TypeOfNote::DOUBLE) {
        return "DOUBLE";
    } else if (type == TypeOfNote::STRING) {
        return "STRING";
    }
    return "";
}

void TypeOfNote::setType(string name) {
    if (!name.compare("DOUBLE")) {
        type = TypeOfNote::DOUBLE;
    } else if (!name.compare("STRING")) {
        type = TypeOfNote::STRING;
    }
}

void TypeOfNote::writeInFile(FILE *fp) {
    fwrite(&type, sizeof(TypeOfNote), 1, fp);
}

void TypeOfNote::readFromFile(FILE *fp) {
    fread(&type, sizeof(TypeOfNote), 1, fp);
}