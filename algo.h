/* algorithm libraray*/


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