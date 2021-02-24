//
// Created by Mark on 23.02.2021.
//

#ifndef INFORMATION_SYSTEM_FILEWORKER_H
#define INFORMATION_SYSTEM_FILEWORKER_H

#include "TableProperties.h"

class FileWorker {
protected:
    TableProperties tableProperties;
    FILE *fp;

public:
    FileWorker(string fleName);

    //FileWorker(TableProperties tableProperties);
};


#endif //INFORMATION_SYSTEM_FILEWORKER_H
