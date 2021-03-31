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
        node(const T &x, node *n = nullptr):data(x), next(n){}
    };
    node *head;
public:
    seqList(){head = new node(); head.data = 0;}
    ~seqList(){clear(); delete head;}
    int search(const T & x) const = 0;
    T visit(int i) const = 0;
    void traverse() const = 0;
    bool empty() const { return head->data == 0;}
    int length() const { return head->data;}
    void clear();
    void insert(int i, const T &x) = 0;
    void remove(int i) = 0;
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
    if (i < 0 or i > head.data - 1) throw OutOfBoundError();
    node *p = head->next;
    while(i--) p = p->next;
    return p->data;
}

template <class T>
void linkList<T>::traverse() const {
    std::cout << std::endl << "Traverse the list:\n";
    node *p = head->next;
    while(p)
        std::cout << p->data << ' ';
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
}

template <class T>
void linkList<T>::insert(int i, const T &x) {
    if (i < 0 or i > head->data) throw OutOfBoundError();
    node *p = head;
    while(i--)
        p = p->next;
    p->next = new node(x, p->next);
    ++head->data;
}

template <class T>
void linkList<T>::remove(int i) {
    if (i < 0 or i > head->data - 1) throw OutOfBoundError();
    node *p = head, *q;
    while(i--) p = p->next;
    q = p->next;
    p->next = q->next;
    delete q;
    --head->data;
}


#endif //DATASTRUCTURE_LINKLIST_H
