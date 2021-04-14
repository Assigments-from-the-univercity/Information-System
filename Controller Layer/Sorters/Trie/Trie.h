//
// Created by Mark on 01.04.2021.
//

#ifndef INFORMATION_SYSTEM_TRIE_H
#define INFORMATION_SYSTEM_TRIE_H


#include <vector>
#include <string>
#include <cstring>
#include "TrieNode.h"
#include "../../../Basic Units/Sort Request/SortRequest.h"
#include "../../../Basic Units/TypeOfNote.h"
#include "../../../CSV Workers/CSVWorker.h"

using namespace std;

class Trie : public CSVWorker {
private:
    TrieNode *root = nullptr;

    int numberOfRecords;
    vector<string> names;
    vector<SortRequest> sortRequest;
    vector<TypeOfNote> types;

    bool firstIsBigger(vector<string> firstRecord, vector<string> secondRecord);

    TrieNode *getGrandparent(TrieNode *trieNode);

    TrieNode *getUncle(TrieNode *trieNode);

public:
    Trie(istream &fin, ostream &fout, vector<SortRequest> sortRequest);

    //Trie(vector<string> rootNodeValue);

    void add(vector<string> newNodeValue);

    void DFS(TrieNode *trieNode);
};


#endif //INFORMATION_SYSTEM_TRIE_H
