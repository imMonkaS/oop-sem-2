// Вариант 17
/*

Разработать программу для упрощения работы со множествами целых чисел. На данном
этапе разрешается реализовывать множества на основе динамического массива.
Использовать встроенные стандартные множества для реализации запрещается.
Реализовать:
a. функцию добавления значений ко множеству;
b. функцию, которая проверяет находится ли заданный элемент во множестве;
c. функцию инициализации одного множества другим.
Решая задачу в рамках ООП, необходимо составить класс для представления такого
множества. Усложнение (+4 балла). В случае реализации через массивы
оптимизировать поиск по множеству с помощью алгоритма двоичного поиска. Связка
(до +10 баллов). Если какой-либо студент из вашей группы (или смежной)
воспользуется вашим классом или классами для решения своей задачи, вы получите
доп. баллы. Польза от использования должна быть логически обоснована, а не
добавлена “ради галочки”.

*/

#include <iostream>

using namespace std;

template <typename T> class MyVector {
private:
    T* data;
    int size;

    bool binary_search(const T* data, const T value) {
        int l = 0;
        int r = size;
        while (l <= r) {
            int c = (l + r) / 2;
            if (value > data[c]) {
                l = c + 1;
            }
            if (value < data[c]) {
                r = c - 1;
            }
            if (value == data[c]) {
                return true;
            }
        }
        return false;
    }

public:
    MyVector(int size = 0) {
        data = new T[size];
        this->size = size;
    }

    MyVector(const MyVector& v2) {
        data = new T[v2.size];
        this->size = v2.size;
        for (int i = 0; i < v2.size; i++) {
            data[i] = v2.data[i];
        }
    }

    int get_size() { return size; }

    MyVector& operator=(const MyVector& v2) {
        if (this == &v2)
            return *this;
        delete[] data;

        data = new T[v2.size];
        this->size = v2.size;
        for (int i = 0; i < v2.size; i++) {
            data[i] = v2.data[i];
        }
        return *this;
    }

    void bubble_sort(T* data, int size) {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size - 1; j++) {
                if (data[j] > data[j + 1]) {
                    int b = data[j];
                    data[j] = data[j + 1];
                    data[j + 1] = b;
                }
            }
        }
    }

    void append(const T value) {
        T* tmp = new T[size];
        for (int i = 0; i < size; i++) {
            tmp[i] = data[i];
        }
        delete[] data;
        data = new T[size + 1];
        for (int i = 0; i < size; i++) {
            data[i] = tmp[i];
        }
        size++;
        delete[] tmp;
        data[size - 1] = value;
    }

    void print() {
        for (int i = 0; i < size; i++) {
            cout << data[i] << " ";
        }
        cout << endl;
    }

    bool search(T value) {
        T* tmp = new T[size];
        for (int i = 0; i < size; i++) {
            tmp[i] = data[i];
        }

        bubble_sort(tmp, size);

        if (binary_search(tmp, value)) {
            return true;
        }
        delete[] tmp;
        return false;
    }

    ~MyVector() { delete[] data; }

    T operator[](int i) const { return data[i]; }

    T& operator[](int i) { return data[i]; }
};

int main() {
    srand(time(NULL));
    MyVector<int> mv;
    for (int i = 0; i < 20; i++) {
        mv.append(rand() % 200 - 100);
    }

    MyVector<int> mv2 = mv;
    mv2.print();
    for (int i = 0; i < 30; i += 3)
        if (mv2.search(i)) {
            cout << i << " is in vector" << endl;
        }
    mv2[3] = 5;
    cout << "Fourth element now equals " << mv2[3]
        << " because I changed it with overloaded brackets" << endl;
    mv2.print();

    return 0;
}