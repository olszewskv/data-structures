#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <iostream>
#include <string>
#include <sstream>
using namespace std;

template<typename T> class Dynamic_Array {
    T* array;
    int size;
    int capacity;

public:
    Dynamic_Array() {
        array = new T[1];
        size = 0;
        capacity = 1;
    }

    ~Dynamic_Array() {
        delete[] array;
    }

    void add_at_end_arr(T data) {
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

    T get_by_index_arr(int i) {
        if (i < 0 || i >= size) {
            throw std::out_of_range("dd");
        }
        return array[i];
    }

    void replace_data_i_element_arr(int i, T data) {
        if (i < 0 || i >= size) {
            throw std::out_of_range("ddd");
        }
        array[i] = data;
    }

    void clear_arr() {
        delete[] array;
        array = new T[1];
        size = 0;
        capacity = 1;
    }

    int getSize_arr() {
        return size;
    }

    void remove_last_arr() {
        if (size > 0) {
            size--;
        }
    }

    void swap(int i1, int i2) {
        T temp = get_by_index_arr(i1);
        replace_data_i_element_arr(i1, get_by_index_arr(i2));
        replace_data_i_element_arr(i2, temp);
    }

    void heap_down(Dynamic_Array<T>& arr, int size, int i) {
        int largest_id = i;
        int lChild_id = 2 * i + 1;
        int rChild_id = 2 * i + 2;

        if (lChild_id < size && arr.get_by_index_arr(largest_id) < arr.get_by_index_arr(lChild_id)) {
            largest_id = lChild_id;
        }
        if (rChild_id < size && arr.get_by_index_arr(largest_id) < arr.get_by_index_arr(rChild_id)) {
            largest_id = rChild_id;
        }
        if (largest_id != i) {
            arr.swap(i, largest_id);
            heap_down(arr, size, largest_id);
        }
    }

    void HeapSort(Dynamic_Array<T>& arr) {
        int heap_size = arr.getSize_arr();

        for (int i = heap_size / 2 - 1; i >= 0; i--) {
            heap_down(arr, heap_size, i);
        }

        for (int i = heap_size - 1; i > 0; i--) {
            arr.swap(0 , i);
            heap_down(arr, i, 0);
        }
    }
};
#endif //DYNAMIC_ARRAY_H
