#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>

template<typename T> struct List_Node {
    T data;
    List_Node<T>* prev;
    List_Node<T>* next;

    List_Node(T value) {
        data = value;
        prev = nullptr;
        next = nullptr;
    }
};

template<typename T> class Linked_List {
private:
    List_Node<T>* head;
    List_Node<T>* tail;
    int size;

public:
    Linked_List() {
        head = nullptr;
        tail = nullptr;
        size = 0;
    }

    ~Linked_List() {
        clear();
    }

    void add_at_tail(T newData) {
        List_Node<T>* newNode = new List_Node<T>(newData);

        if (size == 0) {
            head = tail = newNode;
        }
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        size++;
    }

    void add_at_head(T newData) {
        List_Node<T>* newNode = new List_Node<T>(newData);

        if (size == 0) {
            head = tail = newNode;
        }
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
        size++;
    }

    void delete_from_tail() {
        if (size == 0) {
            throw std::out_of_range("");
        }
        else if (size == 1) {
            delete tail;
            head = tail = nullptr;
        }
        else {
            List_Node<T>* newLast = tail->prev;
            newLast->next = nullptr;
            delete tail;
            tail = newLast;
        }
        size--;
    }

    void delete_from_head() {
        if (size == 0) {
            throw std::out_of_range("");
        }
        else if (size == 1) {
            delete head;
            head = tail = nullptr;
        }
        else {
            List_Node<T>* newHead = head->next;
            newHead->prev = nullptr;
            delete head;
            head = newHead;
        }
        size--;
    }

    T get_by_index(int i) {
        if (i < 0 || i >= size) {
            throw std::out_of_range("");
        }

        if (i < size / 2) {
            List_Node<T>* GetNode = head;
            for (int j = 0; j < i; j++) {
                GetNode = GetNode->next;
            }
            return GetNode->data;
        }

        List_Node<T>* GetNode = tail;
        for (int j = size - 1; j > i; j--) {
            GetNode = GetNode->prev;
        }
        return GetNode->data;
    }

    void replace_data_i_element(int i, T newData) {
        if (i < 0 || i >= size) {
            throw std::out_of_range("");
        }

        List_Node<T>* ReplaceNode = head;
        for (int j = 0; j < i; j++) {
            ReplaceNode = ReplaceNode->next;
        }
        ReplaceNode->data = newData;
    }

    List_Node<T>* search_element(T searchData) {
        List_Node<T>* SearchNode = head;
        while (SearchNode != nullptr) {
            if (SearchNode->searchData == searchData) {
                return SearchNode;
            }
            SearchNode = SearchNode->next;
        }
        return nullptr;
    }

    void clear() {
        while (head != nullptr) {
            delete_from_head();
        }
    }

    std::string to_string(int max = 6) {
        std::ostringstream os;
        os << "\n---------------" <<
            "Size = " << size <<
                "\n---------------\n";

        List_Node<T>* Node = head;
        int i = 0;
        while (Node != nullptr && i < max) {
            os << Node->data << ", ";
            Node = Node->next;
            i++;
        }
        return os.str();
    }
};

#endif //LINKED_LIST_H
