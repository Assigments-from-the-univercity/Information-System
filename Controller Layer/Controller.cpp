//
// Created by mark on 07.02.21.
//

#include "Controller.h"

void Controller::createTempFile() {
    ofstream f(tempFile);
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
    createTempFile();
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
    createTempFile();
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

void Controller::getRecords() {
    createTempFile();
    fstream allRecordsFromTable(tempFile);
    Table table(currentTableName);
    table.get(allRecordsFromTable);

    //TODO filter and sorter the data

    Printer printer(allRecordsFromTable);
    printer.print();

    allRecordsFromTable.close();
    remove(tempFile.c_str());
}

void Controller::addRecord() {
    createTempFile();
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
    createTempFile();
    fstream allRecordsFromTable(tempFile);
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

    remove(tempFile.c_str());
}
