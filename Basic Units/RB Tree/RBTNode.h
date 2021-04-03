//
// Created by Mark on 03.04.2021.
//

#ifndef INFORMATION_SYSTEM_RBTNODE_H
#define INFORMATION_SYSTEM_RBTNODE_H

#include <vector>
#include <string>

using namespace std;

class RBTNode {
public:
    enum Colour {
        BLACK,
        RED
    };

private:
    vector<string> data;
    RBTNode *parent = nullptr;
    RBTNode *leftChild = nullptr;
    RBTNode *rightChild = nullptr;
    Colour colour = Colour::RED;

public:
    RBTNode();

    RBTNode(const vector<string> &data);

    const vector<string> &getData() const;

    void setData(const vector<string> &data);

    RBTNode *getParent() const;

    void setParent(RBTNode *parent);

    RBTNode *getLeftChild() const;

    void setLeftChild(RBTNode *leftChild);

    RBTNode *getRightChild() const;

    void setRightChild(RBTNode *rightChild);

    Colour getColour() const;

    void setColour(Colour colour);
};


#endif //INFORMATION_SYSTEM_RBTNODE_H
