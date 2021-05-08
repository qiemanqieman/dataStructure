#pragma once
#include "dynamicsearchtree.h"


template <class KEY, class OTHER>
class binarySearchTree: public dynamicSearchTree<KEY, OTHER>
{
private:
    struct node
    {
        SET<KEY, OTHER> data;
        node *left;
        node *right;

        explicit node( const SET<KEY, OTHER> &x,node *lt=nullptr,  node *rt=nullptr ): data(x), left(lt), right(rt) {}
    };

    node *root;
    void make_empty( node *t );
    bool find (node *t, const KEY &x) const;

public:
    binarySearchTree(){root = nullptr;}
    ~binarySearchTree() {make_empty(root); root = nullptr;}
    SET<KEY, OTHER> *find(const KEY &x) const ;
    void insert(const SET<KEY, OTHER> &x);
    void remove( const KEY & x);
    [[nodiscard]] KEY findClosestCommonAncestor(const KEY & x, const KEY & y) const;
};


template<class KEY, class OTHER>
void binarySearchTree<KEY, OTHER>::make_empty(binarySearchTree::node *t) {
    if(!t) return;
    make_empty(t->left);
    make_empty(t->right);
    delete t;
}

template <class KEY, class OTHER>
SET<KEY, OTHER>* binarySearchTree<KEY, OTHER>::find(const KEY &x) const {  //非递归实现
    if (!root) return nullptr;
    node *p = root;
    while (p) {
        if (x == p->data.key) return &p->data;
        if (x > p->data.key) p = p->right;
        else p = p->left;
    }
    return nullptr;
}

template <class KEY, class OTHER>
void binarySearchTree<KEY,OTHER>::insert(const SET<KEY, OTHER> &x) {  //非递归实现
    if (!root) { root = new node(x); return;}
    node *p = root;
    while(p){
        if (p->data.key == x.key) { return;}
        if (x.key < p->data.key) {
            if (!p->left) { p->left = new node(x); return; }
            p = p->left;
        }
        else {
            if (!p->right) { p->right = new node(x); return; }
            p = p->right;
        }
    }
}

template<class KEY, class OTHER>
void binarySearchTree<KEY, OTHER>::remove(const KEY &x) {   //非递归实现
    if (!root) return;
    node *p = root, *parent = nullptr;
    int flag;    //0为父结点顺左子下来，1为父结点顺右子下来。
    while(p){
        if (x < p->data.key){ parent = p; flag = 0; p = p->left; continue; }
        if (x > p->data.key){ parent = p; flag = 1; p = p->right; continue;}

        // 删除开始
        if (!p->left or !p->right){  //单子结点 or 叶子结点
            node *tmp = p;
            if (!parent) { root = (p->left)? p->left : p->right; return;}
            if (flag) parent->right = (p->left)? p->left : p->right;
            else parent->left = (p->left)? p->left : p->right;
            delete tmp;
            return;
        }
        else {  //双子结点
            node *q = p->right; parent = p; flag = 1;
            while(q->left) { parent = q; q = q->left; flag = 0; }

            SET<KEY,OTHER> s = p->data;  //交换待删除结点和替身的元素值
            p->data = q->data;
            q->data = s;

            p = q;   //删除结点指针变为替身继续返回循环
        }
    }
}


template<class KEY, class OTHER>
bool binarySearchTree<KEY, OTHER>::find(binarySearchTree::node *t, const KEY &x) const {
    if (!t) return false;
    if (t->data.key == x) return true;
    return find(t->left, x) or find(t->right, x);
}

template<class KEY, class OTHER>
KEY binarySearchTree<KEY, OTHER>::findClosestCommonAncestor(const KEY & x, const KEY & y) const {
    node *p = root, *q;
    while (find(p, x) and find(p, y))
    {
        q = p->left;
        if (find(q, x) and find(q,y)) { p = q; continue;}
        q = p->right;
        if (find(q, x) and find(q,y)) { p = q; continue;}
        break;
    }
    return p->data.key;
}
