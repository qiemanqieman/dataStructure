//
// Created by q on 3/18/21.
//

#ifndef CALCULATOR_CALCULATOR_H
#define CALCULATOR_CALCULATOR_H
#include "../linkStack.h"
#include <iostream>


class badExpressionError{};


class calculator{
private:
    const char* expression;
    enum token{OPAREN, ADD, SUB, MULTI, DIV, EXP, CPAREN, VALUE, EOL};
    static void binary_op(token op, linkStack<int> &data_stack);
    token get_op(int &value);
public:
    calculator() = default;
    explicit calculator(const char* expr): expression(expr){}
    ~calculator() = default;
    int result();
};

int calculator::result() {
    int rvalue = 0;
    token op, last_op;
    const char* tmp = expression;
    linkStack<int> data_stack;
    linkStack<token> op_stack;

    try {
        while ((op = get_op(rvalue)) != EOL) {
            switch (op) {
                case VALUE: {
                    data_stack.push(rvalue);
                    break;
                }
                case EXP: {
                    op_stack.push(op);
                    break;
                }
                case MULTI: {
                    while (!op_stack.empty() and (last_op = op_stack.top()) >= op) {
                        binary_op(last_op, data_stack);
                        op_stack.pop();
                    }
                    op_stack.push(op);
                    break;
                }
                case DIV: {
                    while (!op_stack.empty() and (last_op = op_stack.top()) + 1 >= op) {
                        binary_op(last_op, data_stack);
                        op_stack.pop();
                    }
                    op_stack.push(op);
                    break;
                }
                case ADD:
                case SUB:{
                    while(!op_stack.empty() and (op_stack.top()) != OPAREN){
                        last_op = op_stack.pop();
                        binary_op(last_op, data_stack);
                    }
                    op_stack.push(op);
                    break;
                }
                case OPAREN:{
                    op_stack.push(op); break;
                }
                case CPAREN:{
                    while((last_op = op_stack.pop()) != OPAREN){
                        binary_op(last_op, data_stack);
                    }
                    break;
                }
                case EOL:{
                    while(!op_stack.empty()){
                        last_op = op_stack.pop();
                        binary_op(last_op, data_stack);
                    }
                    break;
                }
            }
        }

        while(!op_stack.empty()){
            binary_op(op_stack.pop(), data_stack);
        }
    }
    catch(badExpressionError){
        std::cout << "unqualified expression!\n";
        return -1;
    }

    expression = tmp;
    int t = data_stack.pop();
    if (!data_stack.empty()) {
        std::cout << "unqualified expression!\n";
        return -1;
    }
    return t;
}

calculator::token calculator::get_op(int &value) {
    while(*expression and *expression == ' ') {
        ++expression;  // jump the spaces
    }
    if (!*expression) return EOL;
    if (*expression <= '9' and *expression >= '0') {
        value = 0;
        while(*expression >= '0' and *expression <= '9'){
            value = 10 * value + *expression - '0';
            ++expression;
        }
        return VALUE;
    }
    switch(*expression){
        case '(': ++expression; return OPAREN;
        case ')': ++expression; return CPAREN;
        case '+': ++expression; return ADD;
        case '-': ++expression; return SUB;
        case '*': ++expression; return MULTI;
        case '/': ++expression; return DIV;
        case '^': ++expression; return EXP;
        default:return EOL;
    }
}

void calculator::binary_op(token op, linkStack<int> &data_stack) {
    int l, r;
    try{
        r = data_stack.pop();
        l = data_stack.pop();
        switch(op){
            case EXP: {
                int t = 1;
                for (int i = 0; i < r; ++i)
                    t *= l;
                data_stack.push(t);
                break;
            }
            case MULTI:{ data_stack.push(l *r); break;}
            case DIV: { data_stack.push(l / r); break;}
            case ADD: { data_stack.push(l + r); break;}
            case SUB: { data_stack.push(l - r); break;}
            default: break;
        }
    }
    catch(operateEmptyStackError) {throw badExpressionError();}
}
#endif //CALCULATOR_CALCULATOR_H
