//
// Created by Mark on 28.03.2021.
//

#ifndef INFORMATION_SYSTEM_PARSER_H
#define INFORMATION_SYSTEM_PARSER_H

#include <iostream>
#include <string>
#include <vector>
#include "../Basic Units/PreSortRequest.h"
#include "../Basic Units/Action.h"
#include "../Basic Units/UserRequest.h"

using namespace std;

class Parser {
private:
    static vector<PreSortRequest> setPreSorterRequest(Action &action);

    static vector<UserRequest> setFilterRequest(Action &action);

public:
    static void makeRequest(Action action, string &tableName,
                            vector<UserRequest> &userRequest,
                            vector<PreSortRequest> &sortRequest);
};


#endif //INFORMATION_SYSTEM_PARSER_H
