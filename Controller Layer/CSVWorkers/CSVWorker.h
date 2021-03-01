//
// Created by Mark on 01.03.2021.
//

#ifndef INFORMATION_SYSTEM_CSVWORKER_H
#define INFORMATION_SYSTEM_CSVWORKER_H

#include <fstream>
#include <vector>

using namespace std;

class CSVWorker {
protected:
    ofstream fout;

    ofstream* getFout();

    vector<string> readNext();

    vector<string> writeNext();

public:
    CSVWorker();
};


#endif //INFORMATION_SYSTEM_CSVWORKER_H
