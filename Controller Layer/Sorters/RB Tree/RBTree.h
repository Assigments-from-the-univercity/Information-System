//
// Created by Mark on 03.04.2021.
//

#ifndef INFORMATION_SYSTEM_RBTREE_H
#define INFORMATION_SYSTEM_RBTREE_H


#include <vector>
#include <string>
#include <cstring>
#include "RBTNode.h"
#include "../../../Basic Units/Sort Request/SortRequest.h"
#include "../../../Basic Units/TypeOfNote.h"
#include "../../../CSV Workers/CSVWorker.h"
#include "../Sortable.h"

using namespace std;

class RBTree : public CSVWorker, public Sortable {
private:
    RBTNode *root = nullptr;

    int numberOfRecords;
    vector<string> names;
    vector<SortRequest> sortRequest;
    vector<TypeOfNote> types;

    RBTNode *getGrandparent(RBTNode *rbtNode);

    RBTNode *getUncle(RBTNode *rbtNode);

    void rotate(RBTNode *trieNode);

    void insertCase1(RBTNode *trieNode);

    void insertCase2(RBTNode *trieNode);

    void insertCase3(RBTNode *trieNode);

    void insertCase4(RBTNode *trieNode);

    void insertCase5(RBTNode *trieNode);

    void add(vector<string> newNodeValue);

    void DFS(RBTNode *rbtNode);

public:
    RBTree(istream &fin, ostream &fout);

    void sort(vector<SortRequest> sortRequest);
};


#endif //INFORMATION_SYSTEM_RBTREE_H
