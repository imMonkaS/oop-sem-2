#include "DynamicArraySequence.h"


DynamicArraySequence::DynamicArraySequence(int size) {
    data = new int[size];
    if (size < 1) this->memorySize = 1;
    else this->memorySize = size;
    actualSize = 0;
}

DynamicArraySequence::~DynamicArraySequence() {
    delete[] data;
}

int DynamicArraySequence::get(int index) {
    return data[index];
}

int DynamicArraySequence::get_size() {
    return actualSize;
}

void DynamicArraySequence::set(int index, int value) {
    data[index] = value;
}

void DynamicArraySequence::add(int value) {
    if ((memorySize - 1) == actualSize) {
        int* tmp = new int[memorySize];
        for (int i = 0; i < memorySize; i++) {
            tmp[i] = data[i];
        }
        delete[] data;
        data = new int[memorySize * 2];
        for (int i = 0; i < memorySize; i++) {
            data[i] = tmp[i];
        }
        for (int i = memorySize; i < memorySize * 2; i++) {
            data[i] = 0;
        }
        memorySize *= 2;
        delete[] tmp;
    }
    data[actualSize] = value;
    actualSize++;
}
