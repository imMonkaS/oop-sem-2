#pragma once

#include <iostream>
using namespace std;

class MyVector {
private:
    int* data;
    int size;

    bool binary_search(const int* data, const int value);
public:
    MyVector();
    MyVector(int size);

    MyVector(const MyVector& v2);

    int get_size();

    MyVector& operator=(const MyVector& v2);

    void bubble_sort(int* data, int size);

    void append(const int value);

    void print();

    bool search(int value);

    ~MyVector();

    int operator [](int i) const;

    int& operator [](int i);

    // Новые функции
    friend ostream& operator<<(ostream& out, const MyVector& myV);

    MyVector operator+(const int val);
    MyVector& operator+=(const int val);

    friend MyVector operator+(MyVector v1, const MyVector& v2);
    MyVector& operator+=(const MyVector& v2);

    friend MyVector operator-(MyVector v1, MyVector v2);
    MyVector& operator-=(const MyVector& v2);

    // умножение просто перемножает попарно элементы множества
    friend MyVector operator*(MyVector v1, const MyVector& v2);
    MyVector& operator*=(const MyVector& v2);

    friend bool operator==(MyVector v1, const MyVector& v2);
    friend bool operator!=(MyVector v1, const MyVector& v2);
};