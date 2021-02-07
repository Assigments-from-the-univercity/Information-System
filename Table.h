//
// Created by mark on 07.02.21.
//

#ifndef INFORMATION_SYSTEM_TABLE_H
#define INFORMATION_SYSTEM_TABLE_H

#include "Header.h"

/**
 * This class represent (a part of) the model layer.
 * This class works with <sheetName>.dat and <sheetName>-prop.dat - files,
 * that have tables data and table properties.
 *
 * Template of <sheetName>-prop.dat :
 *  numberOfNotes (int)
 *  numberOfProperties (int)
 *  sizeOfVector (int)
 *  values (vector<TypeOfNote>)
 *
 * Template of <sheetName>.dat :
 *  note1 (TableProperties)
 *  note2 (TableProperties)
 *  note3 (TableProperties)
 *  ...
 *  note_i (TableProperties)
 */
class Table {
public:
    enum TypeOfNote {
        STRING,
        DOUBLE,
        DATE
    };

    struct Field {
        TypeOfNote type;
        char name[NAME_SIZE];
    };

    struct TableProperties {
        int numberOfNotes;
        int numberOfProperties; // избыточное
        int sizeOfVector;       // избыточное
        vector<Field> values;
    };

    struct RequestDouble {
        double more;
        double less;
    };

    struct RequestString {
        string more;
        string less;
    };

    struct NoteValue {
        char value[DESCRIPTION_SIZE];
    };

private:
    FILE *fp;
    FILE *fpProp;

    void setProperties();

public:
    char name[NAME_SIZE];
    TableProperties properties;

    Table();

    Table(char name[]);

    void setTable(char name[]);

    void printNotes(vector<RequestDouble> requestDouble, vector<RequestString> requestString);

    void addNote(vector<NoteValue> noteProperties);

    /**
     * This method change table properties according to parameters.
     *
     * @param tableProperties Properties to apply
     * @param name Name of changing file
     */
    static void changeTableProperties(TableProperties tableProperties, char *name){
        string n1(name);
        string n = "tables/";
        n += n1;
        n += "-prop.dat";
        char fileName[n.size() + 1];
        strcpy(fileName, n.c_str());
        fileName[n.size()] = '\0';
        FILE *fp1 = fopen(fileName, "wb");

        fwrite(&tableProperties.numberOfNotes, INT_SIZE, 1, fp1);
        fwrite(&tableProperties.numberOfProperties, INT_SIZE, 1, fp1);
        fwrite(&tableProperties.sizeOfVector, INT_SIZE, 1, fp1);
        fwrite(&tableProperties.values, tableProperties.sizeOfVector, 1, fp1);

        fflush(fp1);
    }
};


#endif //INFORMATION_SYSTEM_TABLE_H
