#pragma once
#include "Naumov_1.h"

class Naumov_2 : public Naumov_1 {
private:
	float* myFloat;
public:
	void change();
	Naumov_2();
	Naumov_2(const Naumov_2& other);
	Naumov* copy();
	void print();
	~Naumov_2();
};

