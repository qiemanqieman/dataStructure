/* 4370 online judge
Description
设计并实现一个新的栈类，支持O(1)时间复杂度的push，pop，top，getMin操作：

push(x)——x 入栈；
pop()——堆顶元素出栈；
top()——返回栈顶元素
getMin()——求栈内最小值
Input Format
第1行：一个整数n表示共n条指令；
第2至n+1行：每行一条指令op，分为以下4中情况：

0 x : push(x)
1 : pop()
2 : top()
3 : getMin()
Output Format
对于op为2或3的情况，每行输出操作返回的整数；
若op为1、2或3时栈空，输出“Empty”（不带引号）

Sample Input
10
0 1
0 2
2
3
1
3
1
1
2
3

Sample Output
2
1
1
Empty
Empty
Empty

Limits:
0 < n <= 10^6
0 <= x < 3 * 10^9  ***************************（应该设为unsigned int 或者 long int)
 */

#pragma once


class emptyError{};


class minStack{
private:
    struct node{
        unsigned int elem;
        unsigned int min;
        node* next;
        explicit node(unsigned int e = 0, unsigned int m = 0, node* ne = nullptr) : elem(e), min(m), next(ne){}
        ~node() = default;
    };
    node* Top;
public:
    minStack(){Top = nullptr;}
    ~minStack();
    bool empty() {return Top == nullptr;}
    unsigned int top() {if (empty()) throw emptyError(); return Top->elem;}
    unsigned int getMin() {if (empty()) throw emptyError(); return Top->min;}
    void push(unsigned int x);
    void pop() {if (empty()) throw emptyError(); node* tmp = Top;Top = Top->next;delete tmp;}
};


minStack::~minStack() {
    node* p = Top, *q;
    while(p){
        q = p->next;
        delete p;
        p = q;
    }
}

void minStack::push(unsigned int x) {
    if (empty()) {Top = new node(x, x, Top); return ;}
    Top = new node(x, (x < getMin())? x : getMin(), Top);
}
