//
// Created by Mark on 23.02.2021.
//

#ifndef INFORMATION_SYSTEM_FILEWORKER_H
#define INFORMATION_SYSTEM_FILEWORKER_H

#include "../../Basic Units/List.h"

class FileWorker {
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

    /*void virtual safeState();

    void virtual loadState();*/

public:
    FileWorker(string fileName, string fileFolder);
};


#endif //INFORMATION_SYSTEM_FILEWORKER_H
