#pragma once


//集合
template <class KEY, class OTHER>
struct SET {
    KEY key;  //如学号
    OTHER other; //包含姓名、性别、出生日期等的结构体变量
    SET() = default;
    SET(KEY k, OTHER o) {key = k; other = o;}
//    bool operator>(const SET &o) const {return key > o.key;}
//    bool operator==(const SET &o) const {return key == o.key;}
//    bool operator<(const SET &o) const {return key < o.key;}
};


template <class KEY, class OTHER>
class dynamicSearchTree {
public:
    virtual SET<KEY, OTHER> *find(const KEY &x) const = 0;
    virtual void insert(const SET<KEY, OTHER> &x) = 0;
    virtual void remove(const KEY &x) = 0;
    virtual ~dynamicSearchTree() = default;
};
