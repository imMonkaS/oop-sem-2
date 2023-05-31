// Вариант 17
/*

Усовершенствовать программу для упрощения работы со множествами целых чисел.
Реализовать:
a. функцию потокового вывода множества для консоли (операция <<);
b. перегруженную операцию присваивания с множеством;
c. функцию сложения (ИЛИ) двух множеств в одно, используя перегруженную операцию +;
d. функцию умножения (И) двух множеств в одно, используя перегруженную операцию *;
e. функцию вычитания одного множества из другого, которая возвращает все элементы первого множества,
которых нет во втором, используя перегруженную операцию -;
f. перегруженную функцию сложения множества с целым для добавления числа во множество;
Усложнение #1 (+4 балла). Реализовать функции сложения (ИЛИ), умножения (И) и вычитания двух множеств,
используя перегруженные операции += , *= и -= соответственно (не вместо, а в дополнение к основным).
Усложнение #2 (+3 балла). Реализовать перегруженную операцию сравнения с другим множеством;

*/

#include <iostream>
#include "MyVector.h"

using namespace std;

int main()
{
    MyVector mv1;
    for (int i = 0; i < 5; i++) {
        mv1.append(i + 1);
    }
    cout << "mv1 Created and printed with overloaded <<:" << endl << mv1 << endl;

    MyVector mv2(mv1);
    cout << "Initialized mv2 with mv1: " << endl << mv2 << endl;
    for (int i = 0; i < 5; i++) {
        mv2[i] += 10;
    }
    cout << "increased mv2 to make the following examples more clear: " << endl << mv2 << endl;

    MyVector mv3 = mv1 + mv2;
    mv3 += mv1;
    cout << "Initialized mv3 as mv1 + mv2 and then added all mv1 number to mv3 using +=:" << endl << mv3 << endl;

    mv3 = mv3 + 666;
    mv3 += 777;
    mv3 = mv3 - mv2;
    mv3 -= mv1;
    cout << "Added 666 as int to mv3 using + and 777 using += and deleted all mv2 numbers from mv3 using - and all mv1 numbers using -=:" << endl << mv3 << endl;

    MyVector mv4, mv5;
    mv4 += 1;
    mv4 += 2;
    mv4 += 3;
    mv5 += 4;
    mv5 += 5;
    mv4 = mv4 * mv5;
    mv5 *= mv4;
    cout << "mv4(1,2,3), mv5(4,5) mv4 * mv5:" << endl << mv4 << "mv5 *= mv4:" << endl << mv5 << endl;

    mv5 = mv4;
    if (mv4 == mv5)
        cout << "Comparing mv4 and mv5. Result: equal" << endl;
    else if (mv4 != mv5)
        cout << "Comparing mv4 and mv5. Result: You would've seen this text if they were not equal" << endl;
    mv4[0] = 78;
    if (mv4 == mv5)
        cout << "Comparing mv4 and mv5. Result: You would've seen this text if they were equal" << endl;
    else if (mv4 != mv5)
        cout << "Comparing mv4 and mv5. Result: not equal" << endl;
    mv4[0] += 67; // демонстрация что при сравнении векторов разных длинн ошибки не будет
    if (mv4 == mv5)
        cout << "Comparing mv4 and mv5. Result: You would've seen this text if they were equal" << endl;
    else if (mv4 != mv5)
        cout << "Comparing mv4 and mv5. Result: not equal" << endl;


    return 0;
}