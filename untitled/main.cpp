#include <list>
#include <iostream>
using namespace std;

int main(){
    list<char> l;
    for (int i = 0; i < 30100; ++i){
        l.push_front(i * i * i % 26 + 55);
    }
    auto it = l.begin();


    cout << *l.begin() << endl << l.size() << endl << *l.end() << endl << *l.rend();
}