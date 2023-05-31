#pragma once
#include <fstream>
#include <string>
using namespace std;

class StringVector {
    string* words;
    int size;
    int index;

public:
    StringVector(int size = 1);
    StringVector(string filename);
    StringVector(const StringVector& other);
    ~StringVector();

    void print();
    void print(string filename);

    void printIdenticals(const StringVector& other, string outputFile);
    void printUniques(const StringVector& other, string outputFile);
    void printIdenticals(const StringVector& other);
    void printUniques(const StringVector& other);

    void add(string line);
    StringVector& operator=(const StringVector& other);
    friend StringVector operator+(StringVector l1, const StringVector& other);
    StringVector operator+(string word);
    StringVector operator+=(string word);
    friend StringVector operator+(StringVector l1, const StringVector& other);

    friend ostream& operator << (ostream& out, const StringVector& sv);
    friend istream& operator >> (istream& in, StringVector& sv);
};
