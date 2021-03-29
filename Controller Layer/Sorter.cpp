//
// Created by Mark on 11.03.2021.
//

#include "Sorter.h"
#include <math.h>
#include <string.h>

Sorter::Sorter(istream &fin, ostream &fout, vector<SortRequest> sortRequest) : CSVWorker(fin, fout) {
    this->sortRequest = sortRequest;
    getProperties(numberOfRecords, names, types);
}

void Sorter::sort() {
    //creation buffer file
    ofstream f1(bufferName);
    f1.close();
    buffer.open(bufferName);
    copyFromCurrentPosition(numberOfRecords, getFin(), buffer);
    //buffer.close();

    sortNextLevel(0);

    //buffer.open(bufferName);
    getFout().seekp(getFout().beg);
    getFin().seekg(getFin().beg);
    setProperties(names, types);
    copyAll(numberOfRecords, buffer, getFout());

    buffer.close();
    remove(subFile1.c_str());
    remove(subFile2.c_str());
    remove(bufferName.c_str());
    remove(subBufferName.c_str());
}

void Sorter::sortNextLevel(int level) {
    //создаём необходимые для работы программы файлы
    createFileIfNotExist(subFile1);
    createFileIfNotExist(subFile2);
    createFileIfNotExist(subBufferName);

    //подключаем к ним потоки
    fstream set1(subFile1);
    fstream set2(subFile2);
    fstream subBuffer(subBufferName);

    //подготавливаем буфер и под-буфер для результата промежуточной сортировки
    copyAll(numberOfRecords, buffer, subBuffer);
    /*buffer.close();
    this->clearFile(bufferName);
    buffer.open(bufferName);*/
    rewind(buffer);
    rewind(subBuffer);

    //определяем размер сета на этом этапе
    int set = pow(2, level);

    for (int currentRecord = 0; currentRecord < numberOfRecords;) {
        int currentRecordInSet1 = 0;
        int currentRecordInSet2 = 0;
        this->rewind(set1);
        this->rewind(set2);

        for (; currentRecordInSet1 < set && currentRecord < numberOfRecords;
               ++currentRecordInSet1, ++currentRecord) {
            writeNext(readNext(subBuffer), set1);
        }
        for (; currentRecordInSet2 < set && currentRecord < numberOfRecords;
               ++currentRecordInSet2, ++currentRecord) {
            writeNext(readNext(subBuffer), set2);
        }

        mergeTwoFiles(set1, currentRecordInSet1, set2, currentRecordInSet2);
    }

    set1.close();
    set2.close();
    remove(subFile1.c_str());
    remove(subFile2.c_str());

    if (set * 2 < numberOfRecords) {
        sortNextLevel(level + 1);
    }
}

void Sorter::mergeTwoFiles(fstream &set1, int sizeSet1, fstream &set2, int sizeSet2) {
    //переходим в начало файла
    rewind(set1);
    rewind(set2);

    //добавляем нужные констанкты
    vector<string> arg1;
    vector<string> arg2;
    bool isReady1 = false;
    bool isReady2 = false;

    while (sizeSet1 + sizeSet2 > 0) {
        //проверка, если один из сетов уже пустой
        if (sizeSet2 == 0 && !isReady2) {
            if (isReady1) {
                writeNext(arg1, buffer);
                sizeSet1--;
                isReady1 = false;
            }
            while (sizeSet1 > 0) {
                writeNext(readNext(set1), buffer);
                sizeSet1--;
            }
            continue;
        }
        if (sizeSet1 == 0 && !isReady1) {
            if (isReady2) {
                writeNext(arg2, buffer);
                sizeSet2--;
                isReady2 = false;
            }
            while (sizeSet2 > 0) {
                writeNext(readNext(set2), buffer);
                sizeSet2--;
            }
            continue;
        }

        //получаем значение сравниваемых записей
        if (!isReady1) {
            arg1 = readNext(set1);
            isReady1 = true;
        }
        if (!isReady2) {
            arg2 = readNext(set2);
            isReady2 = true;
        }

        /*////debug
        cout << "arg1: " << arg1[0] << " " << arg1[1] << " " << arg1[2] << endl;
        cout << "arg2: " << arg2[0] << " " << arg2[1] << " " << arg2[2] << endl << endl;
        ////*/

        //сравнение
        if (firsIsBigger(arg1, arg2)) {
            writeNext(arg2, buffer);
            isReady2 = false;
            sizeSet2--;
        } else {
            writeNext(arg1, buffer);
            isReady1 = false;
            sizeSet1--;
        }
    }

    clearFile(subFile1);
    clearFile(subFile2);
}

bool Sorter::firsIsBigger(vector<string> firstRecord, vector<string> secondRecord) {
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
