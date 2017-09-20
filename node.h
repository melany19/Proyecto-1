//
// Created by melany on 20/09/17.
//

#ifndef REMOTE_MEMORY_NODE_H
#define REMOTE_MEMORY_NODE_H


#include <iostream>

using namespace std;

template <class T>

class Node
{
public:
    Node();
    Node(T);
    ~Node();

    Node *next;
    T data;

    void delete_all();
    void print();
};


#endif //REMOTE_MEMORY_NODE_H
