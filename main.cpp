//#include "sort.h"
#include "avltree.h"
#include <iostream>
using namespace std;

int main()
{
    avlTree<int, int> bs;
    for (int i = 0; i < 10; ++i)
        bs.insert(SET<int, int>(i,i));
    bs.preOrder();

}
