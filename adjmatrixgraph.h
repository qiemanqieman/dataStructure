#pragma once
#include "graph.h"


//基于邻接矩阵的图
template <class TypeOfVer, class TypeOfEdge>
class adjMatrixGraph: public graph<TypeOfVer, TypeOfEdge>
{
public:
    adjMatrixGraph(int vSize, const TypeOfVer d[], TypeOfEdge noEdgeFlag);
    ~adjMatrixGraph();
    void insert(TypeOfVer x, TypeOfVer y, TypeOfEdge w);
    void remove(TypeOfVer x, TypeOfVer y);
    bool exist(TypeOfVer x, TypeOfVer y) const;

private:   //总共５个数据成员
    TypeOfVer *ver;
    TypeOfEdge **edge;
    TypeOfEdge noEdge;
    int find(TypeOfVer v) const{
        for (int i = 0; i < this->vers; ++i)
            if (ver[i] == v) return i;
        return -1; // 没有这样的顶点
    }
};

template <class TypeOfVer, class TypeOfEdge>
adjMatrixGraph<TypeOfVer, TypeOfEdge>::adjMatrixGraph (int vSize,  const TypeOfVer d[], const TypeOfEdge noEdgeFlag){
    int i, j;
    this->vers = vSize;
    this->edges = 0;
    noEdge = noEdgeFlag;

    ver = new TypeOfVer[vSize];
    for (i = 0; i < vSize; ++i) ver[i] = d[i];

    edge = new TypeOfEdge*[vSize];
    for (i = 0; i < vSize; ++i){
        edge[i] = new TypeOfEdge[vSize];
        for (j = 0; j < vSize; ++j) edge[i][j] = noEdge; // noEdge 一般取无穷大，用来表示两个顶点之间代价很大，就相当于没有路径
        edge[i][i] = 0;  //结点到自身的代价为０
    }
}

template<class TypeOfVer, class TypeOfEdge>
adjMatrixGraph<TypeOfVer, TypeOfEdge>::~adjMatrixGraph() {
    delete [] ver;
    for (int i = 0; i < this->vers; ++i) delete [] edge[i];
    delete [] edge;
}

template<class TypeOfVer, class TypeOfEdge>
void adjMatrixGraph<TypeOfVer, TypeOfEdge>::insert(TypeOfVer x, TypeOfVer y, TypeOfEdge w) {
    int u  = find(x); int v = find(y);
    if (edge[u][v] != noEdge and u != v) --this->edges;
    edge[u][v] = w;
    ++this->edges;
}

template<class TypeOfVer, class TypeOfEdge>
void adjMatrixGraph<TypeOfVer, TypeOfEdge>::remove(TypeOfVer x, TypeOfVer y) {
    int u = find(x); int v = find(y);
    if (edge[u][v] == noEdge) return;
    edge[u][v] = noEdge;
    --this->edges;
}

template<class TypeOfVer, class TypeOfEdge>
bool adjMatrixGraph<TypeOfVer, TypeOfEdge>::exist(TypeOfVer x, TypeOfVer y) const {
    int u = find(x); int v = find(y);
    if (edge[u][v] == noEdge) return false;
    return true;
}

