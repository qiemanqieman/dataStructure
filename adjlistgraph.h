#pragma once
#include "graph.h"


template <class TypeOfVer, class TypeOfEdge>
class adjListGraph:public graph<TypeOfVer, TypeOfEdge> {
    adjListGraph(int vSize, const TypeOfVer d[]);
    ~adjListGraph();
    void insert(TypeOfVer x, TypeOfVer y, TypeOfEdge w);
    void remove(TypeOfVer x, TypeOfVer y);
    bool exist(TypeOfVer x, TypeOfVer y) const;

private:   //总共５个数据成员
    struct edgeNode{
        int end; TypeOfEdge weight; edgeNode* next;
        edgeNode(int e, TypeOfEdge w, edgeNode* n = nullptr): end(e), weight(w), next(n){}
    };

    struct verNode{
        TypeOfVer ver; edgeNode* head;
        explicit verNode(edgeNode* h = nullptr) : head(h){}
    };

    verNode* verList;   //该类唯一属性，　尺寸继承父类
    int find(TypeOfVer v) const{
        for (int i = 0; i < this->vers; ++i)
            if (verList[i].ver == v) return i;
        return -1;  // 没有这样的顶点
    }
};

template<class TypeOfVer, class TypeOfEdge>
adjListGraph<TypeOfVer, TypeOfEdge>::adjListGraph(int vSize, const TypeOfVer *d) {
    this->vers = vSize;
    this->edges = 0;
    verList = new verNode[vSize];
    for (int i = 0; i < vSize; ++i) verList[i].ver = d[i];
}

template<class TypeOfVer, class TypeOfEdge>
adjListGraph<TypeOfVer, TypeOfEdge>::~adjListGraph() {
    edgeNode* p;
    for (int i = 0; i < this->vers; ++i){
        while((p = verList[i].head) != nullptr) {  // 总是删除首结点
            verList[i].head = p->next;
            delete p;
        }
    }
    delete [] verList;
}

template<class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::insert(TypeOfVer x, TypeOfVer y, TypeOfEdge w) {
    int u = find(x); int v = find(y);
    verList[u].head = new edgeNode(v, w, verList[u].head); //插脖子法
    ++this->edges;
}

template<class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::remove(TypeOfVer x, TypeOfVer y) {
    int u = find(x); int v = find(y);
    edgeNode* p = verList[u].head, *q;
    if (!p) return;
    if (p->end == v) {
        verList[u].head = p->next;
        delete p;
        --this->edges;
        return;
    }
    while(p->next != nullptr and p->next->end != v) p = p->next;
    if (p->next){
        q = p->next;
        p->next = q->next;
        delete q;
        --this->edges;
    }
}

template<class TypeOfVer, class TypeOfEdge>
bool adjListGraph<TypeOfVer, TypeOfEdge>::exist(TypeOfVer x, TypeOfVer y) const {
    int u = find(x); int v = find(y);
    if (u == -1 or v == -1) return false; //　顶点x或顶点y不存在
    edgeNode* p = verList[u].head;
    while (p and p->end != v) p = p->next;
    if (p) return true;
    return false;
}
