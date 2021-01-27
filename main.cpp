#include <iostream>
#include <vector>

using namespace std;

class Status {
public:
    struct Table {
        string name;
        string description;
    };

private:
    const char *FILE_NAME = "manage-file.dat";
    FILE *fp;
    const int numberOfTables = 0;

    vector<Table> getAllTables() {
        rewind(fp);
        vector<Table> tables;
        Table table;
        for (int i = 0; i < numberOfTables; ++i) {
            fread(&table, sizeof table, 1, fp);
            tables.push_back(table);
        }
        return tables;
    };

    void printAllTables(vector<Table> tables) {
        int size = tables.size();
        cout << "список доступних таблиць:" << endl;
        for (int i = 0; i < size; i++) {
            cout << "Ім'я: " << tables[i].name << "Опис: " << tables[i].description << endl;
        }
        if (size == 0) {
            cout << "немає доступних таблиць." << endl;
        }
        cout << "hint: press \"cd <name of table>\" to go to the table." << endl;
    }

    void putTable(Table table) {
        fwrite(&table, sizeof table, 1, fp);
    }

public:
    Status() {
        fp = fopen(FILE_NAME, "r+b");
        if (fp == NULL) {
            cout << "файл заново створений.";
            fp = fopen(FILE_NAME, "w+b");
        }
    }

    void ls() {
        vector<Table> tables = getAllTables();
        printAllTables(tables);
    };
};

int main() {
    string str;
    Status status;
    cout << "Щоб завершити роботу введіть \"end work\"" << endl;
    do {
        cin >> str;
        if (str == "ls") {
            status.ls();
        } else if (str == "end work") {
            cout << "program is stopped.";
            return 0;
        }
        else {
            cout << "command \"" + str + "\" wasn't recognized." << endl;
        }
    } while (str != "end work");
}
