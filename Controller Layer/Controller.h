//
// Created by mark on 07.02.21.
//

#ifndef INFORMATION_SYSTEM_CONTROLLER_H
#define INFORMATION_SYSTEM_CONTROLLER_H


#include "../Model Layer/Table.h"
#include "../View Layer/Printer.h"
#include "../Basic Units/Action.h"
#include "../Basic Units/Sort Request/PreSortRequest.h"
#include "../View Layer/Parser.h"
#include "Sorters/Sorter.h"
#include "Filter.h"
#include "Sorters/Trie/Trie.h"
#include "Sorters/RB Tree/RBTree.h"

/**
 * This class represent the controller layer.
 * This class can call methods from Manifest and Table classes to
 * change, create or delete data.
 * This class isn't working with data directly, but can call methods to do it.
 */

const static string manifestName = "Manifest";

class Controller {
private:
    /*struct UserRequest {
        string name;
        string oper;
        string value;
    };*/

    Table manifest;
    string currentTableName = "";
    string tempFile = "tables\\temp_result.csv";

    void createFile(string fileName);

    /*Manifest::TableProperties toTableProperties(string fileName, string fileDescription);

    Table::TableProperties
    toNoteProperties(int numberOfProperties, vector<string> values, vector<string> namesOfValues);

    FilterRequest::State getState(UserRequest userRequest);

    vector<FilterRequest> makeRequest(vector<UserRequest> userRequest);*/

public:
    Controller();

    void getTables();

    void addTable();

    void cd(string tableName);

    void exit();

    void getRecords();

    void addRecord();

    void deleteRecord();

    void changeRecord();
};


#endif //INFORMATION_SYSTEM_CONTROLLER_H
