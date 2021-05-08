#pragma once
#include "dynamicsearchtree.h"


template <class KEY, class OTHER>
class closeHashTable:public dynamicSearchTree<KEY, OTHER> {
private:
    struct node { //散列表的结点类
        SET <KEY, OTHER>  data;
        int    state;  //0 -- empty   1 -- active   2 -- deleted
        node() {state = 0;}
    };
    node *array;
    int  size;
    int (*key)(const KEY &x);
    static int defaultKey(const int &x) {return x;}  //静态好处，不依赖于对象即可调用

public:
    explicit closeHashTable(int length = 101, int (*f)(const KEY &x) = defaultKey) ;
    ~closeHashTable() {delete [] array;}
    SET<KEY, OTHER> *find(const KEY &x) const;
    void insert(const SET<KEY, OTHER> &x);
    void remove(const KEY &x) ;
};

template <class KEY, class OTHER>
closeHashTable<KEY, OTHER>::closeHashTable(int length, int (*f)(const KEY &x) )
{
    size = length;
    array = new node[size];
    key = f;
}

template <class KEY, class OTHER>
void closeHashTable<KEY, OTHER>::insert(const SET<KEY, OTHER> &x)
{
    int initPos, pos ;
    initPos = pos = key(x.key) % size;
    do {
        if (array[pos].state != 1) {       // 0或者2，找到空单元
            array[pos].data = x;
            array[pos].state = 1;
            return;
        }
        pos = (pos+1) % size;
    } while (pos != initPos);
}

template<class KEY, class OTHER>
SET<KEY, OTHER>* closeHashTable<KEY, OTHER>::find(const KEY &x) const {
    int init_pos, pos;
    init_pos = pos = key(x) % size;
    while (array[pos].state != 0 and array[pos].data.key != x) {
        pos = (++pos) % size;
        if (pos == init_pos) return nullptr;
    }
    if (array[pos].state == 0 or array[pos].state == 2) return nullptr;
    return (SET<KEY, OTHER>*) (array + pos);
}

template<class KEY, class OTHER>
void closeHashTable<KEY, OTHER>::remove(const KEY &x) {
    int init_pos, pos;
    init_pos = pos = key(x) % size;
    while (array[pos].state != 0 and array[pos].data.key != x) {
        pos = (++pos) % size;
        if (pos == init_pos) return;
    }
    if (array[pos].state == 0 or array[pos].state == 2) return;
    array[pos].state = 2;
}



