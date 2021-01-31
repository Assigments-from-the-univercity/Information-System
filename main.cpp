#include <iostream>
#include <vector>
#include <stack>
#include <cstring>
#include <filesystem>
#include <stack>

#include <cstdio>
#include <cstdlib>
#include <cstring>

using namespace std;

static const int INT_SIZE = 4;
static const int NAME_SIZE = 20;
static const int DESCRIPTION_SIZE = 100;

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
        char name[NAME_SIZE];
        char description[DESCRIPTION_SIZE];
    };
private:
    const char *FILE_NAME = "manifest.dat";
    FILE *fp;
    vector<SheetProperties> sheets;

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

        newSheet.name[NAME_SIZE - 1] = '\0';
        newSheet.description[DESCRIPTION_SIZE - 1] = '\0';

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

/*
    struct SheetProperties {
        char name[NAME_SIZE];
        char description[DESCRIPTION_SIZE];
    };
    vector<SheetProperties> sheets;
    vector<SheetProperties> sheets1;
    cout << sizeof sheets << endl;
    cout << sizeof(sheets) << endl;

    SheetProperties sheet;
    SheetProperties sheet1;
    sheet.name[0] = 'n';
    sheet.name[1] = '\0';
    sheet.description[0] = 't';
    sheet.description[1] = '\0';
    sheets.push_back(sheet);

    cout << sizeof sheets << endl;
    cout << sizeof(sheets) << endl;

    cout << endl;

    cout << sizeof(sheet) << endl;
    cout << sizeof(sheet.name) << endl;
    cout << sizeof() << endl;

    FILE *fp = fopen("in.dat", "w+b");
    //FILE *fp = fopen("in.dat", "r+b");
    fwrite(&sheets, 200, 1, fp);
    fflush(fp);
    rewind(fp);
    fread(&sheets1, 200, 1, fp);
    cout << sheets1[0].name << " " << sheets1[0].description;*/
/*
    FILE *fo;
    if ((fo = fopen("data4.dat", "r+b")) == NULL){
        cout << "Error open output file" << endl;
        return 1;}
    const int dl = 80;
    char s[80];
    struct Mon {
        char type[20];

        char comm[30];
    };
    Mon mon;
    mon.type[0] = 't';
    mon.type[1] = '\0';
    mon.comm[0] = 'm';
    mon.comm[1] = '\0';
    cout << sizeof mon << endl << mon.type << endl;
    vector <Mon> mons;
    vector <Mon> mons1;
    cout << sizeof mons << endl;
    mons.push_back(mon);
    cout << sizeof mons << endl;
    fwrite(&mons, sizeof mons, 1, fo);
    fflush(fo);
    //Mon mon1;
    rewind(fo);
    fread(&mons1, sizeof mons, 1, fo);
    cout << mons1[0].type;*/
    /*
    int kol = 0;  //ê³ëüê³ñòü çàïèñ³â ó ôàéë³
    while (kol < 1){
        strncpy(mon.type, s, 19);
        mon.type[19] = '\0';
        mon.opt = atof(&s[20]);
        mon.rozn = atof(&s[30]);
        strncpy(mon.comm, &s[40], 30);
        fwrite(&mon, sizeof mon, 1, fo);
        kol++;
    }
    int i;
    cin >> i;
    if (i >= kol){
        cout << "Not exist"; return 1;}
    fseek(fo, (sizeof mon)*i, SEEK_SET);
    fread(&mon, sizeof mon, 1, fo);
    cout << "mon.type " << mon.type << " opt " << mon.opt
         << " rozn " << mon.rozn << endl;

    fclose(fo);
    cin.get();
    return 0;*/
}
