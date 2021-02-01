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
 * that have sheets data and sheet properties.
 *
 * Template of <sheetName>-prop.dat :
 *  numberOfNotes (int)
 *  numberOfProperties (int)
 *  sizeOfVector (int)
 *  values (vector<TypeOfNote>)
 *
 * Template of <sheetName>.dat :
 *  note1 (NotesProperties)
 *  note2 (NotesProperties)
 *  note3 (NotesProperties)
 *  ...
 *  note_i (NotesProperties)
 */
class Sheet {
public:
    enum TypeOfNote {
        STRING,
        DOUBLE,
        DATE
    };

    struct NotesProperties {
        int numberOfNotes;
        int numberOfProperties;
        int sizeOfVector;
        vector<TypeOfNote> values;
    };

private:
    string name;
    FILE *fp;
    //TODO add more propert.

public:
    /**
     * This method change sheet properties according to parameters.
     *
     * @param notesProperties Properties to apply
     * @param name Name of changing file
     */
    static void changeSheetProperties(NotesProperties notesProperties, char *name) {
        string n1(name);
        string n = "sheets/";
        n += n1;
        n += "-prop.dat";
        char fileName[n.size() + 1];
        strcpy(fileName, n.c_str());
        fileName[n.size()] = '\0';
        FILE *fp1 = fopen(fileName, "wb");

        fwrite(&notesProperties.numberOfNotes, INT_SIZE, 1, fp1);
        fwrite(&notesProperties.numberOfProperties, INT_SIZE, 1, fp1);
        fwrite(&notesProperties.sizeOfVector, INT_SIZE, 1, fp1);
        fwrite(&notesProperties.values, notesProperties.sizeOfVector, 1, fp1);

        fflush(fp1);
    }
};

/**
 * This class represent (a part of) the model layer.
 * This class works with manifest.dat - file, that has data about
 * sheets (name and description) to work with them.
 *
 * Template of manifest.dat :
 *  numberOfSheets (int)
 *  Sheet1 (SheetProperties)
 *  Sheet2 (SheetProperties)
 *  Sheet3 (SheetProperties)
 *  ...
 *  Sheet_i (SheetProperties)
 */
class Manifest {
public:
    struct SheetProperties {
        char name[NAME_SIZE];
        char description[DESCRIPTION_SIZE];
    };
private:
    const char *FILE_NAME = "manifest.dat";
    FILE *fp;
    vector<SheetProperties> sheets;

    /**
     * This method creates files <sheetName>.dat and <sheetName>-prop.dat
     * (properties) in /sheets directory.
     *
     * @param name The name of new table
     */
    void createNewFiles(char name[NAME_SIZE]) {
        string stringName(name);
        string folderName = "sheets/";
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
     * (synchronize with "vector<SheetProperties> sheets")
     */
    void refreshManifest() {
        fp = fopen(FILE_NAME, "w+b");
        int size = sheets.size();
        fwrite(&size, INT_SIZE, 1, fp);
        for (int i = 0; i < size; ++i) {
            fwrite(&sheets[i], sizeof(SheetProperties), 1, fp);
        }
        fflush(fp);
        fp = fopen(FILE_NAME, "r+b");
    }

    /**
     * This method make "vector<SheetProperties> sheets" up-to-date.
     * (synchronize with manifest.dat)
     */
    void updateData() {
        rewind(fp);
        int size = 0;
        fread(&size, INT_SIZE, 1, fp);
        SheetProperties sheet;
        sheets.clear();
        for (int i = 0; i < size; ++i) {
            fread(&sheet, sizeof(SheetProperties), 1, fp);
            sheets.push_back(sheet);
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

            remove("sheets");
            std::filesystem::create_directory("sheets");
        }
        updateData();
    }

    /**
     * This method returns all sheets that exist.
     *
     * @return all existing sheets.
     */
    vector<SheetProperties> getSheets() {
        return sheets;
    }

    /**
     * pring all sheets in console.
     */
    void printSheets() {
        int size = sheets.size();
        cout << "список доступних таблиць:" << endl;
        for (int i = 0; i < size; i++) {
            cout << "Ім'я: " << sheets[i].name << "\nОпис: " << sheets[i].description << endl << endl;
        }
        if (size == 0) {
            cout << "немає доступних таблиць." << endl;
        }
        cout << "hint: use \"cd <name of table>\" to go to the table." << endl;
    }

    /**
     * This method adds a new sheet to manifest.dat
     * to managing this file in future.
     * Also, this method driggers creation files for
     * this sheet.
     *
     * @param sheetProperties properties of existing sheet
     */
    void addTable(SheetProperties sheetProperties) {
        sheets.push_back(sheetProperties);

        refreshManifest();
        updateData();
        createNewFiles(sheetProperties.name);
    }
};

/**
 * This class represent the controller layer.
 * This class can call methods from Manifest and Sheet classes to
 * change, create or delete data.
 * This class isn't working with data directly, but can call methods to do it.
 */
class Controller {
private:
    Manifest manifest;
    Sheet sheet;

    /**
     * This method convert string-type name and description of file to
     * appropriate Manifest::SheetProperties format.
     *
     * @param fileName mane of table we want to convert.
     * @param fileDescription description of table we want to convert.
     * @return Manifest::SheetProperties
     */
    Manifest::SheetProperties toSheetProperties(string fileName, string fileDescription) {
        Manifest::SheetProperties newSheet;

        strcpy(newSheet.name, fileName.c_str());
        strcpy(newSheet.description, fileDescription.c_str());

        newSheet.name[NAME_SIZE - 1] = '\0';
        newSheet.description[DESCRIPTION_SIZE - 1] = '\0';

        return newSheet;
    }

    /**
     * This method convert strings to corresponding properties of sheet (NotesProperties).
     *
     * @param numberOfProperties Size of the vector
     * @param values Vector of strings.
     * @return Sheet::NotesProperties
     */
    Sheet::NotesProperties toNoteProperties(int numberOfProperties, vector<string> values) {
        Sheet::NotesProperties notesProperties;

        notesProperties.numberOfNotes = 0;
        notesProperties.numberOfProperties = numberOfProperties;

        for (int i = 0; i < numberOfProperties; ++i) {
            if (values[i] == "string") {
                notesProperties.values.push_back(Sheet::TypeOfNote::STRING);
            }
            if (values[i] == "double") {
                notesProperties.values.push_back(Sheet::TypeOfNote::DOUBLE);
            }
            if (values[i] == "date") {
                notesProperties.values.push_back(Sheet::TypeOfNote::DATE);
            }
        }

        notesProperties.sizeOfVector = sizeof(Sheet::TypeOfNote) * notesProperties.values.size();

        return notesProperties;
    }

public:
    void lsSheet() {
        manifest.printSheets();
    };

    void addSheet() {
        int numberOfProperties;
        string fileName, fileDescription;
        vector<string> values;

        cout << "Введіть ім'я файлу: ";
        cin >> fileName;
        cin.ignore(32767, '\n'); // удаляем символ новой строки из входного потока данных
        cout << "Введіть опис файлу: ";
        getline(cin, fileDescription);
        cout << "Введіть кількість полів: ";
        cin >> numberOfProperties;
        string type;
        for (int i = 0; i < numberOfProperties; ++i) {
            cout << "Введіть тип " << (i + 1) << " поля: ";
            cin >> type;
            if (type == "string" || type == "double" || type == "date") {
                values.push_back(type);
            }
        }

        manifest.addTable(toSheetProperties(fileName, fileDescription));

        char name[NAME_SIZE];
        strcpy(name, fileName.c_str());
        name[NAME_SIZE - 1] = '\0';
        Sheet::changeSheetProperties(toNoteProperties(numberOfProperties, values), name);
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
                controller.lsSheet();
            } else if (command == "add") {
                controller.addSheet();
            } else if (command == "cd" && userDirectory.size() == 1) {
                char sheetName[NAME_SIZE];
                cin >> sheetName;
                sheetName[NAME_SIZE - 1] = '\0';

                //TODO проверить, со имя существует

                userDirectory.push_back(sheetName);
            } else if (command == "stop") {
                cout << "program is stopped.";
                return;
            } else {
                cout << "command \"" + command + "\" wasn't recognized." << endl;
            }
        } else if (userDirectory.size() == 2) {
            if (command == "ls") {
                //TODO добавить функционал
            } else if (command == "add") {
                //TODO добавить функционал
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
