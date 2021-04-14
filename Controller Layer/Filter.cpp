//
// Created by Mark on 01.03.2021.
//

#include "Filter.h"

Filter::Filter(istream &fin, ostream &fout) : CSVWorker(fin, fout) {
    getProperties(numberOfRecords, names, types);
}

void Filter::filtrate(vector<FilterRequest> request) {
    this->request = request;

    getFout().seekp(getFout().beg);
    getFin().seekg(getFin().beg);

    ofstream f1(bufferName);
    f1.close();
    buffer.open(bufferName);

    readNext();
    readNext();

    int numberOfRecordsAfterSort;
    for (int i = 0; i < numberOfRecords; ++i) {
        vector<string> recordData = readNext();
        if (isAppropriate(recordData)) {
            writeNext(recordData, buffer);
            numberOfRecordsAfterSort++;
        }
    }

    setProperties(names, types);
    copyAll(numberOfRecords, buffer, getFout());

    buffer.close();
    remove(bufferName.c_str());
}

bool Filter::isAppropriate(vector<string> recordData) {
    for (int j = 0; j < CSVReader::numberOfColumns; ++j) {
        if (request[j].state != FilterRequest::State::IGNORE_IT) {
            if (types[j].type == TypeOfNote::DOUBLE) {
                double value = stod(recordData[j]), target = stod(request[j].value);
                switch (request[j].state) {
                    case FilterRequest::State::LESS:
                        if (value < target) {
                            break;
                        } else {
                            return false;
                            continue;
                        }
                    case FilterRequest::State::MORE:
                        if (value > target) {
                            break;
                        } else {
                            return false;
                            continue;
                        }
                    case FilterRequest::State::NOT_MORE:
                        if (value <= target) {
                            break;
                        } else {
                            return false;
                            continue;
                        }
                    case FilterRequest::State::NOT_LESS:
                        if (value >= target) {
                            break;
                        } else {
                            return false;
                            continue;
                        }
                    case FilterRequest::State::EQUAL:
                        if (value == target) {
                            break;
                        } else {
                            return false;
                            continue;
                        }
                    default:
                        //TODO unexpected case
                        return false;
                        continue;
                }
            } else if (types[j].type == TypeOfNote::DOUBLE) {
                string value = recordData[j], target = request[j].value;
                switch (request[j].state) {
                    case FilterRequest::State::EQUAL:
                        if (value.compare(target) == 0) {
                            break;
                        } else {
                            return false;
                            continue;
                        }
                    case FilterRequest::State::INCLUDED:
                        if (value.find(target)) {
                            break;
                        } else {
                            return false;
                            continue;
                        }
                    default:
                        //TODO unexpected case
                        return false;
                        continue;
                }
            }
        }
    }
    return true;
}
