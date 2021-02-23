//
// Created by Mark on 23.02.2021.
//

#ifndef INFORMATION_SYSTEM_TYPEOFNOTE_H
#define INFORMATION_SYSTEM_TYPEOFNOTE_H

#include "Header.h"

class TypeOfNote {
public:
    enum {
        DOUBLE,
        STRING
    } type;

    string getType(int order);
};


#endif //INFORMATION_SYSTEM_TYPEOFNOTE_H
