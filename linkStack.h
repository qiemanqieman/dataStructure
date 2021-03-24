//
// Created by q on 3/14/21.
#pragma once
#include "stack.h"
#include <iostream>


template <class elemType>
class linkStack: public stack<elemType>{
private:
    struct node{
        elemType data;
        node* next;
        explicit node(node* ne = nullptr){next = ne;}
        explicit node(const elemType &e, node* ne = nullptr){data = e; next = ne;}
        ~node() = default;
    };
    node* Top;

public:
    linkStack(){Top = nullptr;}
    linkStack(const elemType* e, int len);
    ~linkStack();
    [[nodiscard]] bool empty() const;
    elemType top() const;
    bool find(const elemType &x);
    void push(const elemType &e);
    elemType pop();
};



template <class elemType>
linkStack<elemType>::linkStack(const elemType* e,int len) {
    // len should be shorter than the length of array e,
    // you'd better pass len as sizeof(e)/ sizeof (elemType) if e is declared as array.
    // but is e is declared as pointer, watch out!
    Top = nullptr;
    for (int i = 0; i < len; ++i)
        this->push(e[i]);
}

template <class elemType>
linkStack<elemType>::~linkStack() {
    while(Top){
        node* p = Top;
        Top = Top->next;
        delete p;
    }
}

template<class elemType>
void linkStack<elemType>::push(const elemType &e) {
    Top = new node(e,Top);
}

template <class elemType>
elemType linkStack<elemType>::pop(){
    if (this->empty()) throw operateEmptyStackError();
    elemType res = Top->data;
    Top = Top->next;
    return res;
}

template <class elemType>
bool linkStack<elemType>::empty() const {
    return !Top;
}

template <class elemType>
elemType linkStack<elemType>::top() const{
    if (!Top) throw operateEmptyStackError();
    return Top->data;
}

template <class elemType>
bool linkStack<elemType>::find(const elemType &x){
    node *p = Top;
    while(p){
        if (p->data == x) return true;
        p = p->next;
    }

    return false;
}