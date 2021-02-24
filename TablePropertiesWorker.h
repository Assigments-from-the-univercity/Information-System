//
// Created by Mark on 23.02.2021.
//

#ifndef INFORMATION_SYSTEM_TABLEPROPERTIESWORKER_H
#define INFORMATION_SYSTEM_TABLEPROPERTIESWORKER_H

#include "FileWorker.h"

class TablePropertiesWorker : public FileWorker {
public:
    TablePropertiesWorker(string fileName) : FileWorker(fileName) {
        tableProperties.loadProperties(fp);
    }

    void setProperties(TableProperties tableProperties);

    TableProperties getProperties();

    ~TablePropertiesWorker();
};


#endif //INFORMATION_SYSTEM_TABLEPROPERTIESWORKER_H
