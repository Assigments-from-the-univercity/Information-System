//
// Created by Mark on 26.02.2021.
//

#include "TableDataWorker.h"

TableDataWorker::TableDataWorker(string fileName, int numberOfRecords, int numberOfColumns,
                                 vector<TypeOfNote> types)
                                 : FileWorker(fileName, TABLES_FOLDER) {
    this->numberOfRecords = numberOfRecords;
    this->numberOfColumns = numberOfColumns;
    this->types = types;
}

std::ofstream* TableDataWorker::get(vector<FilterRequest> request) {
    vector<string> recordData;
    ofstream fout("Data/query.csv");

    for (int i = 0; i < numberOfRecords; ++i) {
        recordData = readNextRecord(getFp());
        if (isAppropriate(recordData, request)) {
            writeNextRecordInCSV(recordData, fout);
        }
    }

    return &fout;
}

void TableDataWorker::add(vector<string> recordData) {
    openForReading();
    writeNextRecord(recordData, getFp());
    numberOfRecords++;
}

void TableDataWorker::change(vector<string> recordData) {
    openForWriting();
    FILE *fpOfCopy = fopen(TEMP_FILE_NAME.c_str(), "w+b");
    vector<string> temporaryRecordData;

    for (int i = 0; i < numberOfRecords; ++i) {
        temporaryRecordData = readNextRecord(getFp());
        if (temporaryRecordData[0] == recordData[0]) {
            writeNextRecord(recordData, fpOfCopy);
        } else {
            writeNextRecord(temporaryRecordData, fpOfCopy);
        }
    }

    deleteTableFile();
    renameTempFile();
    openForReading();
}

void TableDataWorker::deleteItem(string key) {
    openForWriting();
    FILE *fpOfCopy = fopen(TEMP_FILE_NAME.c_str(), "w+b");
    vector<string> temporaryRecordData;

    for (int i = 0; i < numberOfRecords; ++i) {
        temporaryRecordData = readNextRecord(getFp());
        if (temporaryRecordData[0] != key) {
            writeNextRecord(temporaryRecordData, fpOfCopy);
        }
    }

    deleteTableFile();
    renameTempFile();
    openForReading();

    numberOfRecords--;
}

void TableDataWorker::deleteTableFile() {
    string oldFile = "Data/Tables/" + getName() + ".dat";
    remove(oldFile.c_str());
}

void TableDataWorker::renameTempFile() {
    string originalName = "Data/Tables/" + getName() + ".dat";
    rename(TEMP_FILE_NAME.c_str(), originalName.c_str());
}

vector<string> TableDataWorker::readNextRecord(FILE *fp) {
    List list;
    vector<string> recordData;

    for (int i = 0; i < numberOfColumns; ++i) {
        list.readFromFile(fp);
        recordData.push_back(list.get());
    }

    return recordData;
}

void TableDataWorker::writeNextRecord(vector<string> recordData, FILE *fp) {
    List list;

    for (int i = 0; i < numberOfColumns; ++i) {
        list.put(recordData[i]);
        list.writeInFile(fp);
    }
}

void TableDataWorker::writeNextRecordInCSV(vector<string> recordData, ofstream &fout) {
    for (int i = 0; i < numberOfColumns; ++i) {
        fout << recordData[i] << ';';
    }
    fout << endl;
}

bool TableDataWorker::isAppropriate(vector<string> recordData, vector<FilterRequest> request) {
    bool validNote = true;

    for (int i = 0; i < numberOfColumns && validNote == true; ++i) {
        if (request[i].state != FilterRequest::IGNORE_IT) {
            if (types[i].type == TypeOfNote::DOUBLE) {
                double value = stod(recordData[i]), target = stod(request[i].value);
                switch (request[i].state) {
                    case FilterRequest::State::LESS:
                        if (value > target) {
                            validNote = false;
                        }
                        break;
                    case FilterRequest::State::MORE:
                        if (value < target) {
                            validNote = false;
                        }
                        break;
                    case FilterRequest::State::NOT_MORE:
                        if (value >= target) {
                            validNote = false;
                        }
                        break;
                    case FilterRequest::State::NOT_LESS:
                        if (value <= target) {
                            validNote = false;
                        }
                        break;
                    case FilterRequest::State::EQUAL:
                        if (value != target) {
                            validNote = false;
                        }
                        break;
                    default:
                        validNote = false;
                }
            }
            else if (types[i].type == TypeOfNote::STRING) {
                string value = recordData[i], target = request[i].value;
                switch (request[i].state) {
                    case FilterRequest::State::EQUAL:
                        if (value.compare(target) != 0) {
                            validNote = false;
                        }
                        break;
                    case FilterRequest::State::INCLUDED:
                        if (!value.find(target)) {
                            validNote = false;

                        }
                        break;
                    default:
                        validNote = false;
                }
            }
        }
    }

    return validNote;
}