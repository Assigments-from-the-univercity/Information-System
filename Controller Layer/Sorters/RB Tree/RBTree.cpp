//
// Created by Mark on 03.04.2021.
//

#include "RBTree.h"

RBTNode *RBTree::getGrandparent(RBTNode *rbtNode) {
    if (rbtNode != nullptr && rbtNode->getParent() != nullptr) {
        return rbtNode->getParent()->getParent();
    } else {
        return nullptr;
    }
}

RBTNode *RBTree::getUncle(RBTNode *rbtNode) {
    RBTNode *grandparent = getGrandparent(rbtNode);
    if (grandparent == nullptr)
        return nullptr; // No grandparent means no uncle
    if (rbtNode->getParent() == grandparent->getLeftChild())
        return grandparent->getRightChild();
    else
        return grandparent->getLeftChild();
}

void RBTree::rotate(RBTNode *rbtNode) {
    RBTNode *grandparent = getGrandparent(rbtNode);
    RBTNode *uncle = getUncle(rbtNode);
    RBTNode *pivot = new RBTNode();
    pivot->setColour(RBTNode::BLACK);

    if (uncle != nullptr) {
        uncle->setParent(pivot);
    }
    if (grandparent->getRightChild() == uncle) {
        pivot->setRightChild(uncle);
        grandparent->setRightChild(pivot);
    } else {
        pivot->setLeftChild(uncle);
        grandparent->setLeftChild(pivot);
    }

    pivot->setData(grandparent->getData());
    grandparent->setData(rbtNode->getParent()->getData());
    rbtNode->getParent()->setData(rbtNode->getData());

    rbtNode->getParent()->setLeftChild(nullptr);
    rbtNode->getParent()->setRightChild(nullptr);

    delete rbtNode;
}

RBTree::RBTree(istream &fin, ostream &fout) : CSVWorker(fin, fout), Sortable(fin, fout) {
    getProperties(numberOfRecords, names, types);
}

void RBTree::sort(vector<SortRequest> sortRequest) {
    this->sortRequest = sortRequest;

    for (int i = 0; i < numberOfRecords; ++i) {
        add(readNext());
    }

    setProperties(names, types);
    DFS(root);
}

void RBTree::add(vector<string> newNodeValue) {
    RBTNode *current = root;

    if (root == nullptr) {
        root = new RBTNode(newNodeValue);
        insertCase1(root);
        return;
    }

    while (current != nullptr) {
        if (firsIsBigger(newNodeValue, current->getData(), sortRequest, types)) {
            //правый ребёнок
            if (current->getRightChild() != nullptr) {
                current = current->getRightChild();
            } else {
                RBTNode *newNode = new RBTNode(newNodeValue);
                current->setRightChild(newNode);
                newNode->setParent(current);
                insertCase1(newNode);
                return;
            }
        } else {
            //левый ребёнок
            if (current->getLeftChild() != nullptr) {
                current = current->getLeftChild();
            } else {
                RBTNode *newNode = new RBTNode(newNodeValue);
                current->setLeftChild(newNode);
                newNode->setParent(current);
                insertCase1(newNode);
                return;
            }
        }
    }
}

void RBTree::DFS(RBTNode *rbtNode) {
    if (rbtNode != nullptr) {
        DFS(rbtNode->getLeftChild());
        writeNext(rbtNode->getData());
        DFS(rbtNode->getRightChild());
    }
}

void RBTree::insertCase1(RBTNode *trieNode) {
    if (trieNode->getParent() == nullptr) {
        trieNode->setColour(RBTNode::BLACK);
    } else {
        insertCase2(trieNode);
    }
}

void RBTree::insertCase2(RBTNode *trieNode) {
    if (trieNode->getParent()->getColour() == RBTNode::BLACK) {
        return;
    } else {
        insertCase3(trieNode);
    }
}

void RBTree::insertCase3(RBTNode *trieNode) {
    RBTNode *uncle = getUncle(trieNode);

    if (uncle != nullptr && uncle->getColour() == RBTNode::RED) {
        trieNode->getParent()->setColour(RBTNode::BLACK);
        uncle->setColour(RBTNode::BLACK);
        RBTNode *grandparent = getGrandparent(trieNode);
        grandparent->setColour(RBTNode::RED);
        insertCase1(grandparent);
    } else {
        insertCase4(trieNode);
    }
}

void RBTree::insertCase4(RBTNode *trieNode) {
    RBTNode *grandparent = getGrandparent(trieNode);

    if (trieNode->getParent()->getRightChild() && trieNode->getParent() == grandparent->getLeftChild()) {
        RBTNode *savedNote = grandparent->getLeftChild();
        grandparent->setLeftChild(trieNode);
        trieNode->setLeftChild(savedNote);
        trieNode->setParent(grandparent);
        savedNote->setRightChild(nullptr);
        savedNote->setParent(trieNode);

        trieNode = trieNode->getLeftChild();
    } else if (trieNode->getParent()->getLeftChild() && trieNode->getParent() == grandparent->getRightChild()) {
        RBTNode *savedNote = grandparent->getRightChild();
        grandparent->setRightChild(trieNode);
        trieNode->setRightChild(savedNote);
        trieNode->setParent(grandparent);
        savedNote->setLeftChild(nullptr);
        savedNote->setParent(trieNode);

        trieNode = trieNode->getRightChild();
    }
    insertCase5(trieNode);
}

void RBTree::insertCase5(RBTNode *trieNode) {
    rotate(trieNode);
}
