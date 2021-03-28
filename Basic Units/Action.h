//
// Created by Mark on 28.03.2021.
//

#ifndef INFORMATION_SYSTEM_ACTION_H
#define INFORMATION_SYSTEM_ACTION_H

#include <string>
#include <iostream>

using namespace std;

class Action {
public:
    enum {
        SELECT,
        FROM,
        WHERE,
        SORT,
        STOP
    } actionType;

    void getAction(string stringAction);
};


#endif //INFORMATION_SYSTEM_ACTION_H
