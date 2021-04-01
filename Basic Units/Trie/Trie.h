//
// Created by Mark on 01.04.2021.
//

#ifndef INFORMATION_SYSTEM_TRIE_H
#define INFORMATION_SYSTEM_TRIE_H


#include "TrieNode.h"
#include "../SortRequest.h"
#include "../TypeOfNote.h"
#include <vector>
#include <string>

using namespace std;

class Trie {
private:
    TrieNode *root = nullptr;
    vector<SortRequest> sortRequest;
    vector<TypeOfNote> types;

    bool firstIsBigger(vector<string> first, vector<string> second);

    TrieNode *getGrandparent(TrieNode *trieNode);

    TrieNode *getUncle(TrieNode *trieNode);

public:
    Trie();

    Trie(vector<string> rootNodeValue);

    void add(vector<string> newNodeValue);
};


#endif //INFORMATION_SYSTEM_TRIE_H
