//
// Created by Mark on 28.03.2021.
//

#ifndef INFORMATION_SYSTEM_USERREQUEST_H
#define INFORMATION_SYSTEM_USERREQUEST_H

#include <string>
#include <vector>
#include "../Basic Units/FilterRequest.h"

using namespace std;

class UserRequest {
public:
    string name;
    string oper;
    string value;

    static vector<FilterRequest> makeRequest(vector<UserRequest> userRequest, vector<string> names);

    static FilterRequest::State getState(UserRequest userRequest);
};


#endif //INFORMATION_SYSTEM_USERREQUEST_H
