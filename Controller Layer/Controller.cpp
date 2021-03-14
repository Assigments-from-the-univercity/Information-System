//
// Created by mark on 07.02.21.
//

#include "Controller.h"

Controller::Controller() /*: manifest()*/ {

}

void Controller::lsTable() {

}

void Controller::addTable() {

}

void Controller::cd(string tableName) {
    static Table table(tableName);
    this->table = &table;
}

void Controller::lsRecords() {

}

void Controller::selectRecords() {

}

void Controller::addRecord() {

}

void Controller::deleteRecord() {

}

void Controller::changeRecord() {

}
/*
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

    return notesProperties;
}

Table::FilterRequest::State Controller::getState(UserRequest userRequest) {
    if (userRequest.oper == "<") {
        return Table::FilterRequest::LESS;
    } else if (userRequest.oper == ">") {
        return Table::FilterRequest::MORE;
    } else if (userRequest.oper == "<=") {
        return Table::FilterRequest::NOT_MORE;
    } else if (userRequest.oper == ">=") {
        return Table::FilterRequest::NOT_LESS;
    } else if (userRequest.oper == "=") {
        return Table::FilterRequest::EQUAL;
    } else if (userRequest.oper == "in") {
        return Table::FilterRequest::INCLUDED;
    } else {
        return Table::FilterRequest::IGNORE_IT;
    }
}

vector<Table::FilterRequest> Controller::makeRequest(vector<UserRequest> userRequest) {
    vector<Table::FilterRequest> request;

    Table::FilterRequest mRequest;
    for (int i = 0; i < table.properties.numberOfProperties; ++i) {
        mRequest.value = "0";
        mRequest.state = Table::FilterRequest::State::IGNORE_IT;

        for (int j = 0; j < userRequest.size(); ++j) {
            if (userRequest[j].name == table.properties.values[i].name) {
                mRequest.value = userRequest[j].value;
                mRequest.state = getState(userRequest[j]);
            }
        }

        request.push_back(mRequest);
    }

    return request;
}

void Controller::lsTable() {
    manifest.printTables();
}

void Controller::addTable() {
    int numberOfProperties;
    string fileName, fileDescription;
    vector<string> values;
    vector<string> namesOfValues;

    cout << "Write a name of the file: ";
    cin >> fileName;
    cin.ignore(32767, '\n'); // удаляем символ новой строки из входного потока данных
    cout << "Write a description of the file: ";
    getline(cin, fileDescription);
    cout << "Write a number of fields in a file: ";
    cin >> numberOfProperties;
    string type;
    string nameOfType;
    for (int i = 0; i < numberOfProperties; ++i) {
        cout << "Write a name of " << (i + 1) << " field: ";
        cin >> nameOfType;
        cout << "Write a type of " << (i + 1) << " field: ";
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

void Controller::lsRecords() {
    vector<UserRequest> userRequest;
    vector<Table::FilterRequest> request = makeRequest(userRequest);
    table.printNotes(request);
}

void Controller::selectRecords() {
    vector<Table::FilterRequest> request;
    vector<UserRequest> userRequest;

    int numberOfFactors;
    cin >> numberOfFactors;
    UserRequest userReq;
    for (int i = 0; i < numberOfFactors; ++i) {
        cin >> userReq.name >> userReq.oper >> userReq.value;
        userRequest.push_back(userReq);
    }

    request = makeRequest(userRequest);
    table.printNotes(request);
}

void Controller::addRecord() {
    Table::NoteValue noteValue;
    vector<Table::NoteValue> values;
    for (int i = 0; i < table.properties.numberOfProperties; ++i) {
        cout << "Write the value of the field ";
        cout << table.properties.values[i].name;
        cout << " type (";
        cout << Table::getTypeOfNote(table.properties.values[i].type);
        cout << "): ";

        cin >> noteValue.value;

        values.push_back(noteValue);
    }

    table.addNote(values);
}

void Controller::deleteRecord() {
    int id;
    cin >> id;

    table.deleteNote(id - 1);
}

void Controller::changeRecord() {
    int id;
    cin >> id;

    Table::NoteValue noteValue;
    vector<Table::NoteValue> values;
    for (int i = 0; i < table.properties.numberOfProperties; ++i) {
        cout << "Write the value of the field ";
        cout << table.properties.values[i].name;
        cout << " type (";
        cout << Table::getTypeOfNote(table.properties.values[i].type);
        cout << "): ";

        cin >> noteValue.value;

        values.push_back(noteValue);
    }

    table.changeNote(values, id - 1);
}*/