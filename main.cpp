#include <iostream>
#include <vector>
#include <cstring>
#include <filesystem>
#include <cstdio>

using namespace std;

static const int INT_SIZE = 4;
static const int NAME_SIZE = 20;
static const int DESCRIPTION_SIZE = 100;

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

    void setProperties() {
        //TODO load properties from file
    }

public:
    char name[NAME_SIZE];
    TableProperties properties;

    Table() {}

    Table(char name[]) {
        setTable(name);
    }

    void setTable(char name[]){
        strcpy(this->name, name);
        //TODO set up *fp for working with file
        //TODO set up *fpProp for working with file
        setProperties();
    }

    void printNotes(vector<RequestDouble> requestDouble, vector<RequestString> requestString) {
        //TODO
    }

    void addNote(vector<NoteValue> noteProperties) {
        //TODO
    }

    /**
     * This method change table properties according to parameters.
     *
     * @param tableProperties Properties to apply
     * @param name Name of changing file
     */
    static void changeTableProperties(TableProperties tableProperties, char *name) {
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
    void createNewFiles(char name[NAME_SIZE]) {
        string stringName(name);
        string folderName = "tables/";
        string propName = "-prop";
        string sourceType = ".dat";

        string newFile = folderName + stringName + sourceType;
        string newPropFile = folderName + stringName + propName + sourceType;

        char fileName[newFile.length() + 1];
        strcpy(fileName, newFile.c_str());

        char propFileName[newPropFile.length() + 1];
        strcpy(propFileName, newPropFile.c_str());

        FILE *fpNew = fopen(fileName, "w+b");
        fpNew = fopen(propFileName, "w+b");
    }

    /**
     * This method make manifest.dat up-to-date.
     * (synchronize with "vector<TableProperties> tables")
     */
    void refreshManifest() {
        fp = fopen(FILE_NAME, "w+b");
        int size = tables.size();
        fwrite(&size, INT_SIZE, 1, fp);
        for (int i = 0; i < size; ++i) {
            fwrite(&tables[i], sizeof(TableProperties), 1, fp);
        }
        fflush(fp);
        fp = fopen(FILE_NAME, "r+b");
    }

    /**
     * This method make "vector<TableProperties> tables" up-to-date.
     * (synchronize with manifest.dat)
     */
    void updateData() {
        rewind(fp);
        int size = 0;
        fread(&size, INT_SIZE, 1, fp);
        TableProperties table;
        tables.clear();
        for (int i = 0; i < size; ++i) {
            fread(&table, sizeof(TableProperties), 1, fp);
            tables.push_back(table);
        }
    }

public:
    /**
     * public constructor
     */
    Manifest() {
        fp = fopen(FILE_NAME, "r+b");
        if (fp == NULL) {
            cout << "Файл \"manifest.dat\" створений заново." << endl;

            refreshManifest();

            remove("tables");
            std::filesystem::create_directory("tables");
        }
        updateData();
    }

    /**
     * This method returns all tables that exist.
     *
     * @return all existing tables.
     */
    vector<TableProperties> getTables() {
        return tables;
    }

    /**
     * pring all tables in console.
     */
    void printTables() {
        int size = tables.size();
        cout << "список доступних таблиць:" << endl;
        for (int i = 0; i < size; i++) {
            cout << "Ім'я: " << tables[i].name << "\nОпис: " << tables[i].description << endl << endl;
        }
        if (size == 0) {
            cout << "немає доступних таблиць." << endl;
        }
        cout << "hint: use \"cd <name of table>\" to go to the table." << endl;
    }

    /**
     * This method adds a new table to manifest.dat
     * to managing this file in future.
     * Also, this method driggers creation files for
     * this table.
     *
     * @param tableProperties properties of existing table
     */
    void addTable(TableProperties tableProperties) {
        tables.push_back(tableProperties);

        refreshManifest();
        updateData();
        createNewFiles(tableProperties.name);
    }
};

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
    Manifest::TableProperties toTableProperties(string fileName, string fileDescription) {
        Manifest::TableProperties newTable;

        strcpy(newTable.name, fileName.c_str());
        strcpy(newTable.description, fileDescription.c_str());

        newTable.name[NAME_SIZE - 1] = '\0';
        newTable.description[DESCRIPTION_SIZE - 1] = '\0';

        return newTable;
    }

    /**
     * This method convert strings to corresponding properties of table (TableProperties).
     *
     * @param numberOfProperties Size of the vector
     * @param values Vector of strings.
     * @return Table::TableProperties
     */
    Table::TableProperties
    toNoteProperties(int numberOfProperties, vector<string> values, vector<string> namesOfValues) {
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

public:
    void lsTable() {
        manifest.printTables();
    }

    void addTable() {
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

    void cd(char tableName[NAME_SIZE]) {
        table.setTable(tableName);
    }

    void lsNotes() {
        //TODO set properties
        //table.printTable();
    }

    void addNote() {
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
};

/**
 * This class represent the view layer.
 * This class is used for working with console
 * and than giving commands to controller layer.
 */
class View {
private:
    Controller controller;
    vector<string> userDirectory;

    /**
     * This method print the path where user is.
     * Ut gives user a hint where he is and what he can do.
     */
    void printPath() {
        int size = userDirectory.size();
        for (int i = 0; i < size; ++i) {
            cout << userDirectory[i] << "/";
        }
        cout << "> ";
    }

    /**
     * Main method in this class that receive users command
     * and call an appropriate method from controller layer.
     *
     * @param command A command from user.
     */
    void userCommand(string command) {
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
            } else if (command == "add") {
                controller.addNote();
            } else if (command == "back" && userDirectory.size() == 2) {
                userDirectory.pop_back();
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

public:
    /**
     * Public constructor
     */
    View() {
        userDirectory.push_back("home");
    }

    /**
     * The method that start working with user using console.
     */
    void startWork() {
        string command;
        cout << "Щоб завершити роботу введіть \"stop\"" << endl;
        do {
            printPath();
            cin >> command;
            userCommand(command);
        } while (command != "stop");
    }
};

/**
 * MVC pattern is used in this program for
 * managing the data. (https://ru.wikipedia.org/wiki/Model-View-Controller)
 */
int main() {
    //create Model object to have an accesses to method startWork()
    View model;
    model.startWork();
}
