//
// Created by Mark on 23.02.2021.
//

#ifndef INFORMATION_SYSTEM_TABLEPROPERTIES_H
#define INFORMATION_SYSTEM_TABLEPROPERTIES_H

#include "Header.h"
#include "List/List.h"
#include "Basic Units/TypeOfNote.h"

class TableProperties {
public:
    List name;
    List folder;
    List description;
    int numberOfRecords = 0;
    int numberOfColumns = 0;
    vector<TypeOfNote> typesOfColumns;
    vector<List> namesOfColumns;

    void safeProperties(FILE *fp);

    void loadProperties(FILE *fp);
};


#endif //INFORMATION_SYSTEM_TABLEPROPERTIES_H
