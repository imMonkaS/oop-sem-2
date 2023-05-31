#include "MySet.h"
#include "Node.h"
#include<iostream>
using namespace std;

// cout nodes to console
void MySet::inorder(Node* n)
{
    if (n == NULL) {
        return;
    }
    inorder(n->left);
    cout << n->value << " ";
    inorder(n->right);
}

// Binary Tree search
int MySet::containsNode(Node* n, int val)
{
    if (n == NULL) {
        return 0;
    }
    // checking if we found our value
    int x = n->value == val ? 1 : 0;
    // check all left and right nodes
    return x | containsNode(n->left, val) | containsNode(n->right, val);
}

// insert node with value
Node* MySet::insert(Node* n, int val)
{
    if (n == NULL) {
        Node* tmp = new Node;
        tmp->value = val;
        tmp->left = tmp->right = NULL;
        return tmp;
    }

    if (val < n->value) {
        n->left = insert(n->left, val);
        return n;
    }
    else if (val > n->value) {
        n->right = insert(n->right, val);
        return n;
    }
    else
        return n;
}

void MySet::clearingMemory(Node* n)
{
    if (n == NULL) {
        return;
    }
    clearingMemory(n->left);
    clearingMemory(n->right);
    delete n;
}

void MySet::copyAnotherSet(Node* other) {
    if (other == NULL) {
        return;
    }

    copyAnotherSet(other->left);
    root = insert(root, other->value);
    copyAnotherSet(other->right);
}





MySet::MySet() {
    root = NULL;
    size = 0;
}

MySet::MySet(const MySet& s)
{
    copyAnotherSet(s.root);
    size = s.size;
}

MySet& MySet::operator=(const MySet& s)
{
    if (this == &s)
        return *this;

    clearingMemory(root);

    copyAnotherSet(s.root);
    size = s.size;

    return *this;
}

// if value is not in set, add that value to the set
void MySet::add(const int data) {
    if (!containsNode(root, data)) {
        root = insert(root, data);
        size++;
    }
}

bool MySet::contains(int val)
{
    return containsNode(root, val) ? true : false;
}

int MySet::getSize()
{
    return size;
}

void MySet::print(bool brackets)
{
    if (brackets)
        cout << "{ ";
    inorder(root);
    if (brackets)
        cout << "}";
    cout << endl;
}

MySet::~MySet()
{
    clearingMemory(root);
}
