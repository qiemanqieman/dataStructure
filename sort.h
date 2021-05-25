#pragma once


//集合
template <class KEY, class OTHER>
struct SET {
    KEY key;  //如学号
    [[maybe_unused]] OTHER other; //包含姓名、性别、出生日期等的结构体变量
    SET() = default;
    SET(KEY k, OTHER o) {key = k; other = o;}
    bool operator<(const SET &x){return this->key < x.key;}
};


//选择排序＃＃＃＃＃＃＃＃＃＃＃＃＃＃＃＃＃＃＃＃＃＃
//直接插入排序 升序  稳定
template <class KEY, class OTHER>
void simple_insert_sort(SET<KEY, OTHER> a[], int size){
    int i, j;
    for (i = 1; i < size; ++i){
        SET<KEY,OTHER> tmp = a[i];
        for (j = i; j > 0 and tmp.key < a[j-1].key; --j) a[j] = a[j-1];
        a[j] = tmp;
    }
}

//希尔排序
template <class KEY, class OTHER>
void shell_sort(SET<KEY, OTHER> a[], int size){
    int i,j;
    for (int gap = size/2; gap > 0; gap /= 2)
        for (i = gap; i < size; ++i){
            SET<KEY, OTHER> tmp = a[i];
            for (j = i - gap; j >= 0 and a[j].key > tmp.key; j -= gap) a[j+gap] = a[j];
            a[j+gap] = tmp;
        }
}



//选择排序＃＃＃＃＃＃＃＃＃＃＃＃＃＃＃＃
//直接选择排序
template <class KEY, class OTHER>
void simple_select_sort(SET<KEY, OTHER> a[], int size){
    int min;
    SET<KEY, OTHER> tmp;
    for(int i = 0; i < size-1; ++i){
        min = i;
        for (int j = i + 1; j < size; ++j){
            if (a[j].key < a[min].key) min = j;
        }
        tmp = a[min];
        a[min] = a[i];
        a[i] = tmp;
    }
}

//堆排序
template <class KEY, class OTHER> //为了获得升序的数组，使用大顶堆，因为最后得到的数组是逆序的
void percolate_down(SET<KEY, OTHER> a[], int hole, int size){
    int child;
    SET<KEY, OTHER> tmp = a[hole];

    for (; hole*2 + 1 < size; hole = child){
        child = hole * 2 + 1;
        if (child != size - 1 and a[child + 1].key > a[child].key) ++child;
        if (a[child].key > tmp.key) a[hole] = a[child];
        else break;
    }
    a[hole] =tmp;
}

template <class KEY, class OTHER>
void heap_sort(SET<KEY, OTHER> a[], int size){
    int i;
    SET<KEY, OTHER> tmp;
    for (i = (size - 1) / 2; i >= 0; --i) percolate_down(a, i, size);
    for (i = size - 1; i >= 0; --i){
        tmp =a[0]; a[0] = a[i]; a[i] = tmp;
        percolate_down(a, 0, i);
    }
}


//交换排序＃＃＃＃＃＃＃＃＃＃＃＃＃＃＃＃＃＃＃＃＃＃＃＃＃＃
//冒泡排序
template <class KEY, class OTHER>
void bubble_sort(SET<KEY, OTHER> a[], int size){
    bool flag = true;
    int i, j;
    SET<KEY, OTHER> tmp;
    for (i = 1; i < size and flag; ++i){
        flag = false;
        for (j = 0; j < size - i; ++j)
            if ( a[j+1].key < a[j].key ) { tmp = a[j]; a[j] = a[j + 1]; a[j + 1] = tmp; flag = true;}
    }
}

//快速排序
template <class KEY, class OTHER>
int divide(SET<KEY, OTHER> a[], int low , int high){
    SET<KEY, OTHER> tmp = a[low];
    do{
        while(low < high and a[high].key >= tmp.key) --high;
        if (low < high) { a[low] = a[high]; ++low;}
        while(low < high and a[low].key <= tmp.key) ++low;
        if (low < high) { a[high] = a[low]; --high;}
    } while(low != high);
    a[low] = tmp;
    return low;
}

template <class KEY, class OTHER>
void quick_sort(SET<KEY, OTHER> a[], int low, int high){
    if (low >= high) return;
    int mid = divide(a, low, high);
    quick_sort(a,low, mid-1);
    quick_sort(a,mid+1, high);
}

template <class KEY, class OTHER>
void quick_sort(SET<KEY, OTHER> a[], int size) {
    quick_sort(a, 0, size - 1);
}



//归并排序＃＃＃＃＃＃＃＃＃＃　递归　分治＃＃＃＃＃＃＃＃＃＃＃＃＃＃＃＃＃＃＃＃＃＃＃＃
template <class KEY, class OTHER>
void merge(SET<KEY, OTHER> a[], int left, int mid, int right){
    auto* tmp = new SET<KEY,OTHER>[right - left + 1];
    int p = left, q = mid, i = 0;
    while(p < mid and q <= right){
        if (a[p] < a[q]) tmp[i++] = a[p++];
        else tmp[i++] = a[q++];
    }
    while(p < mid) tmp[i++] = a[p++];
    while(q <= right) tmp[i++] = a[q++];
    for (p = left , q = 0; p <= right; ) a[p++] = tmp[q++];
    delete [] tmp;
}

template <class KEY, class OTHER>
void merge_sort(SET<KEY, OTHER> a[], int left, int right){
    if (left == right) return;
    int mid = (left + right) / 2;
    merge_sort(a, left, mid);
    merge_sort(a, mid + 1, right);
    merge(a, left, mid + 1, right);
}

template <class KEY, class OTHER>
void merge_sort(SET<KEY, OTHER> a[], int size){
    merge_sort(a, 0, size - 1);
}


//基数排序 ＃＃＃＃仅适用于数值型关键字＃＃＃＃＃＃＃＃＃＃＃＃＃＃
template <class OTHER>
struct node {   //链表中的结点类的定义
    SET<int, OTHER> data;
    node *next;

    node() { next = nullptr; }
    explicit  node(SET<int, OTHER> d): data(d) { next = nullptr; }
};

template <class OTHER>
void bucket_sort(node<OTHER> *&p)                // p是链表头
{
    node<OTHER> *bucket[10], *last[10], *tail ;
    int i, j, k, base = 1, max = 0, len = 0;
    for (tail = p; tail != nullptr; tail = tail->next)        // 找最大键值
        if (tail->data.key > max) max = tail->data.key;

    // 寻找最大键值的位数
    if (max == 0) len = 0;
    else while (max > 0) { ++len; max /= 10; }
    for (i = 1; i <= len; ++i) {   // 执行len次的分配与重组
        for (j = 0; j <= 9; ++j) bucket[j] = last[j] = nullptr;
        while (p != nullptr) {    // 执行一次分配
            k = p->data.key / base % 10;
            if (bucket[k] == nullptr)  bucket[k] = last[k] = p;
            else last[k] = last[k]->next = p;
            p = p->next;
        }
        p = nullptr;   // 重组后的链表头
        for (j = 0; j <= 9; ++j) {  // 执行重组
            if (bucket[j] == nullptr) continue;
            if (p == nullptr)  p = bucket[j];
            else tail->next = bucket[j];
            tail = last[j];
        }
        tail->next = nullptr;      // 表尾置空
        base *= 10;    // 为下一次分配做准备
    }
}
