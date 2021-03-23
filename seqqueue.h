//
// Created by q on 3/19/21.
//

#ifndef SEQQUEUE_SEQQUEUE_H
#define SEQQUEUE_SEQQUEUE_H

#include "queue.h"

class emptyError{};



template <class elemType>
class seqQueue: public queue<elemType>{
private:
    elemType* data;
    int front, rear;
    int max_size, length;
    void double_space();

public:
    explicit seqQueue(int init_sz = 10) : max_size(init_sz), front(0), rear(0), length(0){data = new elemType[init_sz];}
    ~seqQueue(){delete[] data;}
    [[nodiscard]] bool empty() const {return front == rear;}
    [[nodiscard]] elemType get_front() const {if (empty()) throw emptyError(); return data[front + 1];}
    [[nodiscard]] elemType get_rear() const {if (empty()) throw emptyError(); return data[rear];}
    [[nodiscard]] int index_front() const {return front;}
    [[nodiscard]] int index_rear() const {return rear;}
    [[nodiscard]] int len() const {return length;}
    void push(const elemType &x);
    elemType pop();

};



template <class elemType>
void seqQueue<elemType>::double_space() {
    elemType* tmp = data;
    data = new elemType[2 * max_size];
    for (int i = 1; i < max_size; ++i)
        data[i] = tmp[(i + front) % max_size];
    delete[] tmp;
    front = 0;
    rear = max_size - 1;
    max_size *= 2;
}

template <class elemType>
void seqQueue<elemType>::push(const elemType &x){
    if ((rear + 1) % max_size == front) double_space();
    data[++rear] = x;
    ++length;
}

template <class elemType>
elemType seqQueue<elemType>::pop() {
    if (empty()) throw emptyError();
    front = (front + 1) % max_size;
    --length;
    return data[front];

}

#endif //SEQQUEUE_SEQQUEUE_H
