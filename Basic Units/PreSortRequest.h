//
// Created by Mark on 28.03.2021.
//

#ifndef INFORMATION_SYSTEM_PRESORTREQUEST_H
#define INFORMATION_SYSTEM_PRESORTREQUEST_H

#include <string>
#include <vector>
#include "../Basic Units/SortRequest.h"

using namespace std;

class PreSortRequest : public SortRequest {
public:
    std::string ColumnName;

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

            sortRequest.push_back(sR);
        }

        return sortRequest;
    }
};


#endif //INFORMATION_SYSTEM_PRESORTREQUEST_H
