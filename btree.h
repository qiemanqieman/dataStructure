
//the abstract class of binary tree
template <class T>
class bTree{
public:
    virtual ~bTree(){};
    virtual void clear() = 0;
    virtual bool empty() const = 0;
    virtual T root(T flag) const = 0;
    virtual T parent(T x, T flag) const = 0;
    virtual T lchild(T x, T flag) const = 0;
    virtual T rchild(T x, T flag) const = 0;
    virtual void pre_order() const = 0;
    virtual void mid_order() const = 0;
    virtual void post_order() const = 0;
    virtual void level_order() const = 0;
    virtual void del_left(T x) = 0;
    virtual void del_right(T x) = 0;

};