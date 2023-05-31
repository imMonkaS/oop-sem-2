#include "Naumov_1.h"
#include <iostream>
using namespace std;

Naumov_1::Naumov_1() {
	myInt = new int(33);
}

Naumov_1::Naumov_1(const Naumov_1& other) {
	myInt = new int(*other.myInt);
}

void Naumov_1::print() {
	cout << "Naumov_1: " << *myInt << endl;
}

void Naumov_1::change() {
	*myInt = 55;
}

Naumov* Naumov_1::copy() {
	return new Naumov_1(*this);
}

Naumov_1::~Naumov_1() {
	delete myInt;
}