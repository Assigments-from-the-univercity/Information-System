//
// Created by Mark on 01.04.2021.
//

#ifndef INFORMATION_SYSTEM_TRIENODE_H
#define INFORMATION_SYSTEM_TRIENODE_H

#include <vector>
#include <string>

using namespace std;

class TrieNode {
private:
    vector<string> data;
    TrieNode *parent = nullptr;
    TrieNode *leftChild = nullptr;
    TrieNode *rightChild = nullptr;

public:
    TrieNode();

    TrieNode(vector<string> noteData);

    TrieNode(vector<string> noteData, TrieNode *parent, TrieNode *leftChild, TrieNode *rightChild);

    vector<string> getData() const;

    void setData(vector<string> data);

    TrieNode *getParent() const {
        return parent;
    }

    void setParent(TrieNode *parent);

    TrieNode *getLeftChild() const {
        return leftChild;
    }

    void setLeftChild(TrieNode *leftChild);

    TrieNode *getRightChild() const {
        return rightChild;
    }

    void setRightChild(TrieNode *rightChild);
};


#endif //INFORMATION_SYSTEM_TRIENODE_H
