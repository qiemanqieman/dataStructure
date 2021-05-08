#include <stdio.h>
#include "bracketsStack.h"
using namespace std;

int main(){
    char c;
    bracketsStack s;
    cin >> c;
    while(c != '\0'){
        s.push(c);
        cin >> c;
    }
    if (s.matching()) cout << 1;
    else cout << 0;
}