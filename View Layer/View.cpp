//
// Created by mark on 07.02.21.
//

#include "View.h"

void View::printPath() {
    int size = userDirectory.size();
    for (int i = 0; i < size; ++i) {
        cout << userDirectory[i] << "/";
    }
    cout << "> "; //TODO cout << "> "; - не выводит последний пробел
}

void View::userCommand(string command) {
    if (userDirectory.size() == 1) {
        if (command == "ls") {
            controller.getTables();
        } else if (command == "add") {
            controller.addTable();
        } else if (command == "cd" && userDirectory.size() == 1) {
            string tableName;
            cin >> tableName;

            userDirectory.push_back(tableName);
            controller.cd(tableName);
        } else if (command == "SELECT") {
            controller.getRecords();
        } else if (command == "stop") {
            cout << "program is stopped.";
            return;
        } else {
            cout << "command \"" + command + "\" wasn't recognized." << endl;
        }
    } else if (userDirectory.size() == 2) {
        if (command == "ls") {
            controller.getRecords();
        } else if (command == "SELECT") {
            controller.getRecords();
        } else if (command == "add") {
            controller.addRecord();
        } else if (command == "back" && userDirectory.size() == 2) {
            userDirectory.pop_back();
            controller.exit();
        } else if (command == "delete") {
            controller.deleteRecord();
        } else if (command == "change") {
            controller.changeRecord();
        } else if (command == "stop") {
            cout << "program is stopped.";
            return;
        } else {
            cout << "command \"" + command + "\" wasn't recognized." << endl;
        }
    } else {
        cout << "ERROR! You are in wrong directory!" << endl;
    }
}

View::View() {
    userDirectory.push_back("home");
}

void View::startWork() {
    string command;
    cout << "To stop the program write \"stop\"" << endl;
    do {
        printPath();
        cin >> command;
        userCommand(command);
    } while (command != "stop");
}
