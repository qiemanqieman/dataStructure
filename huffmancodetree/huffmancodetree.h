//
// Created by q on 3/30/21.
//

#ifndef DATASTRUCTURE_HUFFMANCODETREE_H
#define DATASTRUCTURE_HUFFMANCODETREE_H


template <class T>
class hfTree {
private:
    struct node{
        T data;
        int weight;
        int parent, left, right;
    };
    node *elem;
    int length;

public:
    struct hfCode{
        T data;
        std::string code;
    };
    hfTree(const T *x, const int *w, int size);
    ~hfTree(){delete [] elem;}
    void get_code(hfCode *hf_code_table) const;
};

template <class T>
hfTree<T>::hfTree(const T *v, const int *w, int size) {
    const int MAX_INT = 32767;
    length = 2 * size;
    elem = new node[length];
    int min1, min2;  //　最小树,次小树的权值
    int x, y;   // 最小树,次小树的下标
    for (int i = size; i < length; ++i){
        elem[i].weight = w[i - size];
        elem[i].data = v[i - size];
        elem[i].parent = elem[i].left = elem[i].right = 0;
    }

    for (int i = size - 1; i > 0; --i){
        min1 = min2 = MAX_INT;
        x = y = 0;
        for (int j = i + 1; j < length; ++j){
            if (elem[j].parent == 0){
                if (elem[j].weight < min1){
                    min2 = min1;
                    min1 = elem[j].weight;
                    y = x;
                    x = j;
                }
                else if (elem[j].weight < min2){
                    min2 = elem[j].weight;
                    y = j;
                }
            }
        }
        elem[i].weight = min1 + min2;
        elem[i].left = x;
        elem[i].right = y;
        elem[i].parent = 0;
        elem[x].parent = i;
        elem[y].parent = i;
    }
}

template <class T>
void hfTree<T>::get_code(hfCode *hf_code_table) const {
    int size = length / 2;
    for (int i = size; i < length; ++i){
        hf_code_table[i - size].data = elem[i].data;
        hf_code_table[i - size].code = "";
        int p = elem[i].parent, s = i;
        while(p){
            if (elem[p].left == s) hf_code_table[i - size].code = '0'+ hf_code_table[i - size].code;
            else hf_code_table[i - size].code = '1'+ hf_code_table[i - size].code;
            s = p;
            p = elem[p].parent;
        }
    }
}

#endif //DATASTRUCTURE_HUFFMANCODETREE_H
