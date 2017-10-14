//
// Created by melany on 20/09/17.
//

#ifndef REMOTE_MEMORY_NODE_H
#define REMOTE_MEMORY_NODE_H


#include <iostream>

using namespace std;



class Node
{
public:
    Node();
    Node(char * key_,int data_,  int value_size_);
    ~Node();

    Node *next;
    int data;
    char * key;
    int value_size;

    void delete_all();
    void print();
};


#endif //REMOTE_MEMORY_NODE_H
