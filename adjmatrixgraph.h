#pragma once
#include "graph.h"


//基于邻接矩阵的图
//不能表示重边和自环
//计算入度的效率高
template <class TypeOfVer, class TypeOfEdge>
class adjMatrixGraph: public graph<TypeOfVer, TypeOfEdge>
{
public:
    adjMatrixGraph(int vSize, const TypeOfVer d[], TypeOfEdge noEdgeFlag, bool isDirected = false);
    ~adjMatrixGraph();
    void insert(const TypeOfVer &x, const TypeOfVer &y, TypeOfEdge w = 1);  // 如果不是加权图，默认权值w为１
    void remove(const TypeOfVer &x, const TypeOfVer &y); // delete one edge between vertex x and y
    void remove(const TypeOfVer &x);   //　delete one vertex
    bool existEdge(const TypeOfVer &x, const TypeOfVer &y) const;

private:   //总共6个数据成员,其中两个从基类继承
    TypeOfVer *ver;
    TypeOfEdge **edge;
    TypeOfEdge noEdge;
    bool directed{}; // 是否为有向图
    int find(TypeOfVer v) const{
        for (int i = 0; i < this->vers; ++i)
            if (ver[i] == v) return i;
        return -1; // 没有这样的顶点
    }
};

template <class TypeOfVer, class TypeOfEdge>
adjMatrixGraph<TypeOfVer, TypeOfEdge>::adjMatrixGraph (int vSize,  const TypeOfVer d[], const TypeOfEdge noEdgeFlag, bool isDirected){
    int i, j;
    this->vers = vSize;
    this->edges = 0;
    noEdge = noEdgeFlag;
    directed = isDirected;

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
void adjMatrixGraph<TypeOfVer, TypeOfEdge>::insert(const TypeOfVer &x, const TypeOfVer &y, TypeOfEdge w) {
    int u  = find(x); int v = find(y);
    if (u == -1 or v == -1) return;
    if (edge[u][v] != noEdge and edge[u][v] != 0) --this->edges;
    edge[u][v] = w;
    ++this->edges;
    if (!directed) edge[v][u] = w;
}

template<class TypeOfVer, class TypeOfEdge>
void adjMatrixGraph<TypeOfVer, TypeOfEdge>::remove(const TypeOfVer &x, const TypeOfVer &y) {
    int u = find(x); int v = find(y);
    if (u == -1 or v == -1 or edge[u][v] == noEdge or edge[u][v] == 0) return;
    edge[u][v] = noEdge;
    if (directed or u == v) --this->edges;
    else {
        edge[v][u] = noEdge;
        --this->edges;
    }
}

template<class TypeOfVer, class TypeOfEdge>
void adjMatrixGraph<TypeOfVer, TypeOfEdge>::remove(const TypeOfVer &x) {
    int u = find(x);
    if (u == -1) return;
    int n1 = 0, n2 = 0;
    for (int i = 0; i < this->vers; ++i) {
        if (edge[u][i] != noEdge and edge[u][i] != 0) ++n1;
        if (edge[i][u] != noEdge and edge[i][u] != 0) ++n2;
    }
    if (directed) this->edges -= (n1 + n2);
    else this->edges -= n1;
    --this->vers;
    delete [] edge[u];

    for (int i = u; i < this->vers; ++i) {
        ver[i] = ver[i + 1];
        edge[i] = edge[i + 1];
    }
    for (int i = 0; i < this->vers; ++i)
        for (int j = u; j < this->vers; ++j)
            edge[i][j] = edge[i][j + 1];
}

template<class TypeOfVer, class TypeOfEdge>
bool adjMatrixGraph<TypeOfVer, TypeOfEdge>::existEdge(const TypeOfVer &x, const TypeOfVer &y) const {
    int u = find(x); int v = find(y);
    if (u == -1 or v == -1) return false;
    if (edge[u][v] == noEdge or edge[u][v] == 0) return false;
    return true;
}

