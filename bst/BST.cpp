//ALGO2 IS1 210B LAB03
//Szymon Olszewski
//os57850@zut.edu.pl

#include <iostream>
#include <string>
#include <sstream>
#include <time.h>
#include <cmath>
#include <cstdlib>
using namespace std;

template<typename T> struct TreeNode {
    T data;
    TreeNode<T>* parent;
    TreeNode<T>* left;
    TreeNode<T>* right;
    int index;

    TreeNode(T newdata, int id) {
        data = newdata;
        parent = left = right = nullptr;
        index = id;
    }
};

template<typename T> class BST {
private:
    TreeNode<T>* root;
    int size;
    int nextIndex;

    TreeNode<T>* minValueNode(TreeNode<T>* node) {
        TreeNode<T>* current = node;
        while (current && current->left != nullptr) {
            current = current->left;
        }
        return current;
    }

    void delete_tree(TreeNode<T>* node) {
        if (node == nullptr) {
            return;
        }

        delete_tree(node->left);
        delete_tree(node->right);
        delete node;
    }

    int height(TreeNode<T>* node) {
        if (node == nullptr) {
            return 0;
        }

        int leftHeight = height(node->left);
        int rightHeight = height(node->right);

        return max(leftHeight, rightHeight) + 1;
    }

    void print(TreeNode<T>* node, ostringstream& os, int& printed, int max) {
        if (node == nullptr || printed >= max) {
            return;
        }

        os << "(" << node->index << ": [p: ";
        if (node->parent == nullptr) {
            os << "NULL";
        }
        else {
            os << node->parent->index;
        }

        os << ", l: ";
        if (node->left == nullptr) {
            os << "NULL";
        }
        else {
            os << node->left->index;
        }

        os << ", r: ";
        if (node->right == nullptr) {
            os << "NULL";
        }
        else {
            os << node->right->index;
        }

        os << "], data: " << node->data << ")," << endl;

        printed++;

        print(node->left, os, printed, max);
        print(node->right, os, printed, max);
    }

public:
    BST() {
        root = nullptr;
        size = 0;
        nextIndex = 0;
    }

    TreeNode<T>* Root() {
        return root;
    }

    int get_size() {
        return size;
    }

    // (a) dodanie nowego elementu do drzewa
    void add_node(T newdata) {
        TreeNode<T>* newNode = new TreeNode<T>(newdata, nextIndex);
        nextIndex++;

        if (root == nullptr) {
            root = newNode;
            size++;
            return;
        }

        TreeNode<T>* current = root;
        TreeNode<T>* parent = nullptr;

        while (current) {
            parent = current;

            if (newdata < current->data) {
                current = current->left;
            }
            else {
                current = current->right;
            }
        }

        newNode->parent = parent;
        if (newdata < parent->data) {
            parent->left = newNode;
        }
        else {
            parent->right = newNode;
        }
        size++;
    }

    // (b) wyszukanie elementu
    TreeNode<T>* search(T newdata) {
        TreeNode<T>* current = root;

        while (current) {
            if (current->data == newdata) {
                return current;
            }
            else if (newdata < current->data) {
                current = current->left;
            }
            else {
                current = current->right;
            }
        }
        return nullptr;
    }

    // (c) usuwanie znalezionego wcześniej węzła drzewa
    void remove_node(TreeNode<T>* node) {
        if (node == nullptr) {
            return;
        }

        // Brak dzieci
        if (node->left == nullptr && node->right == nullptr) {
            if (node->parent == nullptr) {
                root = nullptr;     // gdy korzen
            }
            else if (node->parent->left == node) {
                node->parent->left = nullptr;
            }
            else {
                node->parent->right = nullptr;
            }
            delete node;
            size--;
        }

        // Jedno dziecko
        else if (node->left == nullptr || node->right == nullptr) {
            TreeNode<T>* tmp;

            if (node->left) {
                tmp = node->left;
            }
            else {
                tmp = node->right;
            }

            if (node->parent == nullptr) {
                root = tmp;
            }
            else if (node->parent->left == node) {
                node->parent->left = tmp;
            }
            else {
                node->parent->right = tmp;
            }

            tmp->parent = node->parent;

            delete node;
            size--;
        }

        // Dwójka dzieci
        else {
            TreeNode<T>* InorderSuccessor = minValueNode(node->right);
            node->data = InorderSuccessor->data;
            remove_node(InorderSuccessor);
        }
    }

    // (d) przejście pre-order drzewa
    void pre_order(TreeNode<T>* node) {
        if (node) {
            cout << node->data << " ";
            pre_order(node->left);
            pre_order(node->right);
        }
    }

    // (e) przejście in-order drzewa
    void in_order(TreeNode<T>* node) {
        if (node) {
            in_order(node->left);
            cout << node->data << " ";
            in_order(node->right);
        }
    }

    // (f) czyszczenie drzewa
    void clear_tree() {
        delete_tree(root);
        root = nullptr;
        size = 0;
    }

    // (g) wyznaczenie wysokości drzewa
    int get_height() {
        return height(root);
    }

    // (h) zwrócenie napisowej reprezentacji drzewa
    string to_string(int max = 10) {
        ostringstream os;

        os << "BST: " << endl;
        os << "size: " << size << endl;
        os << "height: " << get_height() << endl;
        os << "{" << endl;

        int printed = 0;
        print(root, os, printed, max);

        os << "}" << endl;
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
    srand(time(NULL));

    const int MAX_ORDER = 7;
    BST<some_object>* bst = new BST<some_object>();

    for (int o = 1; o <= MAX_ORDER; o++) {
        const int n = pow(10, o);

        clock_t t1 = clock();
        for (int i = 0; i < n; i++) {
            some_object so;
            so.field_1 = ((rand()<<15) + rand()) % 1000000000;
            so.field_2 = 'a' + rand() % 26;
            bst->add_node(so);
        }
        clock_t t2 = clock();

        double addTime = ((t2 - t1) / (double)CLOCKS_PER_SEC) * 1e3;
        cout << "\n\n[" << o << "]--------------------------------------------------------------------------\n"
        << bst->to_string(6)
        << "\n-Dodano " << n << " elementow"
        << "\n-Czas calkowity: " << addTime << " ms | "
        << addTime * 1e3 << " us";

        const int m = pow(10, 4);
        int hits = 0;

        t1 = clock();
        for (int i = 0; i < m; i++) {
            some_object so;
            so.field_1 = ((rand()<<15) + rand()) % 1000000000;
            so.field_2 = 'a' + rand() % 26;
            TreeNode<some_object>* result = bst->search(so);
            if (result) {
                hits++;
            }
        }
        t2 = clock();

        double searchTime = ((t2 - t1) / (double)CLOCKS_PER_SEC) * 1e3;
        cout << "\n-Wyszukiwania: " << m
        << "\n-Trafiono: " << hits
        << "\n-Czas wyszukiwania: " << searchTime << " ms | "
        << searchTime * 1e3 << " us";

        double stosunek = bst->get_height()/log2(bst->get_size());
        cout << "\n-Stosunek height/log2n: " << stosunek;

        bst->clear_tree();
    }

    delete bst;
    return 0;
}