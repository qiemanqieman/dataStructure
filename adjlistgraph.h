#pragma once
#include "graph.h"
#include "linkStack.h"
#include "linkqueue.h"
#include <iostream>
using namespace std;

//基于邻接表的图
//可表示重边和自环
//计算入度时间复杂度高于基于邻接矩阵图
template <class TypeOfVer, class TypeOfEdge>
class adjListGraph:public graph<TypeOfVer, TypeOfEdge> {
private:
    struct edgeNode{
        int end; TypeOfEdge weight; edgeNode* next;
        edgeNode(int e, TypeOfEdge w, edgeNode* n = nullptr): end(e), weight(w), next(n){}
    };

    struct verNode{
        TypeOfVer ver; edgeNode* head;  //head 是不带头结点的　edgeNode 链表
        explicit verNode(edgeNode* h = nullptr) : head(h){}
    };

    struct eulerNode{
        int nodeNum;
        eulerNode *next;
        explicit eulerNode(int ver) {nodeNum = ver; next = nullptr;}
    };

public:
    adjListGraph(int vSize, const TypeOfVer d[], bool isDirected = false); // 默认为无向图
    ~adjListGraph();
    void insert(const TypeOfVer &x, const TypeOfVer &y, TypeOfEdge w = 1); //添加边； w默认为１，用于表示无权图
    void insert(const TypeOfVer &x); //　添加顶点
    void remove(const TypeOfVer &x, const TypeOfVer &y); // 删除边
    void remove(const TypeOfVer &x); // 删除顶点
    bool existEdge(const TypeOfVer &x, const TypeOfVer &y) const;
    int numOfEdgesBetween(const TypeOfVer &x, const TypeOfVer &y) const;
    int outDegree(const TypeOfVer &x) const;
    int inDegree(const TypeOfVer &x) const;
    int degree(const TypeOfVer &x) const; //有向图自环贡献２度，一个入度，一个出度，无向图自环对度的贡献为２
    void dfs(int recursive = 0) const;  //深度优先搜索（遍历)；　是树的前序遍历的推广；　默认使用非递归算法
    void bfs() const; // 是树的层次遍历的推广；　非递归
    bool haveRoad(const TypeOfVer &x, const TypeOfVer &y) const; // 判断是否存在道路
    [[nodiscard]] bool isConnected(bool verbose = false) const ; // 判断是否为连通图（对于有向图，指的是强连通；verbose = true 列出强连通分量
    void eulerCircuit(const TypeOfVer &start); // 输出无向图欧拉回路
    void topSort() const; //　输出有向图拓扑排序

private:
    int find(const TypeOfVer &v) const;  // **********找到顶点v的下标
    void doubleSpace();
    void dfsNonRecursive() const; //　基于非递归的深度优先搜索工具函数
    void dfsRecursive(int start, bool visited[]) const; // 基于递归的深度优先搜索工具函数
    void DFS(int start, bool visited[], bool verbose = false) const;
    [[nodiscard]] bool exist(int u, int v) const;
    [[nodiscard]] bool haveRoad(int u, int v, bool visited[]) const; //　flag 仅用于区别公有函数
    int remove(int u, int v, int flag); // flag 用于标记被哪一个公用remove函数调用
    void remove(int u, int v, char c); // 移除u到v的第一条边
    [[nodiscard]] bool isConnectedUndirected(bool verbose = false) const;  //　判断无向图是否连通
    [[nodiscard]] bool isConnectedDirected(bool verbose = false) const; //　判断有向图是否连通
    void eulerCircuit(int start, eulerNode *&beg, eulerNode *&end);
    verNode* clone() const;

private:
    verNode* verList;
    int maxSizeOfVertex;
    bool directed; // 是否为有向图
};

template<class TypeOfVer, class TypeOfEdge>
adjListGraph<TypeOfVer, TypeOfEdge>::adjListGraph(int vSize, const TypeOfVer *d, bool isDirected) {
    this->vers = vSize;
    this->edges = 0;
    maxSizeOfVertex = 2 * vSize;
    directed = isDirected;
    verList = new verNode[maxSizeOfVertex];
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
void adjListGraph<TypeOfVer, TypeOfEdge>::insert(const TypeOfVer &x, const TypeOfVer &y, TypeOfEdge w) {
    int u = find(x); int v = find(y);
    if (u == -1 or v == -1) return;
    verList[u].head = new edgeNode(v, w, verList[u].head); //插脖子法
    ++this->edges;
    if (!directed) verList[v].head = new edgeNode(u, w, verList[v].head); //如果是无向图
}

template<class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::insert(const TypeOfVer &x) {
    if (find(x) != -1) return;
    if (this->vers == maxSizeOfVertex) doubleSpace();
    verList[this->vers].ver = x;
    verList[this->vers].head = nullptr;
    ++this->vers;
}

template<class TypeOfVer, class TypeOfEdge>
int adjListGraph<TypeOfVer, TypeOfEdge>::remove(int u, int v, int flag) {
    edgeNode* p = verList[u].head, *q;
    int res = 0;
    while (p and p->end == v) {  //不带头结点，所以第一个结点特殊处理
        q = verList[u].head = p->next;
        delete p;
        p = q;
        ++res;
    }
    if (!p) return res;

    if (flag and p->end > v) p->end -= 1; //　如果是remove顶点调用了该函数，则end > v时，应该减小１
    while(p->next){ // 遍历从顶点u出发的所有的边，因为可能会有重边
        while(p->next and p->next->end != v) {  // 找到满足要求的边
            p = p->next;
            if (flag and p->end > v) p->end -= 1;
        }
        if (p->next){
            q = p->next;
            p->next = q->next;
            delete q;
            ++res;
        }
    }
    return res; //返回u指向v的所有边的数量
}

template<class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::remove(int u, int v, char c) {
    edgeNode *p = verList[u].head, *q;
    bool flag = true;
    if (p->end == v) {verList[u].head = p->next; flag = false; delete p; }
    while(flag and p->next) {
        if (p->next->end == v){
            q = p->next;
            p->next = q->next;
            delete q;
            flag = false;
        }
        p = p->next;
    }
    if (!directed){
        p = verList[v].head;
        flag = true;
        if (p->end == u) {verList[v].head = p->next; flag = false; delete p; }
        while(flag and p->next) {
            if (p->next->end == u){
                q = p->next;
                p->next = q->next;
                delete q;
                flag = false;
            }
            p = p->next;
        }
    }
    --this->edges;
}

template<class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::remove(const TypeOfVer &x, const TypeOfVer &y) {
    int u = find(x); int v = find(y);
    if (u == -1 or v == -1) return;
    this->edges -= remove(u, v, 0);
    if (!directed) remove(v, u, 0); //如果是无向图
}

template<class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::remove(const TypeOfVer &x) {
    int u = find(x);
    if (u == -1) return;

    int n1 = 0, n2 = 0;
    edgeNode *p = verList[u].head;
    while(p) {++n1; p = p->next;}
    remove(u, u, 1);  // 移除在有向图中会导致重复计算的自环（ｕ，ｕ）
    for (int i = 0; i < this->vers; ++i)
        n2 += remove(i, u, 1);
    delete [] verList[u].head;
    --this->vers;
    if (directed) this->edges -= (n1 + n2);
    else this->edges -= n1;
    for (int i = u; i < this->vers; ++i) verList[i] = verList[i+1];
}

template<class TypeOfVer, class TypeOfEdge>
bool adjListGraph<TypeOfVer, TypeOfEdge>::exist(int u, int v) const {
    edgeNode* p = verList[u].head;
    while (p and p->end != v) p = p->next;
    if (p) return true;
    return false;
}

template<class TypeOfVer, class TypeOfEdge>
bool adjListGraph<TypeOfVer, TypeOfEdge>::existEdge(const TypeOfVer &x, const TypeOfVer &y) const {
    int u = find(x); int v = find(y);
    if (u == -1 or v == -1) return false; //　顶点x或顶点y不存在
    return exist(u, v);
}

template<class TypeOfVer, class TypeOfEdge>
int adjListGraph<TypeOfVer, TypeOfEdge>::numOfEdgesBetween(const TypeOfVer &x, const TypeOfVer &y) const {
    int u = find(x); int v = find(y);
    if (u == -1 or v == -1) return -1; //顶点不存在，用-1标记
    int res = 0;
    edgeNode *p = verList[u].head;
    while(p) {
        if (p->end == v) ++res;
        p = p->next;
    }
    return res;
}

template<class TypeOfVer, class TypeOfEdge>
int adjListGraph<TypeOfVer, TypeOfEdge>::outDegree(const TypeOfVer &x) const {  //无向图出度＝入度＝总度　
    int u = find(x);
    if (u == -1) return -1;  //顶点不存在，用-1度标记
    int res = 0;
    edgeNode *p = verList[u].head;
    while(p) {
        ++res;
        if(!directed)
            if (p->end == u)
                ++res;
        p = p->next;
    } //自环对度的贡献为２
    return res;
}

template<class TypeOfVer, class TypeOfEdge>
int adjListGraph<TypeOfVer, TypeOfEdge>::inDegree(const TypeOfVer &x) const {
    if (!directed) return outDegree(x);
    int u = find(x);
    if (u == -1) return -1;
    int res = 0;
    for (int i = 0; i < this->vers; ++i) res += numOfEdgesBetween(verList[i].ver, x);
    return res;
}

template<class TypeOfVer, class TypeOfEdge>
int adjListGraph<TypeOfVer, TypeOfEdge>::degree(const TypeOfVer &x) const {
    if (!directed) return outDegree(x);
    int u = find(x);
    if (u == -1) return -1;
    return outDegree(x) + inDegree(x);
}

template<class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::doubleSpace() {
    maxSizeOfVertex *= 2;
    verNode *tmp = verList;
    verList = new verNode[maxSizeOfVertex];
    for (int i = 0; i < this->vers; ++i) verList[i] = tmp[i];
    delete [] tmp;
}

template<class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::dfs(int recursive) const {
    cout << "当前图的深度优先遍历序列为：" << endl;
    if (recursive){
        bool visited[this->vers];
        for (int i = 0; i < this->vers; ++i) visited[i] = false;
        for (int i = 0; i < this->vers; ++i) {
            if (!visited[i]) {
                dfsRecursive(i, visited); //对于无向图，这里的调用次数代表极大连通子图数量
                cout << endl;  //对于无向图，每一行(每一次换行换行）代表一个极大连通分量（子图）
            }
        }
        return;
    }
    dfsNonRecursive();
}

template<class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::dfsNonRecursive() const {
    bool visited[this->vers];
    linkStack<int> s;
    edgeNode *p;
    int cur;
    for (int i = 0; i < this->vers; ++i) visited[i] = false;

    for (int i = 0; i < this->vers; ++i){
        if (visited[i]) continue;
        s.push(i);
        while(!s.empty()) {
            cur = s.pop();
            if (visited[cur]) continue;
            cout << verList[cur].ver << '\t';
            visited[cur] = true;
            p = verList[cur].head;
            while(p) { if (!visited[p->end]) s.push(p->end); p = p->next;}
        }
        cout << endl;
    }
}

template<class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::dfsRecursive(int start, bool *visited) const {
    edgeNode *p = verList[start].head;
    cout << verList[start].ver << '\t';
    visited[start] = true;
    while(p) {if (!visited[p->end]) dfsRecursive(p->end, visited); p = p->next;}
}

template<class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::DFS(int start, bool *visited, bool verbose) const {
    edgeNode *p = verList[start].head;
    visited[start] = true;
    if (verbose)
        cout << verList[start].ver << '\t';
    while(p) {if (!visited[p->end]) DFS(p->end, visited, verbose); p = p->next;}
}

template<class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::bfs() const {
    linkQueue<int> q;
    bool visited[this->vers];
    int i = 0, cur;
    edgeNode *p;

    for (; i < this->vers; ++i) visited[i] = false;
    cout <<  "当前图的广度优先遍历序列为：" << endl;
    for (i = 0; i < this->vers; ++i){
        if (visited[i]) continue;
        q.push(i);
        while(!q.empty()) {
            cur = q.pop();
            if (visited[cur]) continue;
            cout << verList[cur].ver << '\t';
            visited[cur] = true;
            p = verList[cur].head;
            while(p) {if (!visited[p->end]) q.push(p->end); p = p->next;}
        }
        cout << endl;
    }
}

template<class TypeOfVer, class TypeOfEdge>
bool adjListGraph<TypeOfVer, TypeOfEdge>::haveRoad(int u, int v, bool visited[]) const {
    visited[u] = true;
    if (exist(u,v)) return true;
    edgeNode *p = verList[u].head;
    while(p) {
        if (!visited[p->end] and haveRoad(p->end, v, visited)) return true;
        p = p->next;
    }
    return false;
}

template<class TypeOfVer, class TypeOfEdge>
bool adjListGraph<TypeOfVer, TypeOfEdge>::haveRoad(const TypeOfVer &x, const TypeOfVer &y) const {
    int u = find(x); int v = find(y);
    if (u == -1 or v == -1) return false;
    bool visited[this->vers];
    for (int i = 0; i < this->vers; ++i) visited[i] = false;
    return haveRoad(u, v, visited);
}

template<class TypeOfVer, class TypeOfEdge>
bool adjListGraph<TypeOfVer, TypeOfEdge>::isConnectedUndirected(bool verbose) const {
    bool visited[this->vers];
    int i, count = 0;
    for (i = 0; i < this->vers; ++i) visited[i] = false;

    for (i = 0; i < this->vers; ++i){
        if (visited[i]) continue;
        DFS(i, visited, verbose);  // 基于深度优先搜索判断是否为连通无向图，DFS在dfsRecursive函数的基础上做了很小修改
        if (verbose) cout << endl;
        ++count;
    }
    if (count == 1) return true;
    return false;
}

template<class TypeOfVer, class TypeOfEdge>
bool adjListGraph<TypeOfVer, TypeOfEdge>::isConnectedDirected(bool verbose) const {

}

template<class TypeOfVer, class TypeOfEdge>
bool adjListGraph<TypeOfVer, TypeOfEdge>::isConnected(bool verbose) const {
    if (verbose) cout << "强连通分量如下：" << endl;
    if (directed) return isConnectedDirected();
    return isConnectedUndirected(verbose);
}

template<class TypeOfVer, class TypeOfEdge>
int adjListGraph<TypeOfVer, TypeOfEdge>::find(const TypeOfVer &v) const {
    for (int i = 0; i < this->vers; ++i)
        if (verList[i].ver == v) return i;
    return -1;  // 没有这样的顶点
}

template<class TypeOfVer, class TypeOfEdge>
typename adjListGraph<TypeOfVer, TypeOfEdge>::verNode* adjListGraph<TypeOfVer, TypeOfEdge>::clone() const {
    auto *tmp = new verNode[this->vers];
    edgeNode *p;
    for (int i = 0; i < this->vers; ++i) {
        tmp[i].ver = verList[i].ver;
        p = verList[i].head;
        while(p){
            tmp[i].head = new edgeNode(p->end,p->weight, tmp[i].head);
            p = p->next;
        }
    }
    return tmp;
}

template<class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::eulerCircuit(int start, adjListGraph::eulerNode *&beg,
                                                       adjListGraph::eulerNode *&end) {
    beg = end = new eulerNode(start);
    edgeNode *p = verList[start].head, *q;
    while(p){
        end = end->next = new eulerNode(p->end);
        remove(start, p->end, 'c');
        start = end->nodeNum;
        p = verList[start].head;
    }
}

template<class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::eulerCircuit(const TypeOfVer &start) {
    int i, ed = this->edges;
    verNode *tmp;
    eulerNode *beg, *end, *p, *q, *tb, *te;
    if (this->edges == 0) {
        cout << "不存在欧拉回路" << endl;
        return;
    }
    for (i = 0; i < this->vers; ++i){
        if (degree(verList[i].ver) % 2) {
            cout << "不存在欧拉回路" << endl;
            return;
        }
    }

    i = find(start);
    tmp = clone();
    eulerCircuit(i, beg, end);
    while(true){
        p = beg;
        while(p->next)
            if (verList[p->next->nodeNum].head) break;
            else p = p->next;
        if (!p->next) break;
        q = p->next;
        eulerCircuit(q->nodeNum, tb, te);
        te->next = q->next;
        p->next = tb;
        delete q;
    }

    delete [] verList;
    verList = tmp;
    this->edges = ed;

    cout << "从" << start << "出发的欧拉回路是：" << endl;
    while(beg){
        cout << verList[beg->nodeNum].ver << "->";
        p = beg;
        beg = beg->next;
        delete p;
    }
    cout << "\b\b\n";
}

template<class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::topSort() const {
    linkQueue<int> q;
    edgeNode *p;
    int cur;
    int *inDe = new int[this->edges];

    for (int i = 0; i < this->vers; ++i)
        if ((inDe[i] = inDegree(verList[i].ver)) == 0)
            q.push(i);

    cout << "一种可能的拓扑排序为：" << endl;
    while(!q.empty()){
        cur = q.pop();
        cout << verList[cur].ver << "->";
        for (p = verList[cur].head; p; p = p->next)
            if (--inDe[p->end] == 0)
                q.push(p->end);
    }
    cout << "\b\b\n";
}






