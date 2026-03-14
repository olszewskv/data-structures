//ALGO2 IS1 210B LAB04
//Szymon Olszewski
//os57850@zut.edu.pl

#include <iostream>
#include <string>
#include <sstream>
#include <time.h>
#include <cmath>
#include <cstdlib>
using namespace std;

enum Color {
    RED, BLACK
};

template<typename T> struct TreeNode{
    T data;
    TreeNode<T>* parent;
    TreeNode<T>* left;
    TreeNode<T>* right;
    int index;
    Color color;

    TreeNode(T newData, int id, Color c = RED) {
        data = newData;
        parent = left = right = nullptr;
        index = id;
        color = c;
    }
};

template<typename T> class RBT {
private:
    TreeNode<T>* root;
    int size;
    int nextIndex;

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

    TreeNode<T>* getUncle(TreeNode<T>* node) {
        if (node == nullptr || node->parent == nullptr || node->parent->parent == nullptr) {
            return nullptr;
        }

        TreeNode<T>* grandParent = node->parent->parent;

        if (node->parent == grandParent->left) {
            return grandParent->right;
        }
        else {
            return grandParent->left;
        }
    }

    // (f) rotacja w lewo
    void leftRotation(TreeNode<T>* parent, TreeNode<T>* child) {
        // Lewe dziecko Child staje sie prawym dzieckiem Parenta
        parent->right = child->left;
        if (child->left) {
            child->left->parent = parent;
        }

        // Child przejmuje miejsce Parent
        child->parent = parent->parent;
        if (parent->parent == nullptr) {
            root = child;
        }
        else if (parent == parent->parent->left) {
            parent->parent->left = child;
        }
        else {
            parent->parent->right = child;
        }

        // Parent zostaje lewym dzieckiem Child
        child->left = parent;
        parent->parent = child;
    }

    // (f) rotacja w prawo
    void rightRotation(TreeNode<T>* parent, TreeNode<T>* child) {
        // Prawe dziecko Child staje sie lewym dzieckiem Parenta
        parent->left = child->right;
        if (child->right) {
            child->right->parent = parent;
        }

        // Child przejmuje miejsce Parent
        child->parent = parent->parent;

        if (parent->parent == nullptr) {
            root = child;
        }
        else if (parent == parent->parent->left) {
            parent->parent->left = child;
        }
        else {
            parent->parent->right = child;
        }

        // Parent zostaje lewym dzieckiem Child
        child->right = parent;
        parent->parent = child;
    }

    void repair(TreeNode<T>* node) {
        if (node == nullptr) {
            return;
        }

        // (1) node = root
        if (node->parent == nullptr) {
            node->color = BLACK;
            return;
        }

        if (node->parent->color == BLACK) {
            return;
        }

        TreeNode<T>* parent = node->parent;
        TreeNode<T>* grandParent = parent->parent;


        if (grandParent == nullptr) {
            return;
        }

        TreeNode<T>* uncle = getUncle(node);

        // (2) node->uncle = RED
        if (uncle && uncle->color == RED) {
            // Recolorujemy parent, grandparent i uncle
            parent->color = BLACK;
            uncle->color = BLACK;
            grandParent->color = RED;

            repair(grandParent);
            return;
        }

        // (3) node->uncle = BLACK
        if (parent == grandParent->left) {
            if (node == parent->right) {
                // Triangle case
                leftRotation(parent, node);
                node = parent;
                parent = node->parent;
                grandParent = parent->parent;
            }

            // Line case
            rightRotation(grandParent, parent);
            parent->color = BLACK;
            grandParent->color = RED;
        }
        else { // parent == grandParent->right
            if (node == parent->left) {
                // Triangle case
                rightRotation(parent, node);
                node = parent;
                parent = node->parent;
                grandParent = parent->parent;
            }

            // Line case
            leftRotation(grandParent, parent);
            parent->color = BLACK;
            grandParent->color = RED;
        }
    }

    void print(TreeNode<T>* node, ostringstream& os, int& printed, int max) {
        if (node == nullptr || printed >= max) {
            return;
        }

        os << "(" << node->index << ": [";
        if (node->color == BLACK) {
            os << "black";
        }
        else {
            os << "red";
        }

        os << ", p: ";
        if (node->parent == nullptr) {
            os << "NULL";
        }
        else {
            os << node->parent->index;
        }

        os << ", l:";
        if (node->left == nullptr) {
            os << "NULL";
        }
        else {
            os << node->left->index;
        }

        os << ", r:";
        if (node->right == nullptr) {
            os << "NULL";
        }
        else {
            os << node->right->index;
        }

        os << "] (data : " << node->data << "))," << endl;

        printed += 1;

        print(node->left, os, printed, max);
        print(node->right, os, printed, max);
    }

public:
    RBT() {
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

    ~RBT() {
        clear_tree();
    }

    // (a) wyszukanie elementu
    TreeNode<T>* search(T searchData) {
        TreeNode<T>* current = root;

        while (current) {
            if (current->data == searchData) {
                return current;
            }
            else if (searchData < current->data) {
                current = current->left;
            }
            else {
                current = current->right;
            }
        }
        return nullptr;
    }

    // (b) przejście pre-order drzewa
    void pre_order(TreeNode<T>* node) {
        if (node) {
            cout << node->data << " ";
            pre_order(node->left);
            pre_order(node->right);
        }
    }

    // (c) przejście in-order drzewa
    void in_order(TreeNode<T>* node) {
        if (node) {
            in_order(node->left);
            cout << node->data << " ";
            in_order(node->right);
        }
    }

    // (d) czyszczenie drzewa
    void clear_tree() {
        delete_tree(root);
        root = nullptr;
        size = 0;
        nextIndex = 0;
    }

    // (e) wyznaczenie wysokości drzewa
    int get_height() {
        return height(root);
    }

    // (f) dodanie nowego elementu do drzewa
    void add_node(T newdata) {
        TreeNode<T>* newNode = new TreeNode<T>(newdata, nextIndex, RED);
        nextIndex++;

        TreeNode<T>* exist = search(newdata);
        if (exist) {
            return;
        }

        if (root == nullptr) {
            root = newNode;
            root->color = BLACK;
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
        repair(newNode);
    }

    // (g) zwrócenie napisowej reprezentacji drzewa
    string to_string(int max = 10) {
        ostringstream os;

        os << "RBT:" << endl;
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
    RBT<some_object>* rbt = new RBT<some_object>();

    for (int o = 1; o <= MAX_ORDER; o++) {
        const int n = pow(10, o);

        clock_t t1 = clock();
        for (int i = 0; i < n; i++) {
            some_object so;
            so.field_1 = ((rand()<<15) + rand()) % 10000000;
            so.field_2 = 'a' + rand() % 26;
            rbt->add_node(so);
        }
        clock_t t2 = clock();

        double addTime = ((t2 - t1) / (double)CLOCKS_PER_SEC) * 1e3;
        cout << "\n\n[" << o << "]--------------------------------------------------------------------------\n"
        << rbt->to_string(6)
        << "\n-Dodano " << rbt->get_size() << " elementow"
        << "\n-Czas calkowity: " << addTime << " ms | "
        << addTime * 1e3 << " us";

        const int m = pow(10, 4);
        int hits = 0;

        t1 = clock();
        for (int i = 0; i < m; i++) {
            some_object so;
            so.field_1 = ((rand()<<15) + rand()) % 10000000;
            so.field_2 = 'a' + rand() % 26;
            TreeNode<some_object>* result = rbt->search(so);
            if (result != nullptr) {
                hits++;
            }
        }
        t2 = clock();

        double searchTime = ((t2 - t1) / (double)CLOCKS_PER_SEC) * 1e3;
        cout << "\n-Wyszukiwania: " << m
        << "\n-Trafiono: " << hits
        << "\n-Czas wyszukiwania: " << searchTime << " ms | "
        << searchTime * 1e3 << " us";

        double stosunek = rbt->get_height()/log2(rbt->get_size());
        cout << "\n-Stosunek height/log2n: " << stosunek;

        rbt->clear_tree();
    }
    delete rbt;
    return 0;
}