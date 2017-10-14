//
// Created by melany on 20/09/17.
//

#ifndef REMOTE_MEMORY_LIST_H
#define REMOTE_MEMORY_LIST_H


#include <fstream>
#include <iostream>
#include <string>
#include <stdlib.h>

#include "node.cpp"

using namespace std;



class List
{
public:
    List();
    ~List();

    void add_head();
    void add_end(char*, int,  int);
    void add_sort();
    void del_by_data(int);
    void del_by_position(int);
    void print();
    void search(int);
    void sort();

private:
    Node *m_head;
    int m_num_nodes;
};


#endif //REMOTE_MEMORY_LIST_H
