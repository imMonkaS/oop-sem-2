#pragma once
#include<iostream>
#include "Node.h"
using namespace std;

class MySet
{
private:
    Node* root;
    int size;

    void inorder(Node* n);
    int containsNode(Node* n, int val);
    Node* insert(Node* n, int val);
    void clearingMemory(Node* n);
    void copyAnotherSet(Node* other);
public:
    MySet();
    MySet(const MySet& s);
    MySet& operator=(const MySet& s);
    void add(const int data);
    bool contains(int val);
    int getSize();
    void print(bool brackets = true);
    ~MySet();
};

