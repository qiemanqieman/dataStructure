#include <iostream>
#include "cycleddoublelinklist.h"
using namespace std;

int main() {
    cdLinkList<int> ls;
    for (int i = 0; i < 10; ++i)
        ls.insert(i, i*i*i);
    ls.traverse();
    ls.traverse_reversed();
    ls.reverse();
    ls.traverse();
    ls.traverse_reversed();
    std::cout << ls.length() << std::endl;
    ls.traverse();
    ls.remove(5);
    ls.traverse();
    cout << ls.length();
    cdLinkList<int>::iterator it = ls.begin();
    for (int i = 0; i < 4; ++i) ++it;
    ls.remove(it);
    ls.traverse();
    it = ls.end();
    it--; --it;
    ls.remove(it);
    ls.traverse();
    cout << ls.length();
    ls.insert(7,23);
    ls.traverse();
    cout << ls.empty();
    ls.clear();
    cout << ls.empty();
    return 0;
}
