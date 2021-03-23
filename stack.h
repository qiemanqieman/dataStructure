#pragma once
class operateEmptyStackError{
    const char* what() const {return "Can not operate on empty stack";}
};
template <class elemType>
class stack{
	public:
		virtual bool empty() const = 0;
		virtual elemType top() const = 0;
		virtual void push(const elemType &x) = 0;
		virtual elemType pop() = 0;
		virtual ~stack(){};
};

