/*
 *
1161. 快排计数
题目描述
输入1到n的一个排列构成一个序列，输出在这个序列上进行快速排序算法需要的比较次数。

本题的快速排序有以下要求：

每次选择子数组的第一个元素作为pivot
在根据pivot划分完的左子数组元素的顺序与原数组中的顺序一致。右子数组同理。
比如：数组为 5, 3, 6, 8, 2, 4,1 , 9, 10，选择5为pivot，划分得到的左子数组3,2,4,1，右子数组6,8,9,10,7。

输入格式
第一行一个整数n,

第二行n个整数，是1到n的一个排列

输出格式
一个整数，表示快速排序的比较次数

样例输入
6
3 2 4 1 6 5
样例输出
9
解释：首先以3为pivot，进行5次比较得到2, 1和4,6,5,这两个子数组用同样的方法依次需要1次和3次，最终为9次。

数据范围
对于40%40的数据，n≤100，

对于40%40的数据，n≤10000，

对于20%20的数据，n≤1000000. (直接模拟方法可能无法通过)
 */


//解体思路：
//动态规划，第一个比较n-1次，然后入avl树，后面的

#include <iostream>
using namespace std;

template <class KEY, class OTHER>
struct SET {
    KEY key;  //如学号
    [[maybe_unused]] OTHER other; //包含姓名、性别、出生日期等的结构体变量
    SET() = default;
    SET(KEY k, OTHER o) {key = k; other = o;}
};


template<class KEY, class OTHER>
struct avlNode
{
    SET<KEY, OTHER>   data;
    avlNode*left, *right;
    int height; //结点的高度
    avlNode( const SET<KEY, OTHER> &element ,  avlNode *lt, avlNode *rt, int h=1)
            : data(element), left( lt ), right( rt ), height(h) { }
};


template <class KEY, class OTHER>
class avlTree {
    avlNode<KEY, OTHER> *root;

public:
    avlTree() { root = nullptr; }
    ~avlTree( ) { clear(root);}
    [[nodiscard]] SET<KEY, OTHER> * findLess(const KEY &x) const;   // 返回小于x的最大结点的data字段
    [[nodiscard]] SET<KEY, OTHER> * findGreater(const KEY &x) const;//
    void insert( const SET<KEY, OTHER> & x ) ;
    void remove( const KEY & x );

    [[maybe_unused]] [[nodiscard]] bool is_empty() const { return root == nullptr;}
    void clear() { clear(root); root = nullptr;}

private:
    void insert( const SET<KEY, OTHER> & x, avlNode<KEY, OTHER>* & t ) ;
    bool remove( const KEY & x, avlNode<KEY, OTHER>* & t ) ;
    int height( avlNode<KEY, OTHER>*t ) const { return t == nullptr ? 0 : t->height;}
    bool find (avlNode<KEY, OTHER>*t, const KEY &x) const;
    void LL( avlNode<KEY, OTHER>* & t );
    void LR( avlNode<KEY, OTHER>* & t );
    void RL( avlNode<KEY, OTHER>* & t );
    void RR( avlNode<KEY, OTHER>* & t );
    int max(int a, int b) {return (a>b)?a:b;}
    bool adjust(avlNode<KEY, OTHER>*&t, int subTree);
    void clear( avlNode<KEY, OTHER>*t );
};


template<class KEY, class OTHER>
SET<KEY, OTHER> *avlTree<KEY, OTHER>::findLess(const KEY &x) const {
    avlNode<KEY, OTHER> *t = root, *tmp = nullptr;
    while(t){
        if (t->data.key > x) {
            t = t->left;
            continue;
        }
        if (t->data.key < x) {
            tmp = t;
            t = t->right;
        }
    }
    return (SET<KEY, OTHER>*) tmp;
}

template<class KEY, class OTHER>
SET<KEY, OTHER> *avlTree<KEY, OTHER>::findGreater(const KEY &x) const {
    avlNode<KEY, OTHER> *t = root, *tmp = nullptr;
    while(t){
        if (t->data.key < x) {
            t = t->right;
            continue;
        }
        if (t->data.key > x) {
            tmp = t;
            t = t->left;
        }
    }
    return (SET<KEY,OTHER>*)tmp;
}

template <class KEY, class OTHER>
void avlTree<KEY, OTHER>::insert( const SET<KEY, OTHER> & x, avlNode<KEY, OTHER>* & t )
{
    if( t == nullptr )              //在空树上插入
        t = new avlNode<KEY,OTHER>( x, nullptr, nullptr);
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
void avlTree<KEY, OTHER>::LL( avlNode<KEY, OTHER>* & t )
{
    avlNode<KEY, OTHER>*t1 = t->left;       // 未来的树根
    t->left = t1->right;
    t1->right = t;
    t->height = max( height( t->left ),  height( t->right ) ) + 1;
    t1->height = max( height( t1->left ), height(t)) + 1;
    t = t1;//新的父子关联
}

template <class KEY, class OTHER>
void avlTree<KEY, OTHER>::RR( avlNode<KEY, OTHER>* & t )
{
    avlNode<KEY, OTHER>*t1 = t->right;
    t->right = t1->left;
    t1->left = t;
    t->height = max( height( t->left ),  height( t->right ) ) + 1;
    t1->height = max( height( t1->right ), height(t)) + 1;
    t = t1;
}

template <class KEY, class OTHER>
void avlTree<KEY, OTHER>::LR( avlNode<KEY, OTHER>* & t )
{
    RR( t->left );
    LL( t );
}

template <class KEY, class OTHER>
void avlTree<KEY, OTHER>::RL( avlNode<KEY, OTHER>* & t )
{
    LL( t->right );
    RR( t );
}

template<class KEY, class OTHER>
void avlTree<KEY, OTHER>::insert(const SET<KEY, OTHER> &x) {
    insert(x, root);
}

template <class KEY, class OTHER>
bool avlTree<KEY, OTHER>::remove( const KEY & x, avlNode<KEY, OTHER>* & t )
{
    if( t == nullptr )     return true;
    if (x == t->data.key) {                           // 删除根结点
        if ( t->left == nullptr or t->right == nullptr ) {
            avlNode<KEY, OTHER>*oldNode = t;
            t = ( t->left != nullptr ) ? t->left : t->right;
            delete oldNode;
            return false;   // 一定变矮，所以返回false，继续调整
        }
        else {
            avlNode<KEY, OTHER>*tmp = t->right;
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
bool avlTree<KEY, OTHER>::adjust(avlNode<KEY, OTHER>* &t, int subTree)
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
void avlTree<KEY, OTHER>::clear(avlNode<KEY, OTHER>*t) {
    if (!t) return;
    clear(t->left);
    clear(t->right);
    delete t;
}

template<class KEY, class OTHER>
bool avlTree<KEY, OTHER>::find(avlNode<KEY, OTHER>*t, const KEY &x) const {
    if (!t) return false;
    if (t->data.key == x) return true;
    return find(t->left, x) or find(t->right, x);
}


int main() {
    int n, a, p, q, res;
    SET<int, int> *cur;
    avlTree<int, int> bt;
    cin >> n >> a;
    bt.insert(SET<int, int>(a,a));
    res = n - 1; //首项比较n-1次
    for (int i = 1; i < n; ++i) {
        cin >> a;
        cur = bt.findGreater(a);
        if (cur) p = cur->key;
        else p = n + 1;
        cur = bt.findLess(a);
        if (cur) q = cur->key;
        else q = 0;
        res += (p - q - 2);
        bt.insert(SET<int, int>(a,a));
    }
    cout << res;
}
