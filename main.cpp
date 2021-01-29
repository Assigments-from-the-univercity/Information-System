#include <iostream>
#include <vector>
#include <stack>
#include <cstring>
#include <filesystem>

using namespace std;

class Sheet {
public:
    class Note {
        static const int PROPERTIES_SIZE = 30;
        static const int VALUES_SIZE = 50;

        vector<char[PROPERTIES_SIZE]> properties;
        vector<char[VALUES_SIZE]> values;
    };

private:
    string name;
    //TODO add more propert.

public:
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
    static const int INT_SIZE = 4;

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

    void addTable(string fileName, string fileDescription) {
        SheetProperties newSheet;

        strcpy(newSheet.name, fileName.c_str());
        strcpy(newSheet.description, fileDescription.c_str());

        newSheet.name[SheetProperties::NAME_SIZE - 1] = '\0';
        newSheet.description[SheetProperties::DESCRIPTION_SIZE - 1] = '\0';

        sheets.push_back(newSheet);

        refreshManifest();
        createNewFiles(newSheet.name);
    }
};

class Controller {
private:
    Manifest manifest;
    vector<Sheet> sheets;

public:
    void lsSheet() {
        vector<Manifest::SheetProperties> tables = manifest.getSheets();
        manifest.printSheets(tables);
    };

    void addSheet() {
        string fileName, fileDescription;
        cout << "Введіть ім'я файлу: ";
        cin >> fileName;
        cin.ignore(32767, '\n'); // удаляем символ новой строки из входного потока данных
        cout << "Введіть опис файлу: ";
        getline(cin, fileDescription);
        manifest.addTable(fileName, fileDescription);
    }
};

class View {
private:
    Controller controller;
    stack<string> userDirectory;

    void printPath() {
        int size = userDirectory.size();
        for (int i = 0; i < size; ++i) {
            cout << userDirectory.top() << "/";
        }
        cout << "> ";
    }

    void userCommand(string command) {
        if (userDirectory.size() == 1) {
            if (command == "ls") {
                controller.lsSheet();
            } else if (command == "add") {
                controller.addSheet();
            } else if (command == "stop") {
                cout << "program is stopped.";
                return;
            } else {
                cout << "command \"" + command + "\" wasn't recognized." << endl;
            }
        } else if (userDirectory.size() == 2) {
            //TODO work with sheets
        } else {
            cout << "ERROR! You are in wrong directory!" << endl;
        }
    }

public:
    View() {
        userDirectory.push("home");
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
