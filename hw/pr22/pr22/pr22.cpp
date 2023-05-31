#include <iostream>
#include "Naumov.h"
#include "Naumov_1.h"
#include "Naumov_2.h"
#include "DB.h"

using namespace std;

#include <crtdbg.h>
#define _CRTDBG_MAP_ALLOC

struct Leaks {
	~Leaks() { _CrtDumpMemoryLeaks(); }
}_l;

void printMemoryLeaks()
{
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_ERROR, _CRTDBG_FILE_STDOUT);
	_CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDOUT);
}

void change(DB* db) {
	for (int i = 0; i < (*db).v.size(); i++) {
		(*db).v[i]->change();
	}
}

int main()
{
	printMemoryLeaks();

	DB* db1 = new DB;
	db1->add(new Naumov_1());
	db1->add(new Naumov_2());

	cout << "db1 before change:" << endl;
	db1->print();
	cout << endl;

	change(db1);

	cout << "db1 after change:" << endl;
	db1->print();
	cout << endl;

	DB db2(*db1), db3;
	delete db1;
	db3 = db2;

	cout << "db2 copied db1:" << endl;
	db2.print();
	cout << endl;

	cout << "db3 copied db2 with operator =:" << endl;
	db3.print();

	return 0;
}
