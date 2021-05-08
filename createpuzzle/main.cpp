#include <iostream>
#include "../disjointset.h"
using namespace std;


void create_puzzle(int size){   // 生成N阶迷宫，入口左上角，出口右下角
    int num1, num2;
    disJointSet ds(size*size);
    int count = 0;
    srand(time(nullptr));

    while(ds.find(0) != ds.find(size*size - 1)){
        while(true){
            num1 = rand() % (size * size);
            num2 = num1 - size;
            if (num2 >= 0 and ds.find(num1) != ds.find(num2)) break;
            num2 = num1 - 1;
            if (num1 % size != 0 and ds.find(num1) != ds.find(num2)) break;
            num2 = num1 + size;
            if (num2 < size * size and ds.find(num1) != ds.find(num2)) break;
            num2 = num1 + 1;
            if (num2 % size != 0 and ds.find(num1) != ds.find(num2)) break;
        }
        ds.merge(ds.find(num1), ds.find(num2));
        cout << '<' << num1 << ',' << num2 << '>' << ", ";
        ++count;
        if (!(count % 10)) cout << '\n';

    }
    cout << "\b\b";
}
int main() {
    create_puzzle(10);
    return 0;
}
