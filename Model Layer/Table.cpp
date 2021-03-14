//
// Created by mark on 07.02.21.
//

#include "Table.h"
#include "../CSV Workers/CSVWriter.h"
#include "../CSV Workers/CSVWorker.h"

Table::Table(string tableName) {
    f.open(tableName, std::fstream::binary);
}

Table::Table(string tableName, int numberOfColumns, vector <string> names, vector <TypeOfNote> types) {
    f.open(tableName, std::fstream::binary);
    //CSVWriter fileWriter(f, numberOfColumns, names, types);
}

void Table::get(ostream &fout) {
    /*
    //создаём екземпляр для доступа к файлу
    CSVWorker fileWorker(f, fout);

    //данные таблици
    int numberOfRecords;
    vector<string> names;
    vector<TypeOfNote> types;

    //получаем данные таблици
    fileWorker.getProperties(numberOfRecords, names, types);

    //печатаем заголовок
    fileWorker.setProperties(names, types);

    //печатаем сами записи
    fileWorker.copyFromCurrentPosition(numberOfRecords, f, fout);
    */
}

void Table::add(vector <string> recordData) {
    /*
    //создаём екземпляр для доступа к файлу
    CSVWorker fileWorker(f, f);

    //данные таблици
    int numberOfRecords;
    vector<string> names;
    vector<TypeOfNote> types;

    //получаем данные таблици
    fileWorker.getProperties(numberOfRecords, names, types);

    //перематывем указатель в конец и добавляем запись
    fileWorker.getFout().seekp(fileWorker.getFout().end);
    fileWorker.writeNext(recordData);
     */
}

void Table::change(vector <string> recordData) {
    //tableDataWorker->change(recordData);
}

void Table::deleteItem(string key) {
    //tableDataWorker->deleteItem(key);
}

/*
#include <iomanip>
#include <string>

const char *TEMP_FILE = "tables/tempCopy.dat";

void Table::getProperties() {
    properties.values.clear();

    fread(&properties.numberOfNotes, INT_SIZE, 1, fpProp);
    fread(&properties.numberOfProperties, INT_SIZE, 1, fpProp);
    Table::Field field;
    for (int i = 0; i < properties.numberOfProperties; ++i) {
        fread(&field, sizeof(Table::Field), 1, fpProp);
        properties.values.push_back(field);
    }
}

void Table::setProperties() {
    openFpPropForWriting();

    fwrite(&properties.numberOfNotes, INT_SIZE, 1, fpProp);
    fwrite(&properties.numberOfProperties, INT_SIZE, 1, fpProp);
    for (int i = 0; i < properties.numberOfProperties; ++i) {
        fwrite(&properties.values[i], sizeof(Table::Field), 1, fpProp);
    }

    fflush(fpProp);

    openFpPropForReading();
}

void Table::printHeader() {
    printf("%3s ", "id");
    for (int i = 0; i < properties.numberOfProperties; ++i) {
        printf("| %10s ", properties.values[i].name);
    }
    cout << endl;
    cout << "===";
    for (int i = 0; i < properties.numberOfProperties; ++i) {
        cout << "=|===========";
    }
    cout << endl;
}

void Table::printNote(vector<NoteValue> noteProperties, int id) {
    printf("%3d ", id);
    for (int i = 0; i < noteProperties.size(); ++i) {
        printf("| %10s ", noteProperties[i].value);
    }
    cout << endl;
}

void Table::openFpForReading() {
    string stringName(name);
    string folderName = "tables/";
    string sourceType = ".dat";
    string newFile = folderName + stringName + sourceType;

    char fileName[newFile.length() + 1];
    strcpy(fileName, newFile.c_str());

    fp = fopen(fileName, "r+b");
}

void Table::openFpForWriting() {
    string stringName(name);
    string folderName = "tables/";
    string sourceType = ".dat";
    string newFile = folderName + stringName + sourceType;

    char fileName[newFile.length() + 1];
    strcpy(fileName, newFile.c_str());

    fp = fopen(fileName, "w+b");
}

void Table::openFpPropForReading() {
    string stringName(name);
    string folderName = "tables/";
    string propName = "-prop";
    string sourceType = ".dat";

    string newPropFile = folderName + stringName + propName + sourceType;

    char propFileName[newPropFile.length() + 1];
    strcpy(propFileName, newPropFile.c_str());

    fpProp = fopen(propFileName, "r+b");
}

void Table::openFpPropForWriting() {
    string stringName(name);
    string folderName = "tables/";
    string propName = "-prop";
    string sourceType = ".dat";

    string newPropFile = folderName + stringName + propName + sourceType;

    char propFileName[newPropFile.length() + 1];
    strcpy(propFileName, newPropFile.c_str());

    fpProp = fopen(propFileName, "w+b");
}

void Table::writeNoteInFile(vector<NoteValue> noteProperties) {
    for (int i = 0; i < properties.numberOfProperties; ++i) {
        fwrite(&noteProperties[i], sizeof(NoteValue), 1, fp);
    }
    fflush(fp);
}

void Table::writeNoteInFile(vector<NoteValue> noteProperties, FILE *p) {
    for (int i = 0; i < properties.numberOfProperties; ++i) {
        fwrite(&noteProperties[i], sizeof(NoteValue), 1, p);
    }
    fflush(p);
}

vector<Table::NoteValue> Table::readNextNote() {
    vector<NoteValue> result;
    NoteValue value;
    for (int i = 0; i < properties.numberOfProperties; ++i) {
        fread(&value, sizeof(NoteValue), 1, fp);
        result.push_back(value);
    }
    return result;
}

vector<Table::NoteValue> Table::readNextNote(FILE *p) {
    vector<NoteValue> result;
    NoteValue value;
    for (int i = 0; i < properties.numberOfProperties; ++i) {
        fread(&value, sizeof(NoteValue), 1, p);
        result.push_back(value);
    }
    return result;
}

void Table::deleteTableFile() {
    string stringName(name);
    string folderName = "tables/";
    string sourceType = ".dat";
    string newFile = folderName + stringName + sourceType;

    char fileName[newFile.length() + 1];
    strcpy(fileName, newFile.c_str());

    remove(fileName);
}

void Table::renameTempFile() {
    string stringName(name);
    string folderName = "tables/";
    string sourceType = ".dat";
    string newFile = folderName + stringName + sourceType;

    char fileName[newFile.length() + 1];
    strcpy(fileName, newFile.c_str());

    rename(TEMP_FILE, fileName);
}

Table::Table() {}

Table::Table(char name[]) {
    setTable(name);
}

void Table::setTable(char name[]) {
    strcpy(this->name, name);

    openFpForReading();
    openFpPropForReading();

    getProperties();
}

void Table::printNotes(vector<Table::FilterRequest> request) {
    printHeader();

    bool validNote;
    vector<NoteValue> noteProperties;
    rewind(fp);

    for (int i = 0; i < properties.numberOfNotes; ++i) {
        noteProperties = readNextNote();
        validNote = true;
        for (int j = 0; j < properties.numberOfProperties && validNote == true; ++j) {
            if (request[j].state != FilterRequest::State::IGNORE_IT) {
                if (properties.values[j].type == TypeOfNote::DOUBLE) {
                    double value = stod(noteProperties[j].value), target = stod(request[j].value);
                    switch (request[j].state) {
                        case FilterRequest::State::LESS:
                            if (value < target) {
                                break;
                            } else {
                                validNote = false;
                                continue;
                            }
                        case FilterRequest::State::MORE:
                            if (value > target) {
                                break;
                            } else {
                                validNote = false;
                                continue;
                            }
                        case FilterRequest::State::NOT_MORE:
                            if (value <= target) {
                                break;
                            } else {
                                validNote = false;
                                continue;
                            }
                        case FilterRequest::State::NOT_LESS:
                            if (value >= target) {
                                break;
                            } else {
                                validNote = false;
                                continue;
                            }
                        case FilterRequest::State::EQUAL:
                            if (value == target) {
                                break;
                            } else {
                                validNote = false;
                                continue;
                            }
                        default:
                            validNote = false;
                            continue;
                    }
                } else if (properties.values[j].type == TypeOfNote::STRING) {
                    string value = noteProperties[j].value, target = request[j].value;
                    switch (request[j].state) {
                        case FilterRequest::State::EQUAL:
                            if (value.compare(target) == 0) {
                                break;
                            } else {
                                validNote = false;
                                continue;
                            }
                        case FilterRequest::State::INCLUDED:
                            if (value.find(target)) {
                                break;
                            } else {
                                validNote = false;
                                continue;
                            }
                        default:
                            validNote = false;
                            continue;
                    }
                }
            }

        }
        if (validNote == true) {
            printNote(noteProperties, i + 1);
        }
    }
}

void Table::addRecord(vector<NoteValue> noteProperties) {
    writeNoteInFile(noteProperties);
    properties.numberOfNotes++;
    setProperties();
    getProperties();
    cout << "note is added: " << endl;

    printHeader();
    printNote(noteProperties, properties.numberOfNotes);
}

void Table::deleteRecord(int id) {
    FILE *copyOfFp = fopen(TEMP_FILE, "w+b");

    rewind(fp);
    for (int i = 0; i < properties.numberOfNotes; ++i) {
        if (i != id) {
            writeNoteInFile(readNextNote(), copyOfFp);
        } else {
            readNextNote();
        }
    }

    deleteTableFile();
    renameTempFile();
    openFpForReading();

    properties.numberOfNotes--;
    setProperties();
    getProperties();
}

void Table::changeRecord(vector<NoteValue> noteProperties, int id) {
    FILE *copyOfFp = fopen(TEMP_FILE, "w+b");

    rewind(fp);
    for (int i = 0; i < properties.numberOfNotes; ++i) {
        if (i != id) {
            writeNoteInFile(readNextNote(), copyOfFp);
        } else {
            readNextNote();
            writeNoteInFile(noteProperties, copyOfFp);
        }
    }

    deleteTableFile();
    renameTempFile();
    openFpForReading();
}*/