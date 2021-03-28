//
// Created by Mark on 28.03.2021.
//

#include "Parser.h"

void Parser::makeRequest(Action action, string &tableName, vector<UserRequest> &userRequest,
                         vector<PreSortRequest> &preSortRequest) {
    switch (action.actionType) {
        case Action::SELECT: {
            string s;
            cin >> s;
        }
            break;
        case Action::FROM:
            cin >> tableName;
            break;
        case Action::WHERE:
            userRequest = setFilterRequest(action);
            break;
        case Action::SORT:
            preSortRequest = setPreSorterRequest(action);
            break;
        case Action::STOP:
            return;
        default:
            cout << "wrong input in the last query." << endl;
    }

    makeRequest(action, tableName, userRequest, preSortRequest);
}

vector<PreSortRequest> Parser::setPreSorterRequest(Action &action) {
    vector<PreSortRequest> sortRequest;
    string column, order;

    bool doAction = true;
    do {
        cin >> column;

        if (column != "SELECT" || column != "FROM" || column != "WHERE" || column != "SORT" || column != ";") {
            cin >> order;

            PreSortRequest sR;
            sR.ColumnName = column;
            if (order == "ASC") {
                sR.order = PreSortRequest::ASCENDING;
            } else if (order == "DESC") {
                sR.order = PreSortRequest::DESCENDING;
            } else {
                cout << "error in input";
                abort();
            }

            sortRequest.push_back(sR);
        } else {
            doAction = false;
            action.getAction(column);
        }
    } while (doAction);

    return sortRequest;
}

vector<UserRequest> Parser::setFilterRequest(Action &action) {
    vector<UserRequest> userRequest;
    string name, oper, value;

    bool doAction = true;
    do {
        cin >> name;

        if (name != "SELECT" || name != "FROM" || name != "WHERE" || name != "SORT" || name != ";") {
            cin >> oper >> value;

            UserRequest uR;
            uR.name = name;
            uR.oper = oper;
            uR.value = value;

            userRequest.push_back(uR);
        } else {
            doAction = false;
            action.getAction(name);
        }
    } while (doAction);

    return userRequest;
}