//
// Created by Mark on 23.02.2021.
//

#include "Node.h"

Node::Node() {
    value = '\0';
    next = nullptr;
}

Node::Node(char value) {
    this->value = value;
    next = nullptr;
}

char Node::getValue() {
    return value;
}

void Node::setValue(char value) {
    this->value = value;
}

void Node::setNext(Node *next) {
    this->next = next;
}

void Node::set(char value, Node *next) {
    this->value = value;
    this->next = next;
}

Node *Node::getNext() {
    return next;
}