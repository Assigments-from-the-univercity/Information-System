//
// Created by Mark on 23.02.2021.
//

#ifndef INFORMATION_SYSTEM_CSVWORKER_H
#define INFORMATION_SYSTEM_FILEWORKER_H

#include "../../Basic Units/List.h"

class CSVWorker {
private:
    List name;
    List folder;
    FILE *fp;

protected:
    int numberOfRecords;

    void openForReading();

    void openForWriting();

    FILE *getFp();

    string getName();

public:
    CSVWorker(string fileName, string fileFolder);
};


#endif //INFORMATION_SYSTEM_CSVWORKER_H
