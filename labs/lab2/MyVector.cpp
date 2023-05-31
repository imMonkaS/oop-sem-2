#include "MyVector.h"

#include <iostream>

using namespace std;

bool MyVector::binary_search(const int* data, const int value) {
    int l = 0;
    int r = size;
    while (l <= r) {
        int c = (l + r) / 2;
        if (value > data[c]) {
            l = c + 1;
        }
        if (value < data[c]) {
            r = c - 1;
        }
        if (value == data[c]) {
            return true;
        }
    }
    return false;
}

MyVector::MyVector() {
    data = new int[0];
    this->size = 0;
}

MyVector::MyVector(int size) {
    data = new int[size];
    this->size = size;
}

MyVector::MyVector(const MyVector& v2) {
    data = new int[v2.size];
    this->size = v2.size;
    for (int i = 0; i < v2.size; i++) {
        data[i] = v2.data[i];
    }
}

int MyVector::get_size() {
    return size;
}

MyVector& MyVector::operator=(const MyVector& v2)
{
    if (this == &v2)
        return *this;
    delete[] data;

    data = new int[v2.size];
    this->size = v2.size;
    for (int i = 0; i < v2.size; i++) {
        data[i] = v2.data[i];
    }
    return *this;
}

void MyVector::bubble_sort(int* data, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size - 1; j++) {
            if (data[j] > data[j + 1]) {
                int b = data[j];
                data[j] = data[j + 1];
                data[j + 1] = b;
            }
        }
    }
}

void MyVector::append(const int value) {
    int* tmp = new int[size];
    for (int i = 0; i < size; i++) {
        tmp[i] = data[i];
    }
    delete[] data;
    data = new int[size + 1];
    for (int i = 0; i < size; i++) {
        data[i] = tmp[i];
    }
    size++;
    delete[] tmp;
    data[size - 1] = value;
}

void MyVector::print() {
    for (int i = 0; i < size; i++) {
        cout << data[i] << " ";
    }
    cout << endl;
}

bool MyVector::search(int value) {
    int* tmp = new int[size];
    for (int i = 0; i < size; i++) {
        tmp[i] = data[i];
    }

    bubble_sort(tmp, size);

    if (binary_search(tmp, value)) {
        return true;
    }
    delete[] tmp;
    return false;
}

MyVector::~MyVector() {
    delete[] data;
}

int MyVector::operator [](int i) const {
    return data[i];
}

int& MyVector::operator [](int i) {
    return data[i];
}


// Новые функции
ostream& operator<<(ostream& out, const MyVector& myV) {
    for (int i = 0; i < myV.size; i++) {
        cout << myV.data[i] << " ";
    }
    cout << endl;
    return out;
}

MyVector MyVector::operator+(const int val) {
    MyVector v = *this;
    v.append(val);
    return v;
}

MyVector& MyVector::operator+=(const MyVector& v2) {
    *this = *this + v2;
    return *this;
}

MyVector& MyVector::operator+=(const int val) {
    *this = *this + val;
    return *this;
}

MyVector operator+(MyVector v1, const MyVector& v2) {
    MyVector v;
    for (int i = 0; i < v1.size; i++) {
        v.append(v1[i]);
    }
    for (int i = 0; i < v2.size; i++) {
        v.append(v2[i]);
    }
    return v;
}

MyVector operator-(MyVector v1, MyVector v2) {
    MyVector v;
    for (int i = 0; i < v1.size; i++) {
        if (!v2.search(v1[i])) v.append(v1[i]);
    }
    return v;
}

MyVector& MyVector::operator-=(const MyVector& v2) {
    *this = *this - v2;
    return *this;
}

MyVector operator*(MyVector v1, const MyVector& v2) {
    MyVector v;
    for (int i = 0; i < v1.size; i++) {
        for (int j = 0; j < v2.size; j++) {
            v.append(v1[i] * v2[j]);
        }
    }
    return v;
}

MyVector& MyVector::operator*=(const MyVector& v2) {
    *this = *this * v2;
    return *this;
}

bool operator==(MyVector v1, const MyVector& v2) {
    if (v1.size == v2.size) {
        for (int i = 0; i < v1.size; i++) {
            if (v1[i] != v2[i]) return false;
        }
        return true;
    }
    return false;
}

bool operator!=(MyVector v1, const MyVector& v2) {
    return !(v1 == v2);
}
