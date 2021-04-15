//
// Created by Mark on 11.03.2021.
//

#include "Sorter.h"

Sorter::Sorter(istream &fin, ostream &fout) : CSVWorker(fin, fout),
                                              Sortable(fin, fout) {
    getProperties(numberOfRecords, names, types);
}

void Sorter::sort(vector<SortRequest> sortRequest) {
    this->sortRequest = sortRequest;

    //creation buffer file
    string bufferName = "buffer.csv";
    createFileIfNotExist(bufferName);
    fstream buffer(bufferName);
    copyFromCurrentPosition(numberOfRecords, getFin(), buffer);

    // sorting itself
    sortNextLevel(0, buffer);

    // printing result
    setProperties(names, types);
    copyAll(numberOfRecords, buffer, getFout());

    buffer.close();
    remove(bufferName.c_str());
}

void Sorter::sortNextLevel(int level, fstream &buffer) {
    // names for files need in the sort
    string subFile1 = "set1.csv";
    string subFile2 = "set2.csv";
    string subBufferName = "subBuffer.csv";

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

        mergeTwoFiles(set1, currentRecordInSet1, set2, currentRecordInSet2, buffer);
        clearFile(subFile1);
        clearFile(subFile2);
    }

    set1.close();
    set2.close();
    remove(subFile1.c_str());
    remove(subFile2.c_str());

    if (set * 2 < numberOfRecords) {
        sortNextLevel(level + 1, buffer);
    }
}

void Sorter::mergeTwoFiles(fstream &set1, int sizeSet1, fstream &set2, int sizeSet2, fstream &buffer) {
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

        //сравнение
        if (firsIsBigger(arg1, arg2, sortRequest, types)) {
            writeNext(arg2, buffer);
            isReady2 = false;
            sizeSet2--;
        } else {
            writeNext(arg1, buffer);
            isReady1 = false;
            sizeSet1--;
        }
    }
}
