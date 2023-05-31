#include "DB.h"

DB::DB() {

}

DB::~DB() {
	for (int i = 0; i < v.size(); i++) {
		delete v[i];
	}
	v.clear();
}

DB::DB(const DB& other) {
	for (int i = 0; i < other.v.size(); i++)
		add(other.v[i]->copy());
}

void DB::print() {
	for (int i = 0; i < v.size(); i++) {
		v[i]->print();
	}
}

DB& DB::operator=(const DB& other) {
	if (this == &other)
		return *this;

	for (int i = 0; i < v.size(); i++)
		delete v[i];
	v.clear();

	for (int i = 0; i < other.v.size(); i++)
		add(other.v[i]->copy());
}

void DB::add(Naumov* obj) {
	v.push_back(obj);
}
