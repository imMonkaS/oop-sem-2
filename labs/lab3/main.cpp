// Вариант 17
/*

Создать абстрактный класс «последовательность» с абстрактными функциями
получения значения произвольного элемента, установки значения произвольного
элемента, добавления элемента в конец последовательности. Создать реализации
класса «последовательность» на основе динамического массива и на основе
односвязного списка.

*/

#include "DynamicArraySequence.h"
#include "LinkedListSequence.h"
#include "Sequence.h"
#include <iostream>

using namespace std;

int main() {
  Sequence *dynamicArr = new DynamicArraySequence(0);
  Sequence *listArr = new LinkedListSequence();

  // Using add
  for (int i = 1; i <= 20; i++) {
    (*dynamicArr).add(i);
    (*listArr).add(i);
  }

  // Using set
  (*dynamicArr).set(4, 12354);
  (*listArr).set(5, 3425);

  // Using get
  for (int i = 0; i < (*dynamicArr).get_size(); i++) {
    cout << (*dynamicArr).get(i) << " ";
  }

  cout << endl;

  for (int i = 0; i < (*listArr).get_size(); i++) {
    cout << (*listArr).get(i) << " ";
  }

  delete dynamicArr;
  delete listArr;

  return 0;
}