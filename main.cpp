#include "View Layer/View.h"
#include "DAT Workers/DATWriter.h"
#include "DAT Workers/DATReader.h"

//Testing


/**
 * MVC pattern is used in this program for
 * managing the data. (https://ru.wikipedia.org/wiki/Model-View-Controller)
 */
int main() {
    //create Model object to have an accesses to method startWork()
    //View model;
    //model.startWork();

    /*
    string name = "test.dat";
    //CSVWorker fileWorker(name, "Data\\");
    TablePropertiesWorker tablePropertiesWorker("test");
    vector<TypeOfNote> types;
    vector<List> names;
    TypeOfNote typeOfNote;
    List list;

    typeOfNote.type = TypeOfNote::DOUBLE;
    types.push_back(typeOfNote);
    typeOfNote.type = TypeOfNote::STRING;
    types.push_back(typeOfNote);
    typeOfNote.type = TypeOfNote::DOUBLE;
    types.push_back(typeOfNote);

    list.put("id11");
    names.push_back(list);
    list.put("name365");
    names.push_back(list);
    list.put("age34");
    names.push_back(list);

    tablePropertiesWorker.setProperties(4, 3, types, names);

    int n1, n2;
    vector<TypeOfNote> types1;
    vector<List> names2;

    tablePropertiesWorker.getProperties(n1, n2, types1, names2);

    cout << n1 << " " << n2 << " " << names[0].get();
     */

    /// DAT WORKERS TESTING
    FILE *fp = fopen("tables\\test-1.dat", "w+b");

    vector<string> names;
    vector<TypeOfNote> types;

    names.push_back("id11");
    names.push_back("name365");
    names.push_back("age34");

    TypeOfNote typeOfNote;
    typeOfNote.type = TypeOfNote::DOUBLE;
    types.push_back(typeOfNote);
    typeOfNote.type = TypeOfNote::STRING;
    types.push_back(typeOfNote);
    typeOfNote.type = TypeOfNote::DOUBLE;
    types.push_back(typeOfNote);

    DATWriter datWriter(fp, names, types);

    rewind(fp);
    DATReader datReader(fp);

    int numberOfRecords;
    names.clear();
    types.clear();

    datReader.getProperties(numberOfRecords, names, types);

    cout << numberOfRecords << endl;
}
