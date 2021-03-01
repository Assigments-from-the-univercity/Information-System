//
// Created by Mark on 01.03.2021.
//

#ifndef INFORMATION_SYSTEM_CSVWORKER_H
#define INFORMATION_SYSTEM_CSVWORKER_H


#include "../Header.h"
#include "../Model Layer/File Workers/FileWorker.h"
#include <fstream>

class CSVWorker {
public:
    CSVWorker(ofstream fout);

    vector<string> getNextRecord();
};


#endif //INFORMATION_SYSTEM_CSVWORKER_H
