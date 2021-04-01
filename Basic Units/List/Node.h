//
// Created by Mark on 23.02.2021.
//

#ifndef INFORMATION_SYSTEM_NODE_H
#define INFORMATION_SYSTEM_NODE_H


class Node {
private:
    char value;
    Node *next;
public:
    Node();

    Node(char value);

    char getValue();

    void setValue(char value);

    Node * getNext();

    void setNext(Node *next);

    void set(char value, Node *next);
};


#endif //INFORMATION_SYSTEM_NODE_H
