#include <iostream>
#include <string>
#include <sstream>
#include <time.h>
#include <cmath>
#include <cstdlib>
using namespace std;

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

    // (a) dodanie nowego elementu na końcu tablicy (argument: dane)
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

        array[size] = data;
        size++;
    }

    // (b) zwrócenie danych i-tego elemetu (argument: indeks i)
    T get_by_index(int i) {
        if (i < 0 || i >= size) {
            throw out_of_range("");
        }

        return array[i];
    }

    // (c) ustawienie i podmiana danych i-tego elementu (argumenty: indeks i oraz nowe dane)
    void replace_data_i_element(int i, T data) {
        if (i < 0 || i >= size) {
            throw out_of_range("");
        }

        array[i] = data;
    }

    // (d) czyszczenie tablicy
    void clear() {
        delete[] array;
        size = 0;
        capacity = 1;
    }

    // (e) zwrócenie napisowej reprezentacji listy
    string to_string() {
        ostringstream os;

        os << "Size = " << size << "\nCapacity = " << capacity << "\n[";
        for (int i = 0; i < size; i++) {
            os << array[i] << ", ";
        }
        os << "]";
        return os.str();
    }

    // (f) sortowanie bąbelkowe
    void bubble_sort() {
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

ostream &operator<<(ostream &os, const some_object &obj) {
    os << obj.field_1 << obj.field_2;
    return os;
}

int main() {
    srand(time(NULL));
    Dynamic_Array<some_object>* da = new Dynamic_Array<some_object>();

    const int order = 7;
    const int n = pow(10, order);

    clock_t t1 = clock();
    double max_time_per_element = 0.0;
    for (int i = 0; i < n; i++) {
        some_object so;
        so.field_1 = rand() % 10001;
        so.field_2 = 'a' + rand() % 26;

        clock_t t1_element = clock();
        da->add_at_end(so);
        clock_t t2_element = clock();

        double time_per_element = ((t2_element - t1_element) / (double)CLOCKS_PER_SEC);

        if (time_per_element > max_time_per_element) {
            max_time_per_element = time_per_element;
            cout << "Nowy maks. czas dodania: " << max_time_per_element * 1e6
            << " us\nindex: " << i << "\n" << endl;
        }
    }
    clock_t t2 = clock();

    double total = ((t2 - t1) / (double)CLOCKS_PER_SEC);

    cout << "\nCzas calkowity: " << total * 1e6 << " us"
    << "\nCzas zamortyzowany: " << (total / n) * 1e6 << " us" << endl;

    cout << da->to_string() << endl;

    da->clear();
    delete da;

    return 0;
}
