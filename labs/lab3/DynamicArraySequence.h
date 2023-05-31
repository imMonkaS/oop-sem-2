#pragma once
#include "Sequence.h"

class DynamicArraySequence : public Sequence{
private:
    int* data;
    int memorySize;
    int actualSize;
public:
    DynamicArraySequence(int size = 1);
    ~DynamicArraySequence();

    int get_size();

    int get(int index);
    void set(int index, int value);
    void add(int value);
};

