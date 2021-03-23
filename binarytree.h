#include "btree.h"
#include <iostream>
#include "linkqueue.h"
#include "linkStack.h"


template <class T>
class binaryTree;

template <class T>
T max(T a, T b){ return (a > b) ? a : b;}

template <class T>
void print_tree(const binaryTree<T> &t, T flag);


template <class T>
class node{
    friend binaryTree<T>;
private:
    T data;
    node *left, *right;
    node() = default;
    explicit node(T d, node* L = nullptr, node* R = nullptr){ data = d; left = L, right = R;}
    ~node() = default;
};

template <class T>
class binaryTree: public bTree<T>{
    friend void print_tree<T>(const binaryTree<T> &t, T flag);
private:
    node<T>* Root;

    node<T>* find(T x, node<T>* t) const;
    void clear(node<T>* &t);
//    void pre_order(node<T>* t) const;    // if implement traverse with recurse, these private functions are needed.
//    void mid_order(node<T>* t) const;
//    void post_order(node<T>* t) const;
    int size(node<T> *t) const;
    int height(node<T> *t) const;
public:
    explicit binaryTree(node<T>*  n = nullptr) : Root(n){}
    ~binaryTree(){clear(Root);}
    void create_tree(T flag);
    void clear();
    [[nodiscard]] bool empty() const;
    T root(T flag) const;
    T parent(T x, T flag) const {return flag;}
    T lchild(T x, T flag) const;
    T rchild(T x, T flag) const;
    void pre_order() const;
    void mid_order() const;
    void post_order() const;
    void level_order() const;
    [[nodiscard]] int size() const;
    [[nodiscard]] int height() const;
    void del_left(T x);
    void del_right(T x);
};

template<class T>
node<T> *binaryTree<T>::find(T x, node<T> *t) const {
    node<T> *tmp;
    if (!t) return nullptr;
    if (t->data == x) return t;
    if ((tmp = find(x, t->left))) return tmp;
    return find(x, t->right);
}

template<class T>
void binaryTree<T>::clear(node<T> *&t) {
    if (!t) return;
    clear(t->left);
    clear(t->right);
    delete t;
    t = nullptr;
}



template<class T>
int binaryTree<T>::size(node<T> *t) const {
    if (!t) return 0;
    return 1 + size(t->left) + size(t->right);
}

template<class T>
void binaryTree<T>::create_tree(T flag) {
    // create a tree from keyboard, ending with flag
    T elem, left_child, right_child;
    node<T>* parent;
    linkQueue<node<T> *> que;
    std::cout <<  "Starting to create a new tree(input " << flag << " for empty node)" << std::endl << "Please input the Root: ";
    std::cin >> elem;
    if (elem == flag) return;
    Root = new node<T>(elem);
    que.push(Root);
    while(!que.empty()){
        parent = que.pop();
        std::cout << "Please input lchild and rchild of " << parent->data<< ": ";
        std::cin >> left_child >> right_child;
        if (left_child != flag) que.push(parent->left = new node<T>(left_child));
        if (right_child != flag) que.push(parent->right = new node<T>(right_child));
    }
    std::cout << "Create completed!\n";
}

template<class T>
void binaryTree<T>::clear() {
    clear(Root);
}

template<class T>
bool binaryTree<T>::empty() const {
    return Root == nullptr;
}

template<class T>
T binaryTree<T>::root(T flag) const {
    if (!Root) return flag;
    return Root->data;
}

template<class T>
T binaryTree<T>::lchild(T x, T flag) const {
    node<T> *tmp = find(x, Root);
    if (!tmp or !tmp->left) return flag;
    return tmp->left->data;
}

template<class T>
T binaryTree<T>::rchild(T x, T flag) const {
    node<T> *tmp = find(x, Root);
    if (!tmp or !tmp->right) return flag;
    return tmp->right->data;
}


//  implement traverse without recurse
template<class T>
void binaryTree<T>::pre_order() const{
    std::cout << "\nTraverse with pre_order:\n";
    if (empty()) return;
    node<T> *p;
    linkStack<node<T>*> s;
    s.push(Root);
    while(!s.empty()){
        p = s.pop();
        std::cout << p->data << ' ';
        if (p->right) s.push(p->right);
        if (p->left) s.push(p->left);
    }
    std::cout << std::endl;
}

template<class T>
void binaryTree<T>::mid_order() const {
    std::cout << "\nTraverse with mid_order:\n";
    if (empty()) return;
    node<T> *p; bool q;
    linkStack<node<T>*> s1;
    linkStack<bool> s2;
    s1.push(Root);
    s2.push(false);
    while(!s1.empty()){
        p = s1.pop(); q = s2.pop();
        if (!q) {
            s1.push(p);
            s2.push(true);
            if (p->left) {
                s1.push(p->left);
                s2.push(false);
            }
        }
        if (q) {
            std::cout << p->data << ' ';
            if (p->right) {
                s1.push(p->right);
                s2.push(false);
            }
        }
    }
    std::cout << std::endl;
}

template<class T>
void binaryTree<T>::post_order() const{
    std::cout << "\nTraverse with post_order:\n";
    if (empty()) return;
    node<T> *p;
    int q;
    linkStack<node<T>*> s1;
    linkStack<int> s2;
    s1.push(Root);
    s2.push(0);
    while(!s1.empty()){
        p = s1.pop();
        q = s2.pop();
        if (q == 0) {
            s1.push(p);
            s2.push(1);
            if (p->left){
                s1.push(p->left);
                s2.push(0);
            }
        }
        if (q == 1){
            s1.push(p);
            s2.push(2);
            if (p->right){
                s1.push(p->right);
                s2.push(0);
            }
        }
        if (q == 2)
            std::cout << p->data << ' ';
    }
    std::cout << std::endl;
}



template<class T>
void binaryTree<T>::level_order() const {
    std::cout << "\nTraverse with level_order:\n";
    linkQueue<node<T>* > que;
    node<T> *parent;
    if (!Root) return;
    que.push(Root);
    while(!que.empty()){
        parent = que.pop();
        std::cout << parent->data << ' ';
        if (parent->left) que.push(parent->left);
        if (parent->right) que.push(parent->right);
    }
    std::cout << std::endl;
}

template<class T>
void binaryTree<T>::del_left(T x) {
    node<T> * tmp = find(x, Root);
    if (!tmp) return;
    clear(tmp->left);
}

template<class T>
void binaryTree<T>::del_right(T x) {
    node<T> * tmp = find(x, Root);
    if (!tmp) return;
    clear(tmp->right);
}

template<class T>
int binaryTree<T>::height(node<T> *t) const {
    if (!t) return 0;
    return 1 + max(height(t->left), height(t->right));
}

template<class T>
int binaryTree<T>::size() const {
    return size(Root);
}

template<class T>
int binaryTree<T>::height() const {
    return height(Root);
}



template <class T>
void print_tree(const binaryTree<T> &t, T flag){
//    int h, cor = 1, count = 1;
//    h = t.height();
//    for (int i = 0; i < h - 1 ; ++i)
//        cor *= 2;
//    linkQueue<cordination<T>> q;
//    cordination<T> cordi(root(flag), cor);
//    q.push(cordi);
    linkQueue<T> q;
    q.push(t.root(flag));
    std::cout << std::endl;
    while(!q.empty()){
        T p, l, r;
        p = q.pop();
        l = t.lchild(p, flag);
        r = t.rchild(p, flag);
//        for (int i = 0; i < p.left_distance - 1; ++i){
//            std::cout << ' ';
//        }
//        if (p.data == flag) std::cout << flag;
//        else {
//            std::cout << p.data;
//
//        }
        std::cout << p << ' ' << l << ' ' << r << std::endl;
        if (l != flag) q.push(l);
        if (r != flag) q.push(r);
    }
}

// implement traverse recursively
/*
template<class T>
void binaryTree<T>::pre_order(node<T> *t) const {
    if (!t) return;
    std::cout << t->data << ' ';
    pre_order(t->left);
    pre_order(t->right);
}

template<class T>
void binaryTree<T>::mid_order(node<T> *t) const {
    if (!t) return;
    mid_order(t->left);
    std::cout << t->data << ' ';
    mid_order(t->right);
}

template<class T>
void binaryTree<T>::post_order(node<T> *t) const {
    if (!t) return;
    post_order(t->left);
    post_order(t->right);
    std::cout << t->data << ' ';
}

template<class T>
void binaryTree<T>::pre_order() const {
    std::cout << "\nTraverse with pre_order:\n";
    pre_order(Root);
}

template<class T>
void binaryTree<T>::mid_order() const {
    std::cout << "\nTraverse with mid_order:\n";
    mid_order(Root);
}

 template<class T>
void binaryTree<T>::post_order() const {
    std::cout << "\nTraverse with post_order:\n";
    post_order(Root);
}



*/
