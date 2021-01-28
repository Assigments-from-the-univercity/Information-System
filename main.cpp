#include <iostream>
#include <vector>
#include <stack>

using namespace std;

class Note {

};

class Sheet {
private:
    string name;

public:
};

class Manifest {
public:
    struct SheetProperties {
        string name;
        string description;
    };
private:
    const char *FILE_NAME = "manifest.dat";
    FILE *fp;
    int numberOfTables;

    void changeNumberOfTables() {
        FILE *fpCopy = fopen("manifest-copy.dat", "w+b");

        numberOfTables++;
        rewind(fpCopy);
        fwrite(&numberOfTables, sizeof(int), 1, fpCopy);

        fseek(fp, sizeof(int), SEEK_SET);
        SheetProperties sheet;
        for (int i = 0; i < numberOfTables; ++i) {
            fread(&sheet, sizeof sheet, 1, fp);
            fwrite(&sheet, sizeof sheet, 1, fpCopy);
        }

        fclose(fp);
        fclose(fpCopy);

        remove(FILE_NAME);
        rename("manifest-copy.dat", FILE_NAME);

        fp = fopen(FILE_NAME, "r+b");   //TODO этот метод не работает правильно!
        /*SheetProperties sheet1;
        sheet1.name = ".";
        sheet1.description = "..";
        fread(&sheet, sizeof sheet, 1, fp);
        cout << sheet1.name;*/
    }

    void addTable(SheetProperties table) {
        fwrite(&table, sizeof table, 1, fp);
        fflush(fp);
        changeNumberOfTables();
    }

    void readNumberOfTables() {
        rewind(fp);
        fread(&numberOfTables, sizeof(int), 1, fp);
    }

public:
    Manifest() {
        fp = fopen(FILE_NAME, "r+b");
        if (fp == NULL) {
            cout << "Файл \"manifest.dat\" створений заново." << endl;
            fp = fopen(FILE_NAME, "w+b");
            int n = 0;
            fwrite(&n, sizeof(int), 1, fp);
            fflush(fp);
        }
        readNumberOfTables();
    }

    vector<SheetProperties> getAllTables() {
        rewind(fp);
        vector<SheetProperties> tables;
        SheetProperties sheet;
        for (int i = 0; i < numberOfTables; ++i) {
            fread(&sheet, sizeof sheet, 1, fp);
            tables.push_back(sheet);
        }
        return tables;
    };

    void printAllTables(vector<SheetProperties> tables) {
        int size = tables.size();
        cout << "список доступних таблиць:" << endl;
        for (int i = 0; i < size; i++) {
            cout << "Ім'я: " << tables[i].name << "Опис: " << tables[i].description << endl;
        }
        if (size == 0) {
            cout << "немає доступних таблиць." << endl;
        }
        cout << "hint: use \"cd <name of table>\" to go to the table." << endl;
    }

    void addTable(string fileName, string fileDescription) {
        SheetProperties newSheet;
        newSheet.name = fileName;
        newSheet.description = fileDescription;
        addTable(newSheet);
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
