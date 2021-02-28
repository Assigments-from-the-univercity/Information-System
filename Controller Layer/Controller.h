//
// Created by mark on 07.02.21.
//

#ifndef INFORMATION_SYSTEM_CONTROLLER_H
#define INFORMATION_SYSTEM_CONTROLLER_H


#include "../Model Layer/File Workers/Manifest.h"
#include "../Header.h"
#include "../Model Layer/Table.h"

/**
 * This class represent the controller layer.
 * This class can call methods from Manifest and Table classes to
 * change, create or delete data.
 * This class isn't working with data directly, but can call methods to do it.
 */
class Controller {
private:
    Manifest manifest;
    Table *table = nullptr;

    struct UserRequest {
        string name;
        string oper;
        string value;
    };

    /*Manifest::TableProperties toTableProperties(string fileName, string fileDescription);

    Table::TableProperties
    toNoteProperties(int numberOfProperties, vector<string> values, vector<string> namesOfValues);

    Request::State getState(UserRequest userRequest);

    vector<Request> makeRequest(vector<UserRequest> userRequest);*/

public:
    Controller();

    void lsTable();

    void addTable();

    void cd(string tableName);

    void lsRecords();

    void selectRecords();

    void addRecord();

    void deleteRecord();

    void changeRecord();
};


#endif //INFORMATION_SYSTEM_CONTROLLER_H
