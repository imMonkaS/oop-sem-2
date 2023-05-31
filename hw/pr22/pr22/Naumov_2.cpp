#include "Naumov_2.h"
#include <iostream>
using namespace std;

Naumov_2::Naumov_2() {
	myFloat = new float(0.001);
}

Naumov_2::Naumov_2(const Naumov_2& other) {
	myFloat = new float(*other.myFloat);
}

void Naumov_2::print() {
	cout << "Naumov_2: " << *myInt << " and " << *myFloat << endl;
}

Naumov* Naumov_2::copy() {
	return new Naumov_2(*this);
}

void Naumov_2::change() { }

Naumov_2::~Naumov_2() {
	delete myFloat;
}