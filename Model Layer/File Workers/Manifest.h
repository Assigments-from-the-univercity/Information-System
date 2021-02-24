//
// Created by mark on 07.02.21.
//

#ifndef INFORMATION_SYSTEM_MANIFEST_H
#define INFORMATION_SYSTEM_MANIFEST_H

#include "../../Header.h"
#include "FileWorker.h"

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
class Manifest : FileWorker {
private:
    vector<List> namesOfTables;
    vector<List> descriptionsOfTables;

    void safeState();

    void loadState();

public:
    Manifest();

    vector<string> getTables();

    void addTable(string fileName, string fileProperties);
};

#endif //INFORMATION_SYSTEM_MANIFEST_H
