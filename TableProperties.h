//
// Created by Mark on 23.02.2021.
//

#ifndef INFORMATION_SYSTEM_TABLEPROPERTIES_H
#define INFORMATION_SYSTEM_TABLEPROPERTIES_H

#include "Header.h"
#include "List.h"
#include "TypeOfNote.h"

class TableProperties {
public:
    List name;
    List description;
    int numberOfRecords;
    int numberOfColumns;
    vector<TypeOfNote> typesOfColumns;
    vector<List> namesOfColumns;
};


#endif //INFORMATION_SYSTEM_TABLEPROPERTIES_H
