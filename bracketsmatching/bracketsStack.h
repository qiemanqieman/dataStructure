/*1605. Brackets Stack
Description
模拟一个括号栈，其元素是三种括号()、[]、{}。

给出长为n的操作序列，按序列要求完成以下几种操作：

1. push
2. pop（栈空则忽略此操作）
3. 输出栈顶元素（栈空则忽略此操作）
4. 询问当前括号是否匹配（栈空则认为匹配）(要求时间复杂度为O(1))
Input Format
第1行一个整数n，代表总共有n次操作。

第2~n+1行，每行1个整数，第一个数代表操作种类，对于操作1，在同行给定一个入栈元素。

Output Format
对于每次询问操作，输出一行代表答案。

操作3：输出栈顶元素

操作4：匹配输出“YES”,否则输出“NO”

e.g.

{[()]} 匹配

{[}] 不匹配

*/




#ifndef seqstack_BRACKETSSTACK_H
#define seqstack_BRACKETSSTACK_H


#include "../seqstack.h"


class bracketsStack{
private:
    seqStack<char> brackets;
    seqStack<char> assis;
public:
    bracketsStack() = default;
    ~bracketsStack() = default;
    void push(char e);
    void pop();
    [[nodiscard]] char top() const {return brackets.top();}
    [[nodiscard]] bool matching() const {return assis.empty();}
};

void bracketsStack::push(char e) {
    brackets.push(e);
    if (!assis.empty() and assis.top() == '#') { assis.push('#'); return;}
    if (e == '(' or e == '[' or e == '{'){
        assis.push(e);
        return;
    }
    if (assis.empty()) {assis.push('#'); return;}
    char tmp = assis.top();
    if (e == ')' and tmp == '(' or e == ']' and tmp == '[' or e == '}' and tmp == '{')
        assis.pop();
    else assis.push('#');
}

void bracketsStack::pop() {
    if (brackets.empty())
        return;
    char b = brackets.pop();
    if (!assis.empty()and assis.top() == '#') {
        assis.pop();
        return;
    }
    switch(b){
        case '(':
        case '[':
        case '{':{assis.pop(); break;}
        case ')':{assis.push('('); break;}
        case ']':{assis.push('['); break;}
        case '}':{assis.push('{'); break;}
        default: break;
    }

}

#endif //seqstack_BRACKETSSTACK_H
