#pragma once
#include "stack.h"
#include <iostream>
template <class elemType>
class seqStack:public stack<elemType>{
private:
    elemType* data;
    int max_size;
    int Top;
    void double_space();
public:
    explicit seqStack(int init_size = 10);
    ~seqStack(){delete[] data;}
    [[nodiscard]] bool empty() const;
    elemType top() const;
    [[nodiscard]] int length() const {return Top + 1;}
    elemType operator[](int i) const {if (empty()) throw operateEmptyStackError(); return data[i];}
    elemType pop();
    void push(const elemType &x);
};

template <class elemType>
void seqStack<elemType>::double_space() {
    elemType* tmp = data;
    max_size *= 2;
    data = new elemType[max_size];
    for (int i = 0; i <= Top; ++i)
        data[i] = tmp[i];
    delete[] tmp;
}

template <class elemType>
seqStack<elemType>::seqStack(int init_size){
    data = new elemType[init_size];
    Top = -1;
    max_size = init_size;
}

template <class elemType>
bool seqStack<elemType>::empty() const {
    return Top == -1;
}

template <class elemType>
elemType seqStack<elemType>::top() const{
    if (empty()) 
        throw operateEmptyStackError();
    return this->data[Top];
}

template <class elemType>
elemType seqStack<elemType>::pop(){
    if (empty()) 
        throw operateEmptyStackError();
    Top -= 1;
    return data[Top + 1];
}

template <class elemType>
void seqStack<elemType>::push(const elemType &x){
    if (Top == max_size - 1) double_space();
    Top += 1;
    data[Top] = x;
}
