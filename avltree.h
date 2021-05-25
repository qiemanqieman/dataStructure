#pragma once
#include "dynamicsearchtree.h"
#include <iostream>
using namespace std;


template <class KEY, class OTHER>
class avlTree: public dynamicSearchTree<KEY, OTHER> {
    struct avlNode
    {
        SET<KEY, OTHER>   data;
        avlNode *left, *right;
        int height; //结点的高度
        avlNode( const SET<KEY, OTHER> &element ,  avlNode *lt, avlNode *rt, int h=1)
                : data(element), left( lt ), right( rt ), height(h) { }
    };
    avlNode *root;

public:
    avlTree() { root = nullptr; }
    ~avlTree( ) { clear(root);}
    SET<KEY, OTHER> * find(const KEY &x) const;
    void insert( const SET<KEY, OTHER> & x ) ;
    void remove( const KEY & x );
    [[maybe_unused]] [[nodiscard]] bool is_empty() const { return root == nullptr;}
    void clear() { clear(root); root = nullptr;}
    [[nodiscard]] KEY findClosestCommonAncestor(const KEY & x, const KEY & y) const;
    void preOrder() const;
    
private:
    void insert( const SET<KEY, OTHER> & x, avlNode * & t ) ;
    bool remove( const KEY & x, avlNode * & t ) ;
    int height( avlNode *t ) const { return t == nullptr ? 0 : t->height;}
    bool find (avlNode *t, const KEY &x) const;
    void LL( avlNode * & t );
    void LR( avlNode * & t );
    void RL( avlNode * & t );
    void RR( avlNode * & t );
    int max(int a, int b) {return (a>b)?a:b;}
    bool adjust(avlNode *&t, int subTree);
    void clear( avlNode *t );
    void preOrder(avlNode *t) const;
};


template <class KEY, class OTHER>
SET<KEY, OTHER> * avlTree<KEY, OTHER>::find(const KEY &x) const {
    avlNode *t = root;
    while (t and t->data.key != x)
        if (t->data.key > x) t = t->left; else t = t->right;
    if (!t) return nullptr;
    else return (SET<KEY, OTHER> *) t;   // 将avlNode 强制转换为SET是可以的
}

template <class KEY, class OTHER>
void avlTree<KEY, OTHER>::insert( const SET<KEY, OTHER> & x, avlNode * & t )
{
    if( t == nullptr )              //在空树上插入
        t = new avlNode( x, nullptr, nullptr);
    else if( x.key < t->data.key) {                          //在左子树上插入
        insert( x, t->left );
        if ( height( t->left ) - height( t->right ) == 2 )  {  //t失衡
            if( x.key < t->left->data.key ) LL( t ); else LR(t);
        }
    }
    else if(x.key > t->data.key )  {                        //在右子树上插入
        insert( x, t->right );
        if(height( t->left ) - height( t->right ) == - 2 ) {  //t失衡
            if (x.key > t->right->data.key) RR(t); else RL(t);
        }
    }
    //重新计算t的高度
    t->height = max( height( t->left ) , height( t->right ) ) + 1;
}

template <class KEY, class OTHER>
void avlTree<KEY, OTHER>::LL( avlNode * & t )
{
    avlNode *t1 = t->left;       // 未来的树根
    t->left = t1->right;
    t1->right = t;
    t->height = max( height( t->left ),  height( t->right ) ) + 1;
    t1->height = max( height( t1->left ), height(t)) + 1;
    t = t1;//新的父子关联
}

template <class KEY, class OTHER>
void avlTree<KEY, OTHER>::RR( avlNode * & t )
{
    avlNode *t1 = t->right;
    t->right = t1->left;
    t1->left = t;
    t->height = max( height( t->left ),  height( t->right ) ) + 1;
    t1->height = max( height( t1->right ), height(t)) + 1;
    t = t1;
}

template <class KEY, class OTHER>
void avlTree<KEY, OTHER>::LR( avlNode * & t )
{
    RR( t->left );
    LL( t );
}

template <class KEY, class OTHER>
void avlTree<KEY, OTHER>::RL( avlNode * & t )
{
    LL( t->right );
    RR( t );
}

template<class KEY, class OTHER>
void avlTree<KEY, OTHER>::insert(const SET<KEY, OTHER> &x) {
    insert(x, root);
}

template <class KEY, class OTHER>
bool avlTree<KEY, OTHER>::remove( const KEY & x, avlNode * & t )
{
    if( t == nullptr )     return true;
    if (x == t->data.key) {                           // 删除根结点
        if ( t->left == nullptr or t->right == nullptr ) {
            avlNode *oldNode = t;
            t = ( t->left != nullptr ) ? t->left : t->right;
            delete oldNode;
            return false;   // 一定变矮，所以返回false，继续调整
        }
        else {
            avlNode *tmp = t->right;
            while(tmp->left != nullptr) tmp = tmp->left;
            t->data = tmp->data;
            if (remove(tmp->data.key, t->right)) return true;
            return adjust(t, 1);
        }
    }
    if( x < t->data.key )   {              // 在左子树上删除
        if (remove( x, t->left )) return true;
        return adjust(t, 0);
    }
    else  {                                        // 在右子树上删除
        if (remove( x, t->right )) return true;
        return adjust(t, 1);
    }
}

template <class KEY, class OTHER>
bool avlTree<KEY, OTHER>::adjust(avlNode * &t, int subTree)
{
    if (subTree) {                           //  1 在右子树上删除，使右子树变矮
        if (height(t->left) - height(t->right) == 1 ) return true;            // 情况a
        if (height(t->right) == height(t->left)) { --t->height; return false;} // 情况b
        if (height(t->left->right) > height(t->left->left)) { LR(t); return false; }   // 情况d
        LL(t);
        if (height(t->right) == height(t->left)) return false; else return true;
    }
    else {      // 在左子树删除
        if (height(t->right) - height(t->left) == 1 ) return true;             // 情况a
        if (height(t->right) == height(t->left)) { --t->height; return false;} // 情况b
        if (height(t->right->left) > height(t->right->right)) { RL(t); return false; }  // 情况d
        RR(t);
        if (height(t->right) == height(t->left)) return false; else return true;
    }
}

template<class KEY, class OTHER>
void avlTree<KEY, OTHER>::remove(const KEY &x) {
    remove(x, root);
}

template<class KEY, class OTHER>
void avlTree<KEY, OTHER>::clear(avlTree::avlNode *t) {
    if (!t) return;
    clear(t->left);
    clear(t->right);
    delete t;
}

template<class KEY, class OTHER>
bool avlTree<KEY, OTHER>::find(avlTree::avlNode *t, const KEY &x) const {
    if (!t) return false;
    if (t->data.key == x) return true;
    return find(t->left, x) or find(t->right, x);
}

template<class KEY, class OTHER>
KEY avlTree<KEY, OTHER>::findClosestCommonAncestor(const KEY & x, const KEY & y) const {
    avlNode *p = root, *q;
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

template<class KEY, class OTHER>
void avlTree<KEY, OTHER>::preOrder() const {
    cout << "前序遍历：" << endl;
    preOrder(root);
    cout << endl;
}

template<class KEY, class OTHER>
void avlTree<KEY, OTHER>::preOrder(avlTree::avlNode *t) const {
    if (!t) return;
    cout << t->data.key << ' ';
    preOrder(t->left);
    preOrder(t->right);
}






