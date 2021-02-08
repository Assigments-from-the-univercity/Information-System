//
// Created by mark on 07.02.21.
//

#ifndef INFORMATION_SYSTEM_CONTROLLER_H
#define INFORMATION_SYSTEM_CONTROLLER_H


#include "Manifest.h"
#include "Header.h"
#include "Table.h"

/**
 * This class represent the controller layer.
 * This class can call methods from Manifest and Table classes to
 * change, create or delete data.
 * This class isn't working with data directly, but can call methods to do it.
 */
class Controller {
private:
    Manifest manifest;
    Table table;

    /**
     * This method convert string-type name and description of file to
     * appropriate Manifest::TableProperties format.
     *
     * @param fileName mane of table we want to convert.
     * @param fileDescription description of table we want to convert.
     * @return Manifest::TableProperties
     */
    Manifest::TableProperties toTableProperties(string fileName, string fileDescription);

    /**
     * This method convert strings to corresponding properties of table (TableProperties).
     *
     * @param numberOfProperties Size of the vector
     * @param values Vector of strings.
     * @return Table::TableProperties
     */
    Table::TableProperties
    toNoteProperties(int numberOfProperties, vector<string> values, vector<string> namesOfValues);

    Table::RequestDouble toRequestDouble(Table::UserRequest userRequest) {
        if (userRequest.oper == "="){

        }
    }

    void makeRequest(vector<Table::RequestDouble> requestDouble, vector<Table::RequestString> requestString,
                     vector<Table::UserRequest> userRequest);

public:
    void lsTable();

    void addTable();

    void cd(char tableName[NAME_SIZE]);

    void lsNotes();

    void addNote();
};


#endif //INFORMATION_SYSTEM_CONTROLLER_H
