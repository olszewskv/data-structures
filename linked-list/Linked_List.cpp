//ALGO2 IS1 210B LAB01
//Szymon Olszewski
//os57850@zut.edu.pl
#include <iostream>
#include <string>
#include <sstream>
#include <time.h>
#include <cmath>
#include <cstdlib>
using namespace std;

template<typename T> struct List_Node {
    T data;
    List_Node* prev;
    List_Node* next;

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

    // (a) dodanie nowego elementu na końcu listy (argument: dane)
    void add_at_tail(T data) {
        List_Node<T>* tmp = new List_Node<T>(data);

        if (size == 0) {
            tail = tmp;
            head = tmp;
        }
        else {
            tail->next = tmp;
            tmp->prev = tail;
            tail = tmp;
        }
        size++;
    }

    // (b) dodanie nowego elementu na początku listy
    void add_at_head(T data) {
        List_Node<T>* tmp = new List_Node<T>(data);

        if (size == 0) {
            head = tmp;
            tail = tmp;
        }
        else {
            head->prev = tmp;
            tmp->next = head;
            head = tmp;
        }
        size++;
    }

    //  (c) usunięcie ostatniego elementu
    void delete_from_tail() {
        if (size == 0) {
            throw out_of_range("");
        }
        else if (size == 1) {
            delete tail;
            tail = head = nullptr;
            size--;
        }
        else {
            List_Node<T>* tmp = tail->prev;

            tmp->next = nullptr;
            delete tail;
            tail = tmp;
            size--;
        }
    }

    //  (d) usunięcie pierwszego elementu
    void delete_from_head() {
        if (size == 0) {
            throw out_of_range("");
        }
        else if (size == 1) {
            delete head;
            head = tail = nullptr;
            size--;
        }
        else {
            List_Node<T>* tmp = head->next;

            tmp->prev = nullptr;
            delete head;
            head = tmp;
            size--;
        }
    }

    //  (e) zwrócenie danych i-tego elementu listy
    T get_by_index(int i) {
        if (i < 0 || i > size) {
            throw out_of_range("");
        }

        if(i < size / 2) {
            List_Node<T>* tmp = head;

            for (int j = 0; j < i; j++) {
                tmp = tmp->next;
            }
            return tmp->data;
        }
        else {
            List_Node<T>* tmp = tail;
            for (int j = size - 1; j > i; j--) {
                tmp = tmp->prev;
            }
            return tmp->data;
        }
    }
    // (f) ustawienie (podmiana) danych i-tego elementu listy
    void replace_data_i_element(int i, T data) {
        List_Node<T>* tmp = head;

        if (i < 0 || i > size) {
            throw out_of_range("");
        }

        for (int j = 0; j < i; j++) {
            tmp = tmp->next;
        }
        tmp->data = data;
    }

    // (g) wyszukanie elementu
    List_Node<T>* search_element(T data) {
        List_Node<T>* tmp = head;

        while (tmp != nullptr) {
            if (tmp->data == data) {
                return tmp;
            }
            tmp = tmp->next;
        }
        return nullptr;
    }

    // (h) wyszukanie elementu
    bool search_delete(T data) {
        List_Node<T>* tmp = head;

        while (tmp != nullptr) {
            if (tmp->data == data) {
                if (tmp == head) {
                    delete_from_head();
                }
                else if (tmp == tail) {
                    delete_from_tail();
                }
                else {
                    tmp->prev->next = tmp->next;
                    tmp->next->prev = tmp->prev;
                    delete tmp;
                    size--;
                }
                return true;
            }
            tmp = tmp->next;
        }
        return false;
    }

    // (i) dodanie nowego elementu z wymuszeniem porządku
    void add_at_order(T data) {
        List_Node<T>* new_tmp = new List_Node<T>(data);

        List_Node<T>* tmp = head;

        if (size == 0) {
            head = new_tmp;
            tail = new_tmp;
        }
        else {
            while (tmp != nullptr && tmp->data < data) {
                tmp = tmp->next;
            }

            if (tmp == head) {
                head->prev = new_tmp;
                new_tmp->next = head;
                head = new_tmp;
            }
            else if (tmp == nullptr) {
                tail->next = new_tmp;
                new_tmp->prev = tail;
                tail = new_tmp;
            }
            else {
                new_tmp->next = tmp;
                new_tmp->prev = tmp->prev;
                tmp->prev->next = new_tmp;
                tmp->prev = new_tmp;
            }
        }
        size ++;
    }

    // (j) czyszczenie listy
    void clear() {
        while (head != nullptr) {
            delete_from_head();
        }
    }

    // (k) zwrócenie napisowej reprezentacji listy
    string to_string(int max = 6) {
        List_Node<T>* tmp = head;
        ostringstream os;

        os << "Size: " << size << "\nList: ";

        int i = 0;
        while (tmp != nullptr && i < max) {
            os << tmp->data << ", ";
            tmp = tmp->next;
            i++;
        }

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

    bool operator==(const some_object &other) const {
        return field_1 == other.field_1 && field_2 == other.field_2;
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
    srand(time(nullptr));
    const int MAX_ORDER = 6;
    Linked_List<some_object>* ll = new Linked_List<some_object>();

    for (int o = 1; o <= MAX_ORDER; o++) {
        const int n = pow(10, o);

        clock_t t1 = clock();
        for (int i = 0; i < n; i++) {
            some_object so;
            so.field_1 = rand() % 10001;
            so.field_2 = 'a' + rand() % 26;
            ll->add_at_head(so);
        }
        clock_t t2 = clock();

        double add_time = ((t2 - t1) / (double)CLOCKS_PER_SEC) * 1e3;
        double avarge_add_time = add_time / n;
        cout << "Rzad [" << o << "]"
        << "\n-Dodano " << n << " elementow"
        << "\n-Czas calkowity: " << add_time << " ms | " << add_time * 1e3 << " us"
        << "\n-Czas sredni na operacje: " << avarge_add_time << " ms | " << avarge_add_time * 1e3 << " us"
        << "\n====== Lista : ======\n" << ll->to_string(6) << endl;

        const int m = pow(10,4);

        t1 = clock();
        int counter = 0;
        for (int i = 0; i < m; i++) {
            some_object so;
            so.field_1 = rand() % 10001;
            so.field_2 = 'a' + rand() % 26;
            if(ll->search_delete(so)) {
                counter++;
            }
        }
        t2 = clock();

        double search_time = ((t2 - t1) / (double)CLOCKS_PER_SEC) * 1e3;
        double avarge_search_time = search_time / m;
        cout << "\n-Wyszukano: " << m
        << "\n-Usunieto: " << counter
        << "\n-Czas calkowity: " << search_time << " ms | " << search_time * 1e3 << " us"
        << "\n-Czas sredni na opreacje: " << avarge_search_time << " ms | " << avarge_search_time * 1e3 << " us"
        << "\n====== Lista po operacjach: ======\n" << ll->to_string(6) << endl;

        ll->clear();
        cout << "---------------------------------------------------------------------------------" << endl;
    }
    delete ll;
    return 0;
}