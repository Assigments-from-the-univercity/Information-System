//
// Created by mark on 07.02.21.
//

#include "Controller.h"
#include "../Basic Units/Action.h"
#include "../Basic Units/PreSortRequest.h"
#include "../View Layer/Parser.h"
#include "Sorter.h"
#include "Filter.h"
#include "../Basic Units/Trie/Trie.h"

void Controller::createFile(string fileName) {
    ofstream f(fileName);
    f.close();
}

Controller::Controller() : manifest(manifestName) {
    ifstream fin("tables\\" + manifestName + ".dat");
    if (fin.is_open() == false) {
        vector<string> names;
        vector<TypeOfNote> types;
        TypeOfNote type;

        names.push_back("name");
        names.push_back("description");

        type.setType("STRING");
        types.push_back(type);
        types.push_back(type);

        Table::createTable(manifestName, names, types);
    }
}

void Controller::getTables() {
    createFile(tempFile);
    fstream allRecordsFromTable(tempFile);
    manifest.get(allRecordsFromTable);

    Printer printer(allRecordsFromTable);
    printer.print();

    allRecordsFromTable.close();
    remove(tempFile.c_str());
}

void Controller::addTable() {
    // данные таблици
    int numberOfProperties;
    string tableDescription;
    string tableName;
    vector<string> names;
    vector<TypeOfNote> types;

    // дополнительные переменные
    string stringTypeOfColumn;
    TypeOfNote typeOfColumn;
    string nameOfColumn;

    // получаем имя новой таблицы
    cout << "Write a name of the file: ";
    cin >> tableName;

    // получаем описание таблицы
    cin.ignore(32767, '\n'); // удаляем символ новой строки из входного потока данных
    cout << "Write a description of the file: ";
    getline(cin, tableDescription);

    // добавляем таблицу в manifest
    vector<string> tableProperties;
    tableProperties.push_back(tableName);
    tableProperties.push_back(tableDescription);
    manifest.add(tableProperties);

    // получаем количество полей таблицы
    cout << "Write a number of fields in a file: ";
    cin >> numberOfProperties;

    // получаем имя и тип каждого поля таблицы
    for (int i = 0; i < numberOfProperties; ++i) {
        cout << "Write a name of " << (i + 1) << " field: ";
        cin >> nameOfColumn;
        cout << "Write a type of " << (i + 1) << " field: ";
        cin >> stringTypeOfColumn;
        if (stringTypeOfColumn == "STRING" || stringTypeOfColumn == "DOUBLE") {
            typeOfColumn.setType(stringTypeOfColumn);
            types.push_back(typeOfColumn);
            names.push_back(nameOfColumn);
        } else {
            cout << "wrong input: " + stringTypeOfColumn + " isn't STRING or DOUBLE." << endl;
            cout << "re-input this field." << endl;
            i--;
        }
    }

    Table::createTable(tableName, names, types);
}

void Controller::cd(string tableName) {
    createFile(tempFile);
    fstream allRecordsFromTable(tempFile);
    manifest.get(allRecordsFromTable);

    CSVReader csvReader(allRecordsFromTable);
    vector<string> recordData;
    int numberOfRecords;
    vector<string> names;
    vector<TypeOfNote> types;
    csvReader.getProperties(numberOfRecords, names, types);

    for (int i = 0; i < numberOfRecords; ++i) {
        recordData = csvReader.readNext();
        if (recordData[0] == tableName) {
            currentTableName = tableName;
            break;
        }
    }

    allRecordsFromTable.close();
    remove(tempFile.c_str());
}

void Controller::exit() {
    currentTableName = "";
}

void Controller::getRecords() {
    Action action;
    string tableName;
    vector<UserRequest> userRequest;
    vector<PreSortRequest> preSortRequest;
    vector<string> names;
    vector<TypeOfNote> types;

    action.actionType = Action::SELECT;
    Parser::makeRequest(action, tableName, userRequest, preSortRequest);

    createFile(tempFile);
    createFile("tables\\temp_2.csv");
    fstream allRecordsFromTable(tempFile);
    fstream tempCSVFile("tables\\temp_2.csv");
    Table table(tableName);
    table.get(allRecordsFromTable);

    table.getProperties(names, types);

    Filter filter(allRecordsFromTable, tempCSVFile);
    filter.filtrate(UserRequest::makeRequest(userRequest, names));

    allRecordsFromTable.close();
    remove(tempFile.c_str());
    createFile(tempFile);
    allRecordsFromTable.open(tempFile);

    cout << "choose sort method: ";
    string s;
    cin >> s;
    if (s == "trie") {
        Trie trie(tempCSVFile, allRecordsFromTable, PreSortRequest::makeSortRequest(preSortRequest, names));
    } else if (s == "sorter") {
        Sorter sorter(tempCSVFile, allRecordsFromTable, PreSortRequest::makeSortRequest(preSortRequest, names));
        sorter.sort();
    }

    Printer printer(allRecordsFromTable);
    printer.print();

    allRecordsFromTable.close();
    remove(tempFile.c_str());
}

void Controller::addRecord() {
    createFile(tempFile);
    fstream allRecordsFromTable(tempFile);
    Table table(currentTableName);

    vector<string> names;
    vector<TypeOfNote> types;
    table.getProperties(names, types);
    int numberOfColumns = names.size();

    string recordFiledValue;
    vector<string> values;
    for (int i = 0; i < numberOfColumns; ++i) {
        cout << "Write a value of the field ";
        cout << names[i];
        cout << " type (";
        cout << types[i].getType();
        cout << "): ";

        cin >> recordFiledValue;
        //TODO verify recordFiledValue compare the type
        values.push_back(recordFiledValue);
    }

    table.add(values);

    allRecordsFromTable.close();
    remove(tempFile.c_str());
}

void Controller::deleteRecord() {
    Table table(currentTableName);

    string key;
    cin >> key;
    table.deleteItem(key);
}

void Controller::changeRecord() {
    Table table(currentTableName);

    vector<string> names;
    vector<TypeOfNote> types;
    table.getProperties(names, types);
    int numberOfColumns = names.size();

    string recordFiledValue;
    vector<string> values;
    for (int i = 0; i < numberOfColumns; ++i) {
        cout << "Write a new value of the field ";
        cout << names[i];
        cout << " type (";
        cout << types[i].getType();
        cout << "): ";

        cin >> recordFiledValue;
        //TODO verify recordFiledValue compare the type
        values.push_back(recordFiledValue);
    }

    table.change(values);
}
