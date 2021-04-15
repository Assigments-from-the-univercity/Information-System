//
// Created by Mark on 15.04.2021.
//

#ifndef INFORMATION_SYSTEM_SORTABLE_H
#define INFORMATION_SYSTEM_SORTABLE_H

/**
 * This interface is used for sorting records according to @arg vector <SortRequest> sortRequest
 */
class Sortable : public CSVWorker {
public:
    Sortable(istream &fin, ostream &fout) : CSVWorker(fin, fout) {}

    /**
     * This method is sorting records which we gained from @arg fin.
     *
     * @param sortRequest
     */
    void sort(vector <SortRequest> sortRequest) {}

    /**
     * This function is used for comparison two elements.
     *
     * @param firstRecord
     * @param secondRecord
     * @param sortRequest
     * @return true if first is bigger, otherwise returns false
     */
    bool firsIsBigger(vector <string> firstRecord, vector <string> secondRecord, vector <SortRequest> sortRequest,
                      vector <TypeOfNote> types) {
        int requestSize = sortRequest.size();
        for (int i = 0; i < requestSize; ++i) {
            switch (types[sortRequest[i].ColumnIndex].type) {
                case TypeOfNote::STRING: {
                    int compareResult = strcmp(firstRecord[sortRequest[i].ColumnIndex].c_str(),
                                               secondRecord[sortRequest[i].ColumnIndex].c_str());
                    if (compareResult > 0) {
                        if (sortRequest[i].order == SortRequest::ASCENDING) {
                            return true;
                        } else if (sortRequest[i].order == SortRequest::DESCENDING) {
                            return false;
                        }
                    } else if (compareResult < 0) {
                        if (sortRequest[i].order == SortRequest::ASCENDING) {
                            return false;
                        } else if (sortRequest[i].order == SortRequest::DESCENDING) {
                            return true;
                        }
                    }
                }
                    break;

                case TypeOfNote::DOUBLE: {
                    double value1 = stod(firstRecord[sortRequest[i].ColumnIndex]);
                    double value2 = stod(secondRecord[sortRequest[i].ColumnIndex]);
                    if (value1 > value2) {
                        if (sortRequest[i].order == SortRequest::ASCENDING) {
                            return true;
                        } else if (sortRequest[i].order == SortRequest::DESCENDING) {
                            return false;
                        }
                    } else if (value1 < value2) {
                        if (sortRequest[i].order == SortRequest::ASCENDING) {
                            return false;
                        } else if (sortRequest[i].order == SortRequest::DESCENDING) {
                            return true;
                        }
                    }
                }
                    break;
            }
        }

        //если они полностью равны, то первый НЕ БОЛЬШЕ второго
        return false;
    }
};


#endif //INFORMATION_SYSTEM_SORTABLE_H
