//
// Created by Mark on 23.02.2021.
//

#ifndef INFORMATION_SYSTEM_TABLEPROPERTIESWORKER_H
#define INFORMATION_SYSTEM_TABLEPROPERTIESWORKER_H

#include "FileWorker.h"

class TablePropertiesWorker : public FileWorker {
private:
    void safeProperties();

    void loadProperties();

public:
    TablePropertiesWorker(string fileName) : FileWorker(fileName) {
        loadProperties();
    }

    void setProperties(TableProperties tableProperties);

    TableProperties getProperties();

    ~TablePropertiesWorker();
};


#endif //INFORMATION_SYSTEM_TABLEPROPERTIESWORKER_H
