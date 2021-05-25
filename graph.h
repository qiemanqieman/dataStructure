#pragma once


//　抽象基类
template <class TypeOfVer, class TypeOfEdge>
class graph{
public:
    virtual void insert(const TypeOfVer &x, const TypeOfVer &y, TypeOfEdge w) = 0;
    virtual void remove(const TypeOfVer &x, const TypeOfVer &y) = 0;
    virtual bool existEdge(const TypeOfVer &x, const TypeOfVer &y) const = 0;
    int numOfVers() {return vers;}
    int numOfEdges() {return edges;}
    virtual ~graph()= default;

protected:
    int vers{};
    int edges{};
};

