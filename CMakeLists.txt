cmake_minimum_required(VERSION 3.29)
project(Algorytmy_2)

set(CMAKE_CXX_STANDARD 20)

add_executable(ll linked-list/Linked_List.cpp)

add_executable(arr dyn-arr/Dynamic_Array.cpp)

add_executable(bst bst/BST.cpp)

add_executable(rbt rbt/RBT.cpp)

add_executable(heap heap/Heap.cpp
        heap/Dynamic_arr.h
)

add_executable(hash-tab hash-table/Hash_Table.cpp
        hash-table/Dynamic_Array.h
        hash-table/Linked_List.h
)

add_executable(sorting sort-alg/Counting_Sorts.cpp
        sort-alg/Dynamic_Array.h
        sort-alg/Heap.h
)

add_executable(kruskal kruskal/Kruskal's_Algorithm.cpp
        kruskal/Dynamic_Array.h)



