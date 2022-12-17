#pragma once
#include <iostream>

struct Node {
    int data = 0;
    Node *next;
    Node(int a)
    {
        data = a;
        next = nullptr;
    }
};

class List 
{
private:
    Node *first;
    Node *last;

public:

    List() : first(nullptr), last(nullptr) {};

    ~List();

    bool is_include(int n);

    void addNode(int n); // добавляет узел к концу существующего списка

    bool is_empty();

    void printLinkedList();// отображает содержимое списка в консоль

    void deleteElement(int n);

};

