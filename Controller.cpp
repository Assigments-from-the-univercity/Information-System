//
// Created by mark on 07.02.21.
//

#include "Controller.h"

Manifest::TableProperties Controller::toTableProperties(string fileName, string fileDescription) {
    Manifest::TableProperties newTable;

    strcpy(newTable.name, fileName.c_str());
    strcpy(newTable.description, fileDescription.c_str());

    newTable.name[NAME_SIZE - 1] = '\0';
    newTable.description[DESCRIPTION_SIZE - 1] = '\0';

    return newTable;
}

Table::TableProperties
Controller::toNoteProperties(int numberOfProperties, vector<string> values, vector<string> namesOfValues) {
    Table::TableProperties notesProperties;

    notesProperties.numberOfNotes = 0;
    notesProperties.numberOfProperties = numberOfProperties;

    Table::Field field;
    for (int i = 0; i < numberOfProperties; ++i) {
        if (values[i] == "string") {
            field.type = Table::TypeOfNote::STRING;
        } else if (values[i] == "double") {
            field.type = Table::TypeOfNote::DOUBLE;
        } else if (values[i] == "date") {
            field.type = Table::TypeOfNote::DATE;
        } else {
            cout << "Wrong input of properties!" << endl << "Program was stopped.";
            abort();
        }

        strcpy(field.name, namesOfValues[i].c_str());
        field.name[NAME_SIZE - 1] = '\0';

        notesProperties.values.push_back(field);
    }

    notesProperties.sizeOfVector = sizeof(Table::TypeOfNote) * notesProperties.values.size();

    return notesProperties;
}

void Controller::makeRequest(vector<Table::RequestDouble> requestDouble, vector<Table::RequestString> requestString,
                             vector<Table::UserRequest> userRequest) {
    for (int i = 0; i < table.properties.numberOfProperties; ++i) {
        for (int j = 0; j < userRequest.size(); ++j) {
            if (userRequest[j].name == table.properties.values[i].name){
                if (table.properties.values[i].type == Table::TypeOfNote::DOUBLE) {
                    Table::RequestDouble mRequestDouble;
                    //mRequestDouble.

                    requestDouble.push_back(mRequestDouble);
                }
            }
        }
    }
}

void Controller::lsTable() {
    manifest.printTables();
}

void Controller::addTable() {
    int numberOfProperties;
    string fileName, fileDescription;
    vector<string> values;
    vector<string> namesOfValues;

    cout << "Введіть ім'я файлу: ";
    cin >> fileName;
    cin.ignore(32767, '\n'); // удаляем символ новой строки из входного потока данных
    cout << "Введіть опис файлу: ";
    getline(cin, fileDescription);
    cout << "Введіть кількість полів: ";
    cin >> numberOfProperties;
    string type;
    string nameOfType;
    for (int i = 0; i < numberOfProperties; ++i) {
        cout << "Введіть ім'я " << (i + 1) << " поля: ";
        cin >> nameOfType;
        cout << "Введіть тип " << (i + 1) << " поля: ";
        cin >> type;
        if (type == "string" || type == "double" || type == "date") {
            values.push_back(type);
            namesOfValues.push_back(nameOfType);
        }
    }

    manifest.addTable(toTableProperties(fileName, fileDescription));

    char name[NAME_SIZE];
    strcpy(name, fileName.c_str());
    name[NAME_SIZE - 1] = '\0';
    Table::changeTableProperties(toNoteProperties(numberOfProperties, values, namesOfValues), name);
}

void Controller::cd(char tableName[NAME_SIZE]) {
    table.setTable(tableName);
}

void Controller::lsNotes() {
    vector<Table::RequestDouble> requestDouble;
    vector<Table::RequestString> requestString;
    vector<Table::UserRequest> userRequest;
    makeRequest(requestDouble, requestString, userRequest);
    table.printNotes(requestDouble, requestString);
}

void Controller::addNote() {
    Table::NoteValue noteValue;
    vector<Table::NoteValue> values;
    for (int i = 0; i < table.properties.numberOfProperties; ++i) {
        cout << "Введіть значення поля ";
        cout << table.properties.values[i].name;
        cout << "тип (";
        cout << table.properties.values[i].type;
        cout << "): ";

        cin >> noteValue.value;

        values.push_back(noteValue);
    }

    table.addNote(values);
}