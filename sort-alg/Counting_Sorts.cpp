#include <iostream>
#include <string>
#include <sstream>
#include <time.h>
#include <cmath>
#include <cstdlib>
#include "Heap.h"
using namespace std;

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

void CountingSort(int* arr, int n, int m) {

    int* count_arr = new int[m]();

    for (int i = 0; i < n; i++) {
        if (arr[i] < 0 || arr[i] >= m) {
            delete count_arr;
            throw out_of_range("Wartosc " + to_string(arr[i]) +
                               " poza zakresem [0, " + to_string(m-1) + "]");
        }
         count_arr[arr[i]]++;
    }

    int i = 0;
    for (int j = 0; j < m; j++) {
        for (int k = 0; k < count_arr[j]; k++) {
            arr[i] = j;
            i++;
        }
    }
    delete count_arr;
}


void bucket_sort_ints (int* arr, int n, int m) {
    if (n <= 1) {
        return;
    }

    int b = n;

    int **buckets = new int *[b];
    int *bucket_size = new int[b]();

    for (int i = 0; i < b; i++) {
        buckets[i] = new int[n];
    }

    for (int i = 0; i < n; i++) {
        int x = arr[i];
        if (arr[i] < 0 || arr[i] >= m) {
            throw out_of_range("");
        }

        int bucket_id = (x * b) / m;
        if (bucket_id >= b) {
            bucket_id = b - 1;
        }

        buckets[bucket_id][bucket_size[bucket_id]++] = x;
    }

    int id = 0;

    for (int i = 0; i < b; i++) {
        if (bucket_size[i] > 1) {
            CountingSort(buckets[i], bucket_size[i], m);
        }

        for (int j = 0; j < bucket_size[i]; j++) {
            arr[id++] = buckets[i][j];
        }
    }

    for (int i = 0; i < b; i++) {
        delete[] buckets[i];
    }
    
    delete[] buckets;
    delete[] bucket_size;
}

// ints
int main() {
    int arr1[] = {15, 10, 8, 30, 16, 20, 25};
    int arr2[] = {15, 10, 8, 30, 16, 20, 25};
    int arr3[] = {15, 10, 8, 30, 16, 20, 25};

    BinaryHeap<int> heap(arr1, 7, true);

    heap.HeapSort();
    cout << heap.to_string();

    printf("\n\n\n");

    CountingSort(arr2, 7, 31);
    for (int i = 0; i < 7; i++) {
        cout << arr2[i] << " ";
    }
    cout << endl;

    printf("\n\n\n");
    bucket_sort_ints(arr3, 7, 31);
    for (int i = 0; i < 7; i++) {
        cout << arr3[i] << " ";
    }
    cout << endl;

    return 0;
}

// objects
int main_ob() {
    some_object arr1[] = {
        some_object(15, 'a'),
        some_object(10, 'b'),
        some_object(8, 'c'),
        some_object(30, 'd'),
        some_object(16, 'e'),
        some_object(20, 'f'),
        some_object(50, 'g'),
    };

    for (int i = 0; i < 7; i++) {
        cout << arr1[i] << " ";
    }
    cout << endl;

    BinaryHeap<some_object> heap(arr1, 7, true);
    cout << heap.to_string() << endl;

    heap.HeapSort();
    cout << heap.to_string() << endl;

    return 0;
}