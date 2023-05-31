// Вариант 17
/*

Усовершенствовать (или разработать) класс «целочисленное множество». Реализовать
множество на основе списка (любого наиболее удобного) таким образом, чтобы
элементы во множестве всегда содержались в порядке возрастания. Реализовать
метод, который проверяет находится ли заданный элемент во множестве. Этот метод
должен быть оптимизирован с помощью алгоритма двоичного поиска.

*/

#include "MySet.h"
#include <iostream>

using namespace std;

int main() {
  MySet a;
  for (int i = 0; i < 6; i++) {
    a.add(i);
  }
  MySet b(a), c;
  c = b;
  cout << "5 in A: " << a.contains(5) << endl;
  cout << "-5 in B: " << b.contains(-5) << endl;
  cout << "1200 in C: " << c.contains(1200) << endl;

  cout << "A: ";
  a.print();
  cout << "B: ";
  b.print();
  cout << "C: ";
  c.print();

  cout << "A inserted using a loop, B copied A, and C copied B with operator ="
       << endl;

  return 0;
}