//
// Created by Mark on 23.02.2021.
//

#include "Header.h"
#include "List.h"

void List::add(char value) {
    Node *current = &begin;
    while (current->getNext() != nullptr) {
        current = current->getNext(); //доходим до конца списка
    }
    Node *last = new Node(value);
    current->setNext(last);
}

List::List() {
    //begin.setValue(0);
}

List::List(char value) {
    begin.setValue(value);
}

int List::numberOfElements() {
    Node *current = &begin;
    int size = 0;
    while (current) {
        size++;
        current = current->getNext();
    }
    return size;
}

void List::copy(List list) {
    Node *currentTo = &begin;
    Node *currentFrom = &(list.begin);

    currentTo->setValue(currentFrom->getValue());
    currentTo->setNext(nullptr);

    while (currentFrom->getNext()) {
        Node *last = new Node();
        (*currentTo).setNext(last);

        currentTo = currentTo->getNext();
        currentFrom = currentFrom->getNext();

        currentTo->setValue(currentFrom->getValue());
    }
}

bool List::isInList(char value) {
    Node *current = &begin;
    while (current) {
        if (current->getValue() == value) {
            return true;
        }
        current = current->getNext();
    }
    return false;
}

bool List::isEqual(List list) {
    Node *currentThis = &begin;
    Node *currentList = &(list.begin);

    if (this->size() != list.size()) {
        return false;
    }

    while (currentThis) {
        if (currentThis->getValue() != currentList->getValue()) {
            return false;
        }

        currentThis = currentThis->getNext();
        currentList = currentList->getNext();
    }

    return true;
}

bool List::isContains(List list) {
    /*Node *currentThis = &begin;

    while (currentThis) {
        if (!(list.isInList(currentThis->getValue()))) {
            return false;
        }

        currentThis = currentThis->getNext();
    }

    return true;*/
}

void List::change(int order, char newValue) {
    Node *current = &begin;
    while (current && order > 0) {
        current = current->getNext();
        order--;
    }
    if (current) {
        current->setValue(newValue);
    }
}

void List::del(int order) {
    if (order == 0) {
        begin = *begin.getNext();
        return;
    }

    Node *current = &begin;
    Node *prev;

    while (current && order > 1) {
        current = current->getNext();
        order--;
    }
    if (!current) {
        return;
    }

    prev = current;
    current = current->getNext();
    if (current->getNext() == nullptr) {
        delete current;
        prev->setNext(nullptr);
        return;
    }

    prev->setNext(current->getNext());

    delete current;
}