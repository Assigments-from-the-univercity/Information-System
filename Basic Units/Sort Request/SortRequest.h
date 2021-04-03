//
// Created by Mark on 11.03.2021.
//

#ifndef INFORMATION_SYSTEM_SORTREQUEST_H
#define INFORMATION_SYSTEM_SORTREQUEST_H


class SortRequest {
public:
    int ColumnIndex;

    enum {
        ASCENDING,
        DESCENDING
    } order;
};


#endif //INFORMATION_SYSTEM_SORTREQUEST_H
