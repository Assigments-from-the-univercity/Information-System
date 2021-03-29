//
// Created by Mark on 28.02.2021.
//

#ifndef INFORMATION_SYSTEM_FILTERREQUEST_H
#define INFORMATION_SYSTEM_FILTERREQUEST_H

#include <string>

using namespace std;

class FilterRequest {
public:
    string value;

    enum State {
        LESS,
        MORE,
        NOT_MORE,
        NOT_LESS,
        EQUAL,
        INCLUDED,
        IGNORE_IT
    } state;
};


#endif //INFORMATION_SYSTEM_FILTERREQUEST_H
