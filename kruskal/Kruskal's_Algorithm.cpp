// ALGO2 IS1 210B LAB08
// Szymon Olszewski
// os57850@zut.edu.pl

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <cmath>
//#include "Dynamic_Array.h"
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

struct Node{
    float x;
    float y;
};

struct Edge {
    int u;
    int v;
    float weight;

    bool operator <(const Edge &other) const {
        return weight < other.weight;
    }
};

struct Graph {
    int n;
    int e;
    Node *nodes;
    Dynamic_Array<Edge> edges;
};

struct UnionFind {
    int *parent;
    int *rank;
    int n;
    int find_count;

    UnionFind(int n) {
        parent = new int[n];
        rank = new int[n];
        find_count = 0;

        for (int i = 0; i < n; i++) {
            parent[i] = i;
            rank[i] = 0;
        }
    }

    ~UnionFind() {
        delete[] parent;
        delete[] rank;
    }

    int Find(int i) {
        find_count++;
        if (i == parent[i]) {
            return i;
        }
        return Find(parent[i]);
    }

    void Union(int i, int j) {
        int i_root = Find(i);
        int j_root = Find(j);

        if (i_root != j_root) {
            parent[j_root] = i_root;
        }
    }

    int find_by_compression(int i) {
        find_count++;
        if (i == parent[i]) {
            return i;
        }
        int root = find_by_compression(parent[i]);
        if (root != parent[i]) {
            parent[i] = root;
        }
        return root;
    }

    void union_by_rank(int i, int j) {
        int i_root = find_by_compression(i);
        int j_root = find_by_compression(j);

        if (rank[i_root] < rank[j_root]) {
            parent[i_root] = j_root;
        }
        else if (rank[j_root] < rank[i_root]) {
            parent[j_root] = i_root;
        }
        else {
            parent[i_root] = j_root;
            rank[j_root]++;
        }
    }

    int getFindCount() {
        return find_count;
    }
};

void sort(Dynamic_Array<Edge>& arr) {
    arr.HeapSort(arr);
}

Dynamic_Array<Edge> Kruskal(Graph &graph, int &find_op) {
    Dynamic_Array<Edge> MST;
    UnionFind uf(graph.n);

    for (int i = 0; i < graph.edges.getSize_arr(); i++) {
        Edge e = graph.edges.get_by_index_arr(i);

        int root_u = uf.find_by_compression(e.u);
        int root_v = uf.find_by_compression(e.v);

        if (root_u != root_v) {
            MST.add_at_end_arr(e);
            uf.union_by_rank(root_u, root_v);
        }

        if (MST.getSize_arr() == graph.n - 1) {
            break;
        }
    }
    find_op = uf.getFindCount();
    return MST;
}

Graph load_file(const string& filename) {
    ifstream file(filename);
    Graph graph;

    file >> graph.n;
    graph.nodes = new Node[graph.n];
    for (int i = 0; i < graph.n; i++) {
        file >> graph.nodes[i].x >> graph.nodes[i].y;
    }

    file >> graph.e;
    for (int i = 0; i < graph.e; i++) {
        Edge edge;
        file >> edge.u >> edge.v >> edge.weight;
        graph.edges.add_at_end_arr(edge);
    }

    file.close();
    return graph;
}

int main() {

    Graph g = load_file(R"(C:\Users\User\Desktop\zut\sem_3\Algorytmy_2\lab_8\g1.txt)");

    clock_t t1 = clock();
    sort(g.edges);
    clock_t t2 = clock();
    double sortingTime = ((t2 - t1) / (double)CLOCKS_PER_SEC) * 1e3;
    cout << "Czas sortowania: " << sortingTime << " ms" << endl;

    int find_op = 0;

    t1 = clock();
    Dynamic_Array<Edge> mst = Kruskal(g, find_op);
    t2 = clock();
    double kruskalTime = ((t2 - t1) / (double)CLOCKS_PER_SEC) * 1e3;
    cout << "\nCzas Kruskala: " << kruskalTime<< " ms" << endl;

    float total_cost = 0;
    int total_edges = 0;

    for (int i = 0; i < mst.getSize_arr(); i++) {
        Edge e = mst.get_by_index_arr(i);
        //cout << i << ": " << e.u << " " << e.v << " " << e.weight << endl;
        total_cost += e.weight;
        total_edges++;
    }

    cout << "\n- Suma wag: " << total_cost;
    cout << "\n- Liczba krawedzi: " << total_edges;
    cout << "\n- Liczba operacji find: " << find_op << endl;

    delete[] g.nodes;
    return 0;
}