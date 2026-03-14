#ifndef DYNAMIC_ARR_H
#define DYNAMIC_ARR_H

#include <iostream>
#include <string>
#include <sstream>
using namespace std;

template<typename T>
class Dynamic_Array {
private:
    T *array;
    int size;
    int capacity;

public:
    Dynamic_Array();

    ~Dynamic_Array();

    void add_at_end(T data);

    T get_by_index(int i);

    void replace_data_i_element(int i, T data);

    void clear();

    string to_string(int max);

    void bubble_sort();

    int getSize() {
        return size;
    }

    void removeLast();
};

template<typename T>
Dynamic_Array<T>::Dynamic_Array() {
    array = new T[1];
    size = 0;
    capacity = 1;
}

template<typename T>
Dynamic_Array<T>::~Dynamic_Array() {
    delete[] array;
}

template<typename T>
void Dynamic_Array<T>::add_at_end(T data) {
    if (size >= capacity) {
        int new_capacity = capacity * 2;
        T* new_array = new T[new_capacity];

        for (int i = 0; i < size; i++) {
            new_array[i] = array[i];
        }
        delete[] array;

        array = new_array;
        capacity = new_capacity;
    }
    array[size] = data;
    size++;
}

template<typename T>
T Dynamic_Array<T>::get_by_index(int i) {
    if (i < 0 || i >= size) {
        throw out_of_range("");
    }
    return array[i];
}

template<typename T>
void Dynamic_Array<T>::replace_data_i_element(int i, T data) {
    if (i < 0 || i >= size) {
        throw out_of_range("");
    }
    array[i] = data;
}

template<typename T>
void Dynamic_Array<T>::clear() {
    delete[] array;
    array = new T[1];
    size = 0;
    capacity = 1;
}

template<typename T>
string Dynamic_Array<T>::to_string(int max) {
    ostringstream os;

    os << "\n\nSize = " << size << "\n[";
    for (int i = 0; i < size && i < max; i++) {
        os << array[i] << ", ";
    }
    os << "]\n";
    return os.str();
}

template<typename T>
void Dynamic_Array<T>::bubble_sort() {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (array[j + 1] < array[j]) {
                T tmp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = tmp;
            }
        }
    }
}

template<typename T>
void Dynamic_Array<T>::removeLast() {
    if (size > 0) {
        size--;
    }
}

#endif //DYNAMIC_ARR_H
