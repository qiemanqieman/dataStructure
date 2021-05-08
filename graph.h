#pragma once


//　抽象基类
template <class TypeOfVer, class TypeOfEdge>
class graph{
public:
    virtual void insert(TypeOfVer x, TypeOfVer y, TypeOfEdge w) = 0;
    virtual void remove(TypeOfVer x, TypeOfVer y) = 0;
    virtual bool exist(TypeOfVer x, TypeOfVer y) const = 0;
    int numOfVer() {return vers;}
    int numOfEdge() {return edges;}
    virtual ~graph()= default;

protected:
    int vers{};
    int edges{};
};

