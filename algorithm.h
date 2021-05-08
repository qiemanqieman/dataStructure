/* algorithm library*/

#pragma once
/*  KMP algorithm:
 * find whether sting b in a, if in, return the first position in b, else return -1*/
int find_sub_string(const char *a, const char *b){
    int a_len = 0, b_len = 0;
    const char *tmp = a;
    while((*tmp++)) a_len++;
    tmp = b;
    while(*tmp++) ++b_len;
    int *p = new int[b_len] ;// 存放失效函数
    int i, j;

    //生成失效函数
    p[0] = -1;
    for (i = 1; i < b_len; ++i){
        j = i - 1;
        if (j >= 0 and b[p[j] + 1] != a[i]) j = p[j];
        if (j < 0) p[i] = -1;
        else p[i] = p[j] + 1;
    }

    //查找
    i = j = 0;
    while(i < a_len and j < b_len){
        if (a[i] == b[j]) ++i, ++j;
        else if (j == 0) ++i;
        else j = p[j] + 1;
    }

    delete[] p;
    if (j == b_len) return i - j;
    else return -1;
}

//集合结构体
template <class KEY, class OTHER>
struct SET {
    KEY key;  //如学号
    OTHER other; //包含姓名、性别、出生日期等的结构体变量
};

//静态表二分查找
template <class KEY, class OTHER>
int binarySearch(SET<KEY, OTHER> data[], int size, const KEY &x)
{   //0号下标是哨兵位，不存数据，在顺序查找中，利用哨兵可以减少n次比较
    int low = 1,  high = size, mid;
    while (low <= high ) {                 //查找区间存在
        mid = (low + high) / 2;         //计算中间位置
        if ( x == data[mid].key )  return mid;
        if ( x < data[mid].key) high = mid - 1;
        else low = mid + 1;
    }
    return 0;  //0表示没有找到
}
