#ifndef DYN_ARR_H
#define DYN_ARR_H

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

    std::string to_string_arr() {
        std::ostringstream os;
        os << "\n---------------" <<
            "\nSize = " << size <<
                "\nCapacity = " << capacity <<
                    "\n---------------\n[";
        for (int i = 0; i < size; i++) {
            os << array[i] << ", ";
        }
        os << "]";
        return os.str();
    }
};

struct some_object {
    int field_1;
    char field_2;

    some_object(int f1 = 0, char f2 = ' ') {
        field_1 = f1;
        field_2 = f2;
    }

    bool operator<(const some_object &other) const {
        if (field_1 < other.field_1) {
            return true;
        }
        if (field_1 > other.field_1) {
            return false;
        }
        return field_2 < other.field_2;
    }
};

std::ostream &operator<<(std::ostream &os, const some_object &obj) {
    os << obj.field_1 << obj.field_2;
    return os;
}
#endif //DYN_ARR_H
