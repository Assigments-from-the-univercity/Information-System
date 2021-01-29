#include <iostream>
#include <vector>
#include <stack>
#include <cstring>

using namespace std;

class Sheet {
public:
    class Note {
        static const int PROPERTIES_SIZE = 30;
        static const int VALUES_SIZE = 50;

        vector <char[PROPERTIES_SIZE]> properties;
        vector <char[VALUES_SIZE]> values;
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

    void createPath(char sheetName[], char *fileName){
        char *beg = "/sheets/";
        char *end = ".dat";
        int i = 0;
        for (; i < 8; ++i) {
            fileName[i] = beg[i];
        }
        int size = strlen(sheetName);
        for (int j = 0; i < size + 8; ++i) {
            fileName[i] = sheetName[j];
            j++;
        }
        for (int j = 0; i < size + 12; ++i) {
            fileName[i] = end[j];
            j++;
        }
        fileName[i] = '\0';
    }

    void addSheet(SheetProperties sheetProperties){
        char fileName[13 + strlen(sheetProperties.name)];
        createPath(sheetProperties.name, fileName);
        string str(sheetProperties.name);
        str += ".dat";
        fp = fopen(fileName, "w+b");
    }

    void readNumberOfTables() {
        rewind(fp);
        fread(&numberOfTables, INT_SIZE, 1, fp);
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
        }
        readNumberOfTables();
    }

    vector<SheetProperties> getAllTables() {
        //rewind(fp);
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

        int size = SheetProperties::NAME_SIZE - 1;
        if (fileName.size() < size) {
            size = fileName.size();
        }
        for (int i = 0; i < size; ++i) {
            newSheet.name[i] = fileName[i];
        }
        newSheet.name[size] = '\0';

        size = SheetProperties::DESCRIPTION_SIZE - 1;
        if (fileName.size() < size) size = fileDescription.size();
        for (int i = 0; i < size; ++i) {
            newSheet.description[i] = fileDescription[i];
        }
        newSheet.description[size] = '\0';

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
