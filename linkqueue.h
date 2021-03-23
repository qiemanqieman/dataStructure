//
// Created by q on 3/19/21.
//

#ifndef LINKQUEUE_LINKQUEUE_H
#define LINKQUEUE_LINKQUEUE_H


#include "queue.h"


class emptyError{};


template <class elemType>
class linkQueue: public queue<elemType>{
    struct node{
        elemType data;
        node* next;
        node() = default;
        node(const elemType &e, node* n = nullptr) : data(e), next(n){}
        ~node() = default;
    };

private:
    node* front, *rear;

public:
    linkQueue(){front = rear = nullptr;}
    ~linkQueue();
    bool empty() const {return front == nullptr;}
    elemType get_front() const {if (empty()) throw emptyError(); return front->data; }
    elemType get_rear() const {if (empty()) throw emptyError(); return rear->data;}
    void push(const elemType &x);
    elemType pop();
};


template <class elemType>
linkQueue<elemType>::~linkQueue() {
    node* p;
    while(front){
        p = front->next;
        delete front;
        front = p;
    }
}

template <class elemType>
void linkQueue<elemType>::push(const elemType &x){
    if (empty()) front = rear = new node(x);
    else
        rear = rear->next = new node(x);
}

template <class elemType>
elemType linkQueue<elemType>::pop() {
    if(empty()) throw emptyError();
    elemType tmp = front->data;
    node* n = front;
    front = front->next;
    if (front == nullptr) rear = front;
    delete n;
    return tmp;
}

#endif //LINKQUEUE_LINKQUEUE_H
