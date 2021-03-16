//
// Created by mark on 07.02.21.
//

#include "Table.h"
#include "../CSV Workers/CSVWriter.h"
#include "../DAT Workers/DATWriter.h"
#include "../DAT Workers/DATReader.h"

Table::Table(string tableName) {
    this->tableName = tableName;
    path = folder + tableName + extension;
}

Table::Table(string tableName, vector<string> names, vector<TypeOfNote> types) {
    this->tableName = tableName;
    path = folder + tableName + extension;
    FILE *f = fopen(path.c_str(), "w+b");
    DATWriter datWriter(f, names, types);
}

void Table::get(ostream &fout) {
    //создаём объекты для доступа к файлу
    FILE *f = fopen(path.c_str(), "rb");

    int numberOfRecords;
    vector<string> names;
    vector<TypeOfNote> types;

    DATReader datReader(f);
    datReader.getProperties(numberOfRecords, names, types);
    CSVWriter csvWriter(fout, datReader.getNumberOfColumns());

    //печатаем заголовок
    csvWriter.setProperties(names, types);

    //печатаем сами записи
    for (int i = 0; i < datReader.getNumberOfRecords(); ++i) {
        csvWriter.writeNext(datReader.readNext());
    }
}

void Table::add(vector<string> recordData) {
    //создаём объекты для доступа к файлу
    FILE *f = fopen(path.c_str(), "r+b");

    int numberOfRecords;
    vector<string> names;
    vector<TypeOfNote> types;

    DATReader datReader(f);
    datReader.getProperties(numberOfRecords, names, types);
    DATWriter datWriter(f, datReader.getNumberOfColumns());

    //добавляем запись
    for (int i = 0; i < numberOfRecords; ++i) {
        if (!strcmp(datReader.readNext()[0].c_str(), recordData[0].c_str())) {
            return;
        }
    }
    fseek(datWriter.getFout(), 0, SEEK_END);
    datWriter.writeNext(recordData);

    //печатаем правильный заголовок
    numberOfRecords++;
    datWriter.setProperties(numberOfRecords, names, types);
}

void Table::change(vector<string> recordData) {
    //создаём объекты для доступа к файлу
    string pathTemp = folder + "TEMP";
    FILE *fin = fopen(path.c_str(), "rb");
    FILE *fout = fopen(pathTemp.c_str(), "w+b");

    int numberOfRecords;
    vector<string> names;
    vector<TypeOfNote> types;

    DATReader datReader(fin);
    datReader.getProperties(numberOfRecords, names, types);
    DATWriter datWriter(fout, datReader.getNumberOfColumns());

    //печатаем заголовок
    datWriter.setProperties(numberOfRecords, names, types);

    //печатаем сами записи
    vector<string> currentRecord;
    for (int i = 0; i < datReader.getNumberOfColumns(); ++i) {
        currentRecord = datReader.readNext();
        if (!strcmp(currentRecord[0].c_str(), recordData[0].c_str())) {
            datWriter.writeNext(currentRecord);
        } else {
            datWriter.writeNext(recordData);
        }
    }

    remove(path.c_str());
    rename(pathTemp.c_str(), path.c_str());
}

void Table::deleteItem(string key) {
    //создаём объекты для доступа к файлу
    string pathTemp = folder + "TEMP";
    FILE *fin = fopen(path.c_str(), "rb");
    FILE *fout = fopen(pathTemp.c_str(), "w+b");

    int numberOfRecords;
    vector<string> names;
    vector<TypeOfNote> types;

    DATReader datReader(fin);
    datReader.getProperties(numberOfRecords, names, types);
    DATWriter datWriter(fout, datReader.getNumberOfColumns());

    //печатаем пробный заголовок (если запись удаляем - этот изменим) - чтоз зарезервировать место
    datWriter.setProperties(numberOfRecords, names, types);

    //печатаем сами записи
    vector<string> currentRecord;
    bool isDeleted = false;
    for (int i = 0; i < datReader.getNumberOfColumns(); ++i) {
        currentRecord = datReader.readNext();
        if (!strcmp(currentRecord[0].c_str(), key.c_str())) {
            datWriter.writeNext(currentRecord);
            isDeleted = true;
        }
    }

    if (isDeleted) {
        //печатаем правильный заголовок
        datWriter.setProperties(numberOfRecords - 1, names, types);
    }

    remove(path.c_str());
    rename(pathTemp.c_str(), path.c_str());
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