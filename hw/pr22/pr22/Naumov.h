#pragma once

class Naumov {
public:
	virtual void print() = 0;
	virtual Naumov* copy() = 0;
	virtual void change() = 0;
	virtual ~Naumov() { };
};
