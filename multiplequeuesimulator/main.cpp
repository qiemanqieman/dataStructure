#include <iostream>
using namespace std;
//#include "simulator.h"
//int main()
//{
//    simulator sim;
//    cout << "平均等待时间："
//         << sim.avgWaitTime() << endl;
//    return 0;
//}
//



#include <cstdio>

struct fln

{
    int fs[2];
    double xs;
};

int n,num = 0;
fln bb[20000];


int gcd(int a,int b) //获取两个数的最大公因数
{
    if (b == 0)
        return a;
    else
        return gcd(b,a % b);

}

void input_data()
{
    scanf("%d",&n);
}

void get_ans()
{
    for (int i = 1;i <= n;i++)
        for (int j = i+1;j <= n;j++) //获取i和j 即i/j ,其中i < j，且i,j互质
            if (gcd(i,j) == 1)
            {
                num++;
                bb[num].fs[0] = i; //fs代表分数
                bb[num].fs[1] = j;
                double aa = (double) i;
                double cc = (double) j;
                double temp = aa / cc;
                bb[num].xs = temp; //记录小数
            }
    bb[++num].fs[0] = 0;  //把 0/1 和 1/1加入数组中.
    bb[num].fs[1] = 1;
    bb[num].xs =0.0;
    bb[++num].fs[0] = 1;
    bb[num].fs[1] = 1;
    bb[num].xs = 1.0;
}

void kp(int l,int r) //以小数作为元素 进行快排。
{
    int i = l,j = r;double m = bb[(i+j)/2].xs;
    do
    {
        while (bb[i].xs < m) i++;
        while (m < bb[j].xs) j--;
        if (i <= j)
        {
            int m; //要整个交换 这一段可以写成 fln m m = bb[i];bb[i] = bb[j];bb[j] = m,这样会短很多.
            m = bb[i].fs[0];bb[i].fs[0] = bb[j].fs[0];bb[j].fs[0] = m;
            m = bb[i].fs[1];bb[i].fs[1] = bb[j].fs[1];bb[j].fs[1] = m;
            double tt;
            tt = bb[i].xs;bb[i].xs = bb[j].xs;bb[j].xs = tt;
            i++;j--;
        }
    }
    while (i <= j);
    if (l < j) kp(l,j);
    if (i < r) kp (i,r);
}




void output_ans()
{
    int m = 0;
    for (int i = 1;i <= num;i++) //控制一下输出
    {
        printf("%d/%d ",bb[i].fs[0],bb[i].fs[1]);
        m++;
        if (m == 10)
        {
            printf("\n");
            m = 0;
        }
    }
}

int main() {
    input_data();
//    int k;
//    cin >> k;
    get_ans();
    kp(1, num);
    output_ans();
//    printf("%d/%d ",bb[num - k].fs[0],bb[num - k].fs[1]);
    return 0;
}