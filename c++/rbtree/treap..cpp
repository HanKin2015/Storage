#include <bits/stdc++.h>
using namespace std;

struct Node {
    int key, priority;
    Node *left, *right;
    Node(int k) : key(k), priority(rand()), left(nullptr), right(nullptr) {}
};

Node* merge(Node* l, Node* r) {
    if (!l || !r) return l ? l : r;
    if (l->priority > r->priority) {
        l->right = merge(l->right, r);
        return l;
    } else {
        r->left = merge(l, r->left);
        return r;
    }
}

void split(Node* t, int k, Node*& l, Node*& r) {
    if (!t) {
        l = r = nullptr;
        return;
    }
    if (t->key <= k) {
        l = t;
        split(t->right, k, l->right, r);
    } else {
        r = t;
        split(t->left, k, l, r->left);
    }
}

void insert(Node*& t, int k) {
    Node *l, *r;
    split(t, k, l, r);
    t = merge(merge(l, new Node(k)), r);
}

void erase(Node*& t, int k) {
    if (!t) return;
    if (t->key == k) {
        Node* tmp = t;
        t = merge(t->left, t->right);
        delete tmp;
    } else if (t->key < k) {
        erase(t->right, k);
    } else {
        erase(t->left, k);
    }
}

bool find(Node* t, int k) {
    if (!t) return false;
    if (t->key == k) return true;
    if (t->key < k) return find(t->right, k);
    return find(t->left, k);
}

void print(Node* t) {
    if (!t) return;
    print(t->left);
    cout << t->key << " ";
    print(t->right);
}

int main() {
    Node* root = nullptr;
    insert(root, 3);
    insert(root, 1);
    insert(root, 4);
    insert(root, 1);
    insert(root, 5);
    erase(root, 1);
    cout << find(root, 1) << endl; // 0
    cout << find(root, 3) << endl; // 1
    print(root); // 3 4 5
    return 0;
}
