//
// Created by Mark on 23.02.2021.
//

#ifndef INFORMATION_SYSTEM_LIST_H
#define INFORMATION_SYSTEM_LIST_H

#include "Node.h"

class List {
private:
    Node begin;

    void add(char value);

public:
    List();

    List(char value);

    string get();

    void put(string record);

    int size();

    int numberOfElements();

    void copy(List list);

    bool isInList(char value);

    bool isEqual(List list);

    bool isContains(List list);//TODO this method

    void change(int order, char newValue);

    void del(int order);
};


#endif //INFORMATION_SYSTEM_LIST_H
