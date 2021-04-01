//
// Created by q on 4/1/21.
// Double cycled linked list with two redundant nodes(head and tail)

#ifndef CYCLED_DOUBLE_LINKLIST_CYCLEDDOUBLELINKLIST_H
#define CYCLED_DOUBLE_LINKLIST_CYCLEDDOUBLELINKLIST_H


#include "list.h"


template <class T>
class cdLinkList:public list<T>{
private:
    struct node{
        T data;
        node *pre;
        node *next;
        node() = default;
        explicit node(const T &x, node *p = nullptr, node *n = nullptr) : data(x), pre(p), next(n){}
        ~node() = default;
    };

    node *head;
    node *tail;
    int len;

public:
    class iterator{
        friend class cdLinkList;
    private: node *pointer;
    public:
        explicit iterator(node *n = nullptr) {pointer = n;}
        T& operator*() const {return this->pointer->data;} // getting-value operand overload
        iterator& operator++(){pointer = pointer->next; return *this;} //pre-positioned increase operand overload
        iterator operator++(int){iterator tmp = *this; pointer = pointer->next; return tmp;}
        iterator& operator--(){pointer = pointer->pre; return *this;}
        iterator operator--(int){iterator tmp = *this; pointer = pointer->pre; return tmp;}
        [[nodiscard]] bool operator==(const iterator &other) const{return pointer == other.pointer;}
    };

    cdLinkList(){head = new node(); tail = new node(); head->pre = head->next = tail; tail->pre = tail->next = head; len = 0;}
    ~cdLinkList() {clear(); delete head; delete tail;}
    [[nodiscard]] int search(const T &x) const;  // find the first position x appears in list
    T visit(int i) const;
    void traverse() const;
    void traverse_reversed() const;
    [[nodiscard]] bool empty() const {return len == 0;}
    [[nodiscard]] int length() const {return len;}
    void clear();
    void insert(int i, const T &x);
    void remove(int i);  // remove element in position i
    void remove(const iterator &it); // remove element pointed by iterator it
    void reverse();

    [[nodiscard]] iterator begin() const {return iterator(head);}//return an iterator pointing head,
                                                                        // which is just in front the first node
    [[nodiscard]] iterator end() const {return iterator(tail);} // return an iterator pointing tail,
                                                                // which is just after the last node
};

template <class T>
int cdLinkList<T>::search(const T &x) const {
    int index = 0;
    node *p = head->next;
    while(p != tail){
        if (p->data == x) return index;
        p = p->next;
        ++index;
    }
    return -1;
}

template <class T>
T cdLinkList<T>::visit(int i) const {
    if (i < 0 or i > len - 1) throw OutOfBoundError();
    node *p = head->next;
    while(i--) p = p->next;
    return p->data;
}

template <class T>
void cdLinkList<T>::traverse() const {
    std::cout << std::endl << "Traverse the list:\n";
    if (empty()) return;
    node *p = head->next;
    while(p != tail){
        std::cout << p->data << ' ';
        p = p->next;
    }
    std::cout << std::endl;
}

template<class T>
void cdLinkList<T>::traverse_reversed() const {
    std::cout << std::endl << "Traverse the list with reversed order:\n";
    if (empty()) return;
    node *p = tail->pre;
    while(p != head){
        std::cout << p->data << ' ';
        p = p->pre;
    }
    std::cout << std::endl;
}


template <class T>
void cdLinkList<T>::clear() {
    if (len == 0) return;
    node *p = head->next, *q;
    while(p != tail){
        q = p->next;
        delete p;
        p = q;
    }
    len = 0;
    head->next = tail;
    tail->pre = head;
}

template <class T>
void cdLinkList<T>::insert(int i, const T &x) {
    if (i < 0 or i > len) throw OutOfBoundError();
    node *p = head, *q;
    while(i--) p = p->next;
    q = p->next;
    p->next = new node(x, p, p->next);
    q->pre = p->next;
    ++len;
}

template <class T>
void cdLinkList<T>::remove(int i) {
    if (i < 0 or i > len - 1) throw OutOfBoundError();
    node *p = head, *q;
    while(i--) p = p->next;
    q = p->next;
    p->next = q->next;
    q->next->pre = p;
    delete q;
    --len;
}

template<class T>
void cdLinkList<T>::remove(const cdLinkList::iterator &it) {
    if (it == begin() or it == end()) return;
    cdLinkList<T>::node *tmp = it.pointer->pre;
    tmp->next = it.pointer->next;
    tmp->next->pre = tmp;
    delete it.pointer;
    --len;
}

template<class T>
void cdLinkList<T>::reverse() {
    if (length() < 2) return;
    node *p = head->next, *q;
    tail->pre = p;
    head->next = tail;
    while(p != tail){
        q = p->next;
        p->next = head->next;
        p->pre = head;
        head->next = p;
        p->next->pre = p;
        p = q;
    }
}

#endif //CYCLED_DOUBLE_LINKLIST_CYCLEDDOUBLELINKLIST_H
