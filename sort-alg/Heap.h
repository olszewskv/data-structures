#ifndef HEAP_H
#define HEAP_H
using namespace std;

template<typename T> class BinaryHeap {
private:
    T* ex_arr;
    int bh_size;

    void swap(int i1, int i2) {
        T temp = ex_arr[i1];
        ex_arr[i1] = ex_arr[i2];
        ex_arr[i2] = temp;
    }

    void heap_up(int i) {
        while (i > 0) {
            int parent_id = (i - 1) / 2;

            if (ex_arr[parent_id] < ex_arr[i]) {
                swap(i, parent_id);
                i = parent_id;
            }
            else {
                break;
            }
        }
    }

    void heap_down(int i, int current_size) {
        while (true) {
            int largest_id = i;
            int lChild_id = 2 * i + 1;
            int rChild_id = 2 * i + 2;

            if (lChild_id < current_size && ex_arr[largest_id] < ex_arr[lChild_id]) {
                largest_id = lChild_id;
            }

            if (rChild_id < current_size && ex_arr[largest_id] < ex_arr[rChild_id]) {
                largest_id = rChild_id;
            }

            if (largest_id != i) {
                swap(i, largest_id);
                i = largest_id;
            }
            else {
                break;
            }
        }
    }

public:
    BinaryHeap(T* arr, int size, bool bottom_up = true) {
        ex_arr = arr;
        bh_size = size;

        if (bottom_up) {
            for (int i = bh_size / 2 - 1; i >= 0; i--) {
                heap_down(i, size);
            }
        }
        else {
            for (int i = 1; i < size; i++) {
                heap_up(i);
            }
        }
    }

    void HeapSort() {
        for (int i = bh_size - 1; i > 0; i--) {
            swap(0, i);
            heap_down(0, i);
        }
    }

    string to_string() {
        ostringstream os;
        os << "[";
        for (int i = 0; i < bh_size; i++) {
            os << ex_arr[i] << ",";
        }
        os << "]";
        return os.str();
    }

};
#endif //HEAP_H



