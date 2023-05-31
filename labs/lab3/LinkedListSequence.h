#pragma once
#include "Sequence.h"

class LinkedListSequence : public Sequence{
private:
    struct Node {
        int value;
        Node* next;
    };
    Node* head;
    Node* tail;
public:
    LinkedListSequence();
    ~LinkedListSequence();

    int get_size();

    int get(int index);
    void set(int index, int value);
    void add(int value);
};

