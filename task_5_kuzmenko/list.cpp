#include <iostream>
#include "list.h"

List::~List() {
    Node* p = first;
    Node* pt = first;
    while (p != nullptr) {
        pt = pt -> next;
        delete p;
        p = pt;
    }
}

bool List::is_empty() {
    return first == nullptr;
};

void List::addNode(int n)
{
    Node* p = new Node(n);

    if (is_empty()) {
        first = p;
        last = p;
        return;
    }
    else 
    {
        last->next = p;
        last = p;
        return;
    };

}

bool List::is_include(int n) {

    if (is_empty()) {
        return false;
    }

    Node* p = first;
    
    while (p != nullptr) {
        if (p->data == n)
            return true;
        p = p->next;
    }
    return false;
}

void List::printLinkedList()
{
    Node* p = first;
    while (p != nullptr) {
        std::cout << p->data << " ";
        p = p->next;
    }
    std::cout << std::endl;
}

void List::deleteElement(int n) 
{  
    while (is_include(n)) {
        if (first->data == n) {
            Node *p = first;
            first = p->next;
            delete p;
            continue;
        }

        if (last->data == n) {
            if (first == last) {
                Node *p = first;
                first = p->next;
                delete p;
                continue;
            }

            Node *p = first;
            while (p->next != last) {
                p = p->next;
            }
            p->next = nullptr;
            delete last;
            last = p;
            continue;
        }

        Node *prev = first;
        Node *now = prev->next;

        while (now != nullptr && now->data != n) {
            prev = prev->next;
            now = now->next;
        }
        /*if (now == nullptr) {
            std::cout << "Element does not exist" << std::endl;
            return;
        }*/

        prev->next = now->next;
        delete now;
    }
    if (is_empty()) {
        std::cout << "Linked list is empty" << std::endl;
        return;
    }
    return;
}

