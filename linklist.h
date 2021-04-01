//
// Created by q on 3/31/21.
//

#ifndef DATASTRUCTURE_LINKLIST_H
#define DATASTRUCTURE_LINKLIST_H


#include "list.h"


template < class T>
class linkList: public list<T>{
private:
    struct node{
        T data;
        node *next;
        node() = default;
        explicit node(const T &x, node *n = nullptr):data(x), next(n){}
    };
    node *head;
    int len;
public:
    linkList(){head = new node(); len = 0;}
    ~linkList(){clear(); delete head;}
    int search(const T & x) const;
    T visit(int i) const;
    void traverse() const;
    [[nodiscard]] bool empty() const { return len == 0;}
    [[nodiscard]] int length() const { return len;}
    void clear();
    void insert(int i, const T &x);
    void remove(int i);
    void remove_back(node *n);  // remove node after n;
    void reverse(); //插脖子法　O(n)
    void remove_duplicate_neighbouring_elements();
};


template <class T>
int linkList<T>::search(const T &x) const {
    int index = 0;
    node *p = head->next;
    while(p) {
        if (p->data == x) return index;
        ++index;
        p = p->next;
    }
    return -1;
}

template <class T>
T linkList<T>::visit(int i) const{
    if (i < 0 or i > len - 1) throw OutOfBoundError();
    node *p = head->next;
    while(i--) p = p->next;
    return p->data;
}

template <class T>
void linkList<T>::traverse() const {
    std::cout << std::endl << "Traverse the list:\n";
    node *p = head->next;
    while(p){
        std::cout << p->data << ' ';
        p = p->next;
    }
    std::cout << std::endl;
}

template <class T>
void linkList<T>::clear() {
    node *p =head->next, *q;
    while(p){
        q = p->next;
        delete p;
        p = q;
    }
    head->next = nullptr;
    head->data = 0;
    len = 0;
}

template <class T>
void linkList<T>::insert(int i, const T &x) {
    if (i < 0 or i > len) throw OutOfBoundError();
    node *p = head;
    while(i--)
        p = p->next;
    p->next = new node(x, p->next);
    ++len;
}

template <class T>
void linkList<T>::remove(int i) {
    if (i < 0 or i > len - 1) throw OutOfBoundError();
    node *p = head, *q;
    while(i--) p = p->next;
    q = p->next;
    p->next = q->next;
    delete q;
    --len;
}

template<class T>
void linkList<T>::remove_back(node* n){
    if (!n) return;
    node * p = n->next;
    if (!p) return;
    n->next = p->next;
    delete p;
}

template<class T>
void linkList<T>::reverse() {
    node* p = head->next, *q;
    head->next = nullptr;
    while(p){
        q = p->next;
        p->next = head->next;
        head->next = p;
        p = q;
    }
}

template <class T>
void linkList<T>::remove_duplicate_neighbouring_elements() {
    if (length() < 2) return;
    node* p = head->next;
    while(p->next){
        if (p->data == p->next->data)
            remove_back(p);
        else p = p->next;
    }
}


#endif //DATASTRUCTURE_LINKLIST_H
