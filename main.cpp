#include <iostream>
#include <vector>
#include <stack>
#include <cstring>
#include <filesystem>
#include <stack>

using namespace std;

static const int INT_SIZE = 4;

class Sheet {
public:
    enum TypeOfNote {
        STRING,
        DOUBLE,
        DATE
    };

    struct NotesProperties {
        /*static const int PROPERTIES_SIZE = 30;
        static const int VALUES_SIZE = 50;*/

        /*vector<char[PROPERTIES_SIZE]> properties;
        vector<char[VALUES_SIZE]> values;*/

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

class Manifest {
public:
    struct SheetProperties {
        static const int NAME_SIZE = 20;
        static const int DESCRIPTION_SIZE = 100;

        char name[NAME_SIZE];
        char description[DESCRIPTION_SIZE];
    };
private:
    const char *FILE_NAME = "manifest.dat";
    FILE *fp;
    vector<SheetProperties> sheets;

    void createNewFiles(char name[SheetProperties::NAME_SIZE]) {
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

    void refreshManifest() {
        fp = fopen(FILE_NAME, "w+b");
        int n = sizeof(sheets);
        fwrite(&n, INT_SIZE, 1, fp);
        fwrite(&sheets, n, 1, fp);
        fflush(fp);
    }

    void updateData() {
        rewind(fp);
        int size = 0;
        fread(&size, INT_SIZE, 1, fp);
        fread(&sheets, size, 1, fp);
    }

public:
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

    vector<SheetProperties> getSheets() {
        return sheets;
    }

    void printSheets(vector<SheetProperties> tables) {
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

    void addTable(SheetProperties sheetProperties) {
        sheets.push_back(sheetProperties);

        refreshManifest();
        updateData();
        createNewFiles(sheetProperties.name);
    }
};

class Controller {
private:
    Manifest manifest;
    Sheet sheet;

    Manifest::SheetProperties toSheetProperties(string fileName, string fileDescription) {
        Manifest::SheetProperties newSheet;

        strcpy(newSheet.name, fileName.c_str());
        strcpy(newSheet.description, fileDescription.c_str());

        newSheet.name[Manifest::SheetProperties::NAME_SIZE - 1] = '\0';
        newSheet.description[Manifest::SheetProperties::DESCRIPTION_SIZE - 1] = '\0';

        return newSheet;
    }

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
        vector<Manifest::SheetProperties> tables = manifest.getSheets();
        manifest.printSheets(tables);
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

        char name[Manifest::SheetProperties::NAME_SIZE];
        strcpy(name, fileName.c_str());
        name[Manifest::SheetProperties::NAME_SIZE - 1] = '\0';
        Sheet::changeSheetProperties(toNoteProperties(numberOfProperties, values), name);
    }
};

class View {
private:
    Controller controller;
    vector<string> userDirectory;

    void printPath() {
        int size = userDirectory.size();
        for (int i = 0; i < size; ++i) {
            cout << userDirectory[i] << "/";
        }
        cout << "> ";
    }

    void userCommand(string command) {
        if (userDirectory.size() == 1) {
            if (command == "ls") {
                controller.lsSheet();
            } else if (command == "add") {
                controller.addSheet();
            } else if (command == "cd" && userDirectory.size() == 1) {
                char sheetName[Manifest::SheetProperties::NAME_SIZE];
                cin >> sheetName;
                sheetName[Manifest::SheetProperties::NAME_SIZE - 1] = '\0';

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
    View() {
        userDirectory.push_back("home");
    }

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

int main() {
    View model;
    model.startWork();
}
