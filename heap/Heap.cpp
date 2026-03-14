#include <iostream>
#include <string>
#include <sstream>
#include <time.h>
#include <cmath>
#include <cstdlib>
#include "Dynamic_arr.h"

template<typename T> class BinaryHeap {
private:
    Dynamic_Array<T> bh;

    // (e) heap up
    void heapUp(int i) {
        if (i == 0) {
            return;
        }

        int parent = (i-1) / 2;
        if (bh.get_by_index(parent) < bh.get_by_index(i)) {
            T childData = bh.get_by_index(i);
            T parentData = bh.get_by_index(parent);

            bh.replace_data_i_element(i, parentData);
            bh.replace_data_i_element(parent, childData);

            heapUp(parent);
        }
    }

    // (f) heap down
    void heapDown(int i) {
        int lChild = 2 * i + 1;
        int rChild = 2 * i + 2;

        int parent = i;

        if (lChild < bh.getSize() && bh.get_by_index(parent) < bh.get_by_index(lChild)) {
            parent = lChild;
        }
        if (rChild < bh.getSize() && bh.get_by_index(parent) < bh.get_by_index(rChild)) {
            parent = rChild;
        }

        if (parent != i) {
            T tmp = bh.get_by_index(i);

            bh.replace_data_i_element(i, bh.get_by_index(parent));
            bh.replace_data_i_element(parent, tmp);

            heapDown(parent);
        }
    }

public:

    // (a) dodanie nowego elementu
    void add(T newData) {
        bh.add_at_end(newData);
        heapUp(bh.getSize() - 1);
    }

    // (b) pobranie i usunięcie elementu maksymalnego
    T deleteMax() {
        if (bh.getSize() == 0) {
            throw out_of_range("");
        }

        T max = bh.get_by_index(0);

        if (bh.getSize() == 1) {
            bh.clear();
            return max;
        }

        T last = bh.get_by_index(bh.getSize() - 1);
        bh.replace_data_i_element(0, last);

        bh.removeLast();
        if (bh.getSize() > 0) {
            heapDown(0);
        }

        return max;
    }

    // (c) czyszczenie kopca
    void deleteHeap() {
        bh.clear();
    }

    // (d) zwrócenie napisowej reprezentacji kopca
    string toString() {
        return bh.to_string(10);
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
    const int MAX_ORDER = 7;

    BinaryHeap<some_object>* bh = new BinaryHeap<some_object>();
    for (int o = 1; o <= MAX_ORDER; o++) {
        const int n = pow(10,o );

        clock_t t1 = clock();
        for (int i = 0; i < n; i++) {
            some_object so;
            so.field_1 = ((rand()<<15) + rand()) % 10000000;
            so.field_2 = 'a' + rand() % 26;
            bh->add(so);
        }
        clock_t t2 = clock();

        double addTime = ((t2 - t1) / (double)CLOCKS_PER_SEC) * 1e3;
        cout << "\n\n[" << o << "]--------------------------------------------------------------------------\n";
        cout << "\n- Dodano: " << n
        << "\n- Calkowity czas dodawania: " << addTime
        << " ms / " << addTime * 1e3 << " us"
        << "\n- Sredni czas dodawania: " << (addTime / n)
        << " ms / " << (addTime / n) * 1e3 << " us";
        cout << bh->toString();

        t1 = clock();
        for (int i = 0; i < n; i++) {
            some_object polled = bh->deleteMax();
        }
        t2 = clock();

        double deleteTime = ((t2 - t1) / (double)CLOCKS_PER_SEC) * 1e3;
        cout << "\n\n- Usunieto: " << n
        << "\n- Calkowity czas usuwania: " << deleteTime
        << " ms / " << deleteTime * 1e3 << " us"
        << "\n- Sredni czas usuwania: " << (deleteTime / n)
        << " ms / " << (deleteTime / n) * 1e3 << " us";
        cout << bh->toString();

        bh->deleteHeap();
    }
    delete bh;
    return 0;
}
