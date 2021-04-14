//
// Created by Mark on 01.04.2021.
//

#include "Trie.h"

Trie::Trie(istream &fin, ostream &fout, vector<SortRequest> sortRequest) : CSVWorker(fin, fout) {
    this->sortRequest = sortRequest;
    getProperties(numberOfRecords, names, types);

    for (int i = 0; i < numberOfRecords; ++i) {
        add(readNext());
    }

    setProperties(names, types);
    DFS(root);
}

/*Trie::Trie(vector<string> rootNodeValue) {
    this->root = new TrieNode(rootNodeValue);
}*/

void Trie::add(vector<string> newNodeValue) {
    TrieNode *current = root;

    if (root == nullptr) {
        root = new TrieNode(newNodeValue);
        return;
    }

    while (current != nullptr) {
        if (firstIsBigger(newNodeValue, current->getData())) {
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

bool Trie::firstIsBigger(vector<string> firstRecord, vector<string> secondRecord) {
    int requestSize = sortRequest.size();
    for (int i = 0; i < requestSize; ++i) {
        switch (types[sortRequest[i].ColumnIndex].type) {
            case TypeOfNote::STRING: {
                int compareResult = strcmp(firstRecord[sortRequest[i].ColumnIndex].c_str(),
                                           secondRecord[sortRequest[i].ColumnIndex].c_str());
                if (compareResult > 0) {
                    if (sortRequest[i].order == SortRequest::ASCENDING) {
                        return true;
                    } else if (sortRequest[i].order == SortRequest::DESCENDING) {
                        return false;
                    }
                } else if (compareResult < 0) {
                    if (sortRequest[i].order == SortRequest::ASCENDING) {
                        return false;
                    } else if (sortRequest[i].order == SortRequest::DESCENDING) {
                        return true;
                    }
                }
            }
                break;

            case TypeOfNote::DOUBLE: {
                double value1 = stod(firstRecord[sortRequest[i].ColumnIndex]);
                double value2 = stod(secondRecord[sortRequest[i].ColumnIndex]);
                if (value1 > value2) {
                    if (sortRequest[i].order == SortRequest::ASCENDING) {
                        return true;
                    } else if (sortRequest[i].order == SortRequest::DESCENDING) {
                        return false;
                    }
                } else if (value1 < value2) {
                    if (sortRequest[i].order == SortRequest::ASCENDING) {
                        return false;
                    } else if (sortRequest[i].order == SortRequest::DESCENDING) {
                        return true;
                    }
                }
            }
                break;
        }
    }

    //если они полностью равны, то первый НЕ БОЛЬШЕ второго
    return false;
}

void Trie::DFS(TrieNode *trieNode) {
    if (trieNode != nullptr) {
        DFS(trieNode->getLeftChild());
        writeNext(trieNode->getData());
        DFS(trieNode->getRightChild());
    }
}
