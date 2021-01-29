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
    int numberOfTables;
    static const int INT_SIZE = 4;

    void changeNumberOfTables() {
        FILE *fpCopy = fopen("manifest-copy.dat", "w+b");

        numberOfTables++;
        rewind(fpCopy);
        fwrite(&numberOfTables, INT_SIZE, 1, fpCopy);

        fseek(fp, INT_SIZE, SEEK_SET);
        SheetProperties sheet;
        for (int i = 0; i < numberOfTables; ++i) {
            fread(&sheet, SheetProperties::NAME_SIZE + SheetProperties::DESCRIPTION_SIZE, 1, fp);
            fwrite(&sheet, SheetProperties::NAME_SIZE + SheetProperties::DESCRIPTION_SIZE, 1, fpCopy);
        }

        fclose(fp);
        fclose(fpCopy);

        remove(FILE_NAME);
        rename("manifest-copy.dat", FILE_NAME);

        fp = fopen(FILE_NAME, "r+b");
    }

    void addTable(SheetProperties table) {
        fwrite(&table, SheetProperties::NAME_SIZE + SheetProperties::DESCRIPTION_SIZE, 1, fp);
        fflush(fp);
        changeNumberOfTables();
    }

    void addSheet(SheetProperties sheetProperties) {
        string path = "sheets/";
        string str(sheetProperties.name);
        path += str;
        path += ".dat";
        int n = path.length();
        char fileName[n + 1];
        strcpy(fileName, path.c_str());
        fp = fopen(fileName, "w+b");
    }

    void readNumberOfTables() {
        rewind(fp);
        fread(&numberOfTables, INT_SIZE, 1, fp);
    }

    void printString() {

    }

public:
    Manifest() {
        fp = fopen(FILE_NAME, "r+b");
        if (fp == NULL) {
            cout << "Файл \"manifest.dat\" створений заново." << endl;
            fp = fopen(FILE_NAME, "w+b");
            int n = 0;
            fwrite(&n, INT_SIZE, 1, fp);
            fflush(fp);

            remove("sheets");
            std::filesystem::create_directory("sheets");
            //mkdir("sheets", 0777);
        }
        readNumberOfTables();
    }

    vector<SheetProperties> getAllTables() {
        //rewind(fp);
        fp = fopen(FILE_NAME, "r+b");
        fseek(fp, INT_SIZE, SEEK_SET);
        vector<SheetProperties> tables;
        SheetProperties sheet;
        for (int i = 0; i < numberOfTables; ++i) {
            fread(&sheet, SheetProperties::NAME_SIZE + SheetProperties::DESCRIPTION_SIZE, 1, fp);
            tables.push_back(sheet);
        }
        return tables;
    };

    void printAllTables(vector<SheetProperties> tables) {
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

        addTable(newSheet);
        addSheet(newSheet);
    }
};

class Controller {
private:
    Manifest manifest;
    vector<Sheet> sheets;

public:
    void lsSheet() {
        vector<Manifest::SheetProperties> tables = manifest.getAllTables();
        manifest.printAllTables(tables);
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
