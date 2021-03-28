//
// Created by Mark on 24.03.2021.
//

#ifndef INFORMATION_SYSTEM_PRESORTREQUEST_H
#define INFORMATION_SYSTEM_PRESORTREQUEST_H

#include <string>
#include <vector>
#include "../Basic Units/SortRequest.h"

class PreSortRequest : public SortRequest {
public:
    std::string ColumnName;

    /*enum {
        ASCENDING,
        DESCENDING
    } order;*/

    static vector<SortRequest> makeSortRequest(vector<PreSortRequest> preSortRequest, vector<string> names) {
        vector<SortRequest> sortRequest;

        for (int i = 0; i < preSortRequest.size(); ++i) {
            SortRequest sR;
            sR.order = preSortRequest[i].order;
            sR.ColumnIndex = -1;

            for (int j = 0; j < names.size(); ++j) {
                if (preSortRequest[i].ColumnName == names[j]) {
                    sR.ColumnIndex = j;
                }
            }

            if (sR.ColumnIndex == -1) {
                cout << "error in SORT input";
                abort();
            }
        }

        return sortRequest;
    }
};


#endif //INFORMATION_SYSTEM_PRESORTREQUEST_H
