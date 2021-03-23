//
// Created by q on 3/19/21.
//

#ifndef LINEAR_QUEUE_H
#define LINEAR_QUEUE_H

template <class elemType>
class queue{
public:
    virtual ~queue() = default;
    virtual bool empty() const = 0;
    virtual elemType get_front() const = 0;
    virtual elemType get_rear() const = 0;
    virtual void push(const elemType &x) = 0;
    virtual  elemType pop() = 0;
};

#endif //LINEAR_QUEUE_H
