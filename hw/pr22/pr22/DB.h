#pragma once
#include <vector>
#include "Naumov.h"

using namespace std;

class DB{
private:
	vector<Naumov*> v;
public:
	DB();
	~DB();
	void add(Naumov* obj);
	void print();
	DB(const DB& other);
	DB& operator=(const DB& other);

	friend void change(DB* db);
};

