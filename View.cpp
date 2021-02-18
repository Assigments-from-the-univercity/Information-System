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
            controller.lsTable();
        } else if (command == "add") {
            controller.addTable();
        } else if (command == "cd" && userDirectory.size() == 1) {
            char tableName[NAME_SIZE];
            cin >> tableName;
            tableName[NAME_SIZE - 1] = '\0';

            //TODO проверить, что имя существует

            userDirectory.push_back(tableName);

            controller.cd(tableName);
        } else if (command == "stop") {
            cout << "program is stopped.";
            return;
        } else {
            cout << "command \"" + command + "\" wasn't recognized." << endl;
        }
    } else if (userDirectory.size() == 2) {
        if (command == "ls") {
            controller.lsNotes();
        } else if (command == "SELECT") {
            controller.selectNotes();
        } else if (command == "add") {
            controller.addNote();
        } else if (command == "back" && userDirectory.size() == 2) {
            userDirectory.pop_back();
        } else if (command == "delete") {
            controller.deleteNote();
        } else if (command == "change") {
            controller.changeNote();
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
