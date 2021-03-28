//
// Created by Mark on 28.03.2021.
//

#include "UserRequest.h"

vector<FilterRequest> UserRequest::makeRequest(vector<UserRequest> userRequest, vector<string> names) {

    vector<FilterRequest> request;

    FilterRequest mRequest;
    for (int i = 0; i < names.size(); ++i) {
        mRequest.value = "0";
        mRequest.state = FilterRequest::State::IGNORE_IT;

        for (int j = 0; j < userRequest.size(); ++j) {
            if (userRequest[j].name == names[i]) {
                mRequest.value = userRequest[j].value;
                mRequest.state = getState(userRequest[j]);
            }
        }

        request.push_back(mRequest);
    }

    return request;
}

FilterRequest::State UserRequest::getState(UserRequest userRequest) {
    if (userRequest.oper == "<") {
        return FilterRequest::LESS;
    } else if (userRequest.oper == ">") {
        return FilterRequest::MORE;
    } else if (userRequest.oper == "<=") {
        return FilterRequest::NOT_MORE;
    } else if (userRequest.oper == ">=") {
        return FilterRequest::NOT_LESS;
    } else if (userRequest.oper == "=") {
        return FilterRequest::EQUAL;
    } else if (userRequest.oper == "in") {
        return FilterRequest::INCLUDED;
    } else {
        return FilterRequest::IGNORE_IT;
    }
}
