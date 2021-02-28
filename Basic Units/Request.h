//
// Created by Mark on 28.02.2021.
//

#ifndef INFORMATION_SYSTEM_REQUEST_H
#define INFORMATION_SYSTEM_REQUEST_H


class Request {
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


#endif //INFORMATION_SYSTEM_REQUEST_H
