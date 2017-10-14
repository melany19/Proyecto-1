//
// Created by melany on 20/09/17.
//

#include "node.h"


// Constructor por defecto

Node ::Node()
{
    data = NULL;
    next = NULL;
    key = NULL;
    value_size = 0;
}

// Constructor por parámetro

Node ::Node(char * key_,int data_,int value_size_)
{
    data = data_;
    key= key_;
    value_size = value_size_;
    next = NULL;
}

// Eliminar todos los Nodos

void Node::delete_all()
{
    if (next)
        next->delete_all();
    delete this;
}

// Imprimir un Nodo

void Node::print()
{
    //cout << "Node-> " << "Dato: " << dato << " Direcion: " << this << " Siguiente: " << next << endl;
    cout << data << "-> ";
}


Node::~Node() {}
