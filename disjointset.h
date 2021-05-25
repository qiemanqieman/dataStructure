#pragma once


//不相交集　　　并查集    等价类（离散数学里的概念：自反对称传递性）
//适用于生成迷宫问题，迷宫可抽象为等价类
class disJointSet{
    int size;
    int *parent;

public:
    explicit disJointSet(int s = 11);
    ~disJointSet(){delete [] parent;}
    void merge(int root1, int root2);   //　按规模并－－－优化的合并方法， 每一个等价类（不相交集）的根节点保存的是规模的负值
    int find(int x);   //　路径压缩－－－优化的查找方法，递归，回溯时更新路径上每一个结点的父亲为根结点
};

disJointSet::disJointSet(int s): size(s){
    parent = new int[size];
    for (int i = 0; i < size; ++i) parent[i] = -1;
}

void disJointSet::merge(int root1, int root2) {
    if (root1 == root2) return;
    if (parent[root1] > parent[root2]) {
        parent[root2] += parent[root1];
        parent[root1] = root2;
        return;
    }
    parent[root1] += parent[root2];
    parent[root2] = root1;
}

int disJointSet::find(int x) {
    if (parent[x] < 0) return x;
    return parent[x] = find(parent[x]);
}

