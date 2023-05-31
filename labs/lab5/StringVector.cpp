#include "StringVector.h"
#include <fstream>
#include <string>
#include <iostream>
using namespace std;

StringVector::StringVector(int size) {
    words = new string[size];
    this->size = size;
    index = 0;
}

StringVector::~StringVector() {
    delete[] words;
}

StringVector::StringVector(string filename) {
    size = 1;
    words = new string[size];
    this->size = size;
    index = 0;

    ifstream file(filename);
    while (file.good() && file.is_open()) {
        string tmp;
        file >> tmp;
        add(tmp);
    }
}

StringVector::StringVector(const StringVector& other) {
    words = new string[other.size];
    this->size = other.size;
    index = other.index;

    for (int i = 0; i < other.size; i++) {
        words[i] = other.words[i];
    }
}

StringVector& StringVector::operator=(const StringVector& other) {
    if (this == &other) return *this;

    delete[] words;

    words = new string[other.size];
    this->size = other.size;
    index = other.index;

    for (int i = 0; i < other.size; i++) {
        words[i] = other.words[i];
    }

    return *this;
}

void StringVector::add(string line) {
    if ((size - 1) == index) {
        string* tmp = new string[size];
        for (int i = 0; i < size; i++) {
            tmp[i] = words[i];
        }
        delete[] words;
        words = new string[size * 2];
        for (int i = 0; i < size; i++) {
            words[i] = tmp[i];
        }
        size *= 2;
        delete[] tmp;
    }
    words[index] = line;
    index++;
}

void StringVector::print() {
    for (int i = 0; i < size; i++) {
        cout << words[i] << endl;
    }
}

void StringVector::print(string filename) {
    ofstream output(filename);
    for (int i = 0; i < size; i++) {
        output << words[i] << endl;
    }
}

void StringVector::printIdenticals(const StringVector& other, string outputFile) {
    ofstream output(outputFile);
    for (int i = 0; i < index; i++) {
        for (int j = 0; j < other.index; j++) {
            if (words[i] == other.words[j]) {
                output << words[i] << endl;
            }
        }
    }
}

void StringVector::printUniques(const StringVector& other, string outputFile) {
    ofstream output(outputFile);
    for (int i = 0; i < index; i++) {
        bool flag = true;
        for (int j = 0; j < other.index; j++) {
            if (words[i] == other.words[j]) {
                flag = false;
            }
        }
        if (flag) {
            output << words[i] << endl;
        }
    }
}

void StringVector::printIdenticals(const StringVector& other) {
    for (int i = 0; i < index; i++) {
        for (int j = 0; j < other.index; j++) {
            if (words[i] == other.words[j]) {
                cout << words[i] << endl;
            }
        }
    }
}

void StringVector::printUniques(const StringVector& other) {
    for (int i = 0; i < index; i++) {
        bool flag = true;
        for (int j = 0; j < other.index; j++) {
            if (words[i] == other.words[j]) {
                flag = false;
            }
        }
        if (flag) {
            cout << words[i] << endl;
        }
    }
}

StringVector operator+(StringVector l1, const StringVector& other) {
    for (int i = 0; i < other.size; i++) {
        l1.add(other.words[i]);
    }
    return l1;
}

StringVector StringVector::operator+(string word) {
    add(word);
    return *this;
}

StringVector StringVector::operator+=(string word) {
    *this = *this + word;
    return *this;
}

ostream& operator << (ostream& out, const StringVector& sv) {
    for (int i = 0; i < sv.size; i++) {
        out << sv.words[i] << endl;
    }
    return out;
}

istream& operator >> (istream& in, StringVector& sv) {
    string tmp;
    getline(in, tmp);
    string word = "";
    for (int i = 0; i < tmp.size(); i++) {
        if (tmp[i] == ' ' || tmp[i] == tmp.size() - 1) {
            sv.add(word);
            word = "";
        }
        else {
            word += tmp[i];
        }
    }
    return in;
}
