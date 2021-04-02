#include "View Layer/View.h"
#include "Basic Units/Trie/Trie.h"

/**
 * MVC pattern is used in this program for
 * managing the data. (https://ru.wikipedia.org/wiki/Model-View-Controller)
 */
int main() {
    //create Model object to have an accesses to method startWork()
    View view;
    view.startWork();
}
