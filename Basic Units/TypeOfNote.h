//
// Created by Mark on 23.02.2021.
//

#ifndef INFORMATION_SYSTEM_TYPEOFNOTE_H
#define INFORMATION_SYSTEM_TYPEOFNOTE_H

#include "../Header.h"

class TypeOfNote {
private:
    string names[2] = {"DOUBLE", "STRING"};
public:
    enum {
        DOUBLE,
        STRING
    } type;

    string getType(int order);

    string getType();

    void setType(string name);

    void writeInFile(FILE *fp);

    void readFromFile(FILE *fp);
};


#endif //INFORMATION_SYSTEM_TYPEOFNOTE_H
