//
// Created by Mark on 01.04.2021.
//

#include "Trie.h"

Trie::Trie(istream &fin, ostream &fout) : CSVWorker(fin, fout), Sortable(fin, fout) {
    getProperties(numberOfRecords, names, types);
}

void Trie::sort(vector<SortRequest> sortRequest) {
    this->sortRequest = sortRequest;

    for (int i = 0; i < numberOfRecords; ++i) {
        add(readNext());
    }

    setProperties(names, types);
    DFS(root);
}

void Trie::add(vector<string> newNodeValue) {
    TrieNode *current = root;

    if (root == nullptr) {
        root = new TrieNode(newNodeValue);
        return;
    }

    while (current != nullptr) {
        if (firsIsBigger(newNodeValue, current->getData(), sortRequest, types)) {
            //правый ребёнок
            if (current->getRightChild() != nullptr) {
                current = current->getRightChild();
            } else {
                current->setRightChild(new TrieNode(newNodeValue));
                return;
            }
        } else {
            //левый ребёнок
            if (current->getLeftChild() != nullptr) {
                current = current->getLeftChild();
            } else {
                current->setLeftChild(new TrieNode(newNodeValue));
                return;
            }
        }
    }
}

void Trie::DFS(TrieNode *trieNode) {
    if (trieNode != nullptr) {
        DFS(trieNode->getLeftChild());
        writeNext(trieNode->getData());
        DFS(trieNode->getRightChild());
    }
}
