// Вариант 17
/*

Усовершенствовать (или разработать) класс «множество строк». Разработать
программу, которая сравнивает два файла по выбору пользователя и: a. выводит или
записывает в другой файл все слова/строки, которые есть и в первом и во втором
файлах; b. выводит или записывает в другой файл все слова/строки, которые есть в
первом/втором файле, но которых нет во втором/первом файле.

*/

#include "StringVector.h"
#include <iostream>
using namespace std;

int main() {
  StringVector f("file1.txt");
  StringVector s("file2.txt");

  f.printIdenticals(s, "identicals.txt");
  f.printUniques(s, "uniques.txt");

  StringVector f1(f);
  StringVector f2;
  f2 = f1;
  StringVector f3 = f1 + f2;
  f1.print("copyConstructor.txt");
  f2.print("copyOperator.txt");
  f3.print("plusOperator.txt");

  // operator+,+=,>>,<< overload
  StringVector f4;
  cin >> f4;
  f4 += "asdagfwq";
  cout << f4;

  return 0;
}
