//
// Created by Mark on 01.04.2021.
//

#include "TrieNode.h"

TrieNode::TrieNode() {

}

TrieNode::TrieNode(vector<string> noteData) {
    this->data = noteData;
}

TrieNode::TrieNode(vector<string> noteData, TrieNode *parent, TrieNode *leftChild, TrieNode *rightChild) {
    this->data = noteData;
    this->parent = parent;
    this->leftChild = leftChild;
    this->rightChild = rightChild;
}


vector<string> TrieNode::getData() const {
    return data;
}

void TrieNode::setData(vector<string> data) {
    TrieNode::data = data;
}

void TrieNode::setParent(TrieNode *parent) {
    TrieNode::parent = parent;
}

void TrieNode::setLeftChild(TrieNode *leftChild) {
    TrieNode::leftChild = leftChild;
}

void TrieNode::setRightChild(TrieNode *rightChild) {
    TrieNode::rightChild = rightChild;
}