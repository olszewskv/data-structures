#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <iostream>
#include <string>
#include <sstream>

template<typename T> class Dynamic_Array {
private:
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

    void add_at_end(T data) {
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

        size++;
        array[size] = data;
    }

    T get_by_index(int i) {
        if (i < 0 || i >= size) {
            throw std::out_of_range("");
        }
        return array[i];
    }

    void replace_data_i_element(int i, T data) {
        if (i < 0 || i >= size) {
            throw std::out_of_range("");
        }
        array[i] = data;
    }

    void clear() {
        delete[] array;
        array = new T[1];
        size = 0;
        capacity = 1;
    }

    std::string to_string() {
        std::ostringstream os;
        os << "\n---------------" <<
            "Size = " << size <<
                "\nCapacity = " << capacity <<
                    "\n---------------\n[";
        for (int i = 0; i < size; i++) {
            os << array[i] << ", ";
        }
        os << "]";
        return os.str();
    }
};

#endif //DYNAMIC_ARRAY_H
