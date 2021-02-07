//
// Created by mark on 07.02.21.
//

#ifndef INFORMATION_SYSTEM_MANIFEST_H
#define INFORMATION_SYSTEM_MANIFEST_H

#include "Header.h"

/**
 * This class represent (a part of) the model layer.
 * This class works with manifest.dat - file, that has data about
 * tables (name and description) to work with them.
 *
 * Template of manifest.dat :
 *  numberOfSheets (int)
 *  Sheet1 (TableProperties)
 *  Sheet2 (TableProperties)
 *  Sheet3 (TableProperties)
 *  ...
 *  Sheet_i (TableProperties)
 */
class Manifest {
public:
    struct TableProperties {
        char name[NAME_SIZE];
        char description[DESCRIPTION_SIZE];
    };
private:
    const char *FILE_NAME = "manifest.dat";
    FILE *fp;
    vector<TableProperties> tables;

    /**
     * This method creates files <sheetName>.dat and <sheetName>-prop.dat
     * (properties) in /tables directory.
     *
     * @param name The name of new table
     */
    void createNewFiles(char name[NAME_SIZE]);

    /**
     * This method make manifest.dat up-to-date.
     * (synchronize with "vector<TableProperties> tables")
     */
    void refreshManifest();

    /**
     * This method make "vector<TableProperties> tables" up-to-date.
     * (synchronize with manifest.dat)
     */
    void updateData();

public:
    /**
     * public constructor
     */
    Manifest();

    /**
     * This method returns all tables that exist.
     *
     * @return all existing tables.
     */
    vector<TableProperties> getTables();

    /**
     * pring all tables in console.
     */
    void printTables();

    /**
     * This method adds a new table to manifest.dat
     * to managing this file in future.
     * Also, this method driggers creation files for
     * this table.
     *
     * @param tableProperties properties of existing table
     */
    void addTable(TableProperties tableProperties);
};

#endif //INFORMATION_SYSTEM_MANIFEST_H
