#pragma once
#include "Naumov.h"

class Naumov_1 : public Naumov {
protected:
	int* myInt;
public:
	Naumov_1();
	void change();
	Naumov_1(const Naumov_1& other);
	Naumov* copy();
	void print();
	~Naumov_1();
};
