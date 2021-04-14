//
// Created by Mark on 03.04.2021.
//

#include "RBTNode.h"

RBTNode::RBTNode() {}

RBTNode::RBTNode(const vector<string> &data) : data(data) {}

const vector<string> &RBTNode::getData() const {
    return data;
}

void RBTNode::setData(const vector<string> &data) {
    RBTNode::data = data;
}

RBTNode *RBTNode::getParent() const {
    return parent;
}

void RBTNode::setParent(RBTNode *parent) {
    RBTNode::parent = parent;
}

RBTNode *RBTNode::getLeftChild() const {
    return leftChild;
}

void RBTNode::setLeftChild(RBTNode *leftChild) {
    RBTNode::leftChild = leftChild;
}

RBTNode *RBTNode::getRightChild() const {
    return rightChild;
}

void RBTNode::setRightChild(RBTNode *rightChild) {
    RBTNode::rightChild = rightChild;
}

RBTNode::Colour RBTNode::getColour() const {
    return colour;
}

void RBTNode::setColour(RBTNode::Colour colour) {
    RBTNode::colour = colour;
}
