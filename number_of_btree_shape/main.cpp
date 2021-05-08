#include <iostream>
using namespace std;


int main(){
    int n;
    cin >> n;
    if (n == 0 or n == 1) {cout << 1; return 0;}
    auto *no_shape = new unsigned long[n + 1];
    no_shape[0] = no_shape[1] = 1;
    int i = 1;
    while (++i <= n){
        no_shape[i] = 0;
        for (int j = 0; j < i/2; ++j){
            no_shape[i] += no_shape[j] * no_shape[i-1-j] * 2 % 1000000007;
            no_shape[i] %= (1000000007);
        }
        if (i % 2) {
            no_shape[i] += no_shape[i/2] * no_shape[i/2] % 1000000007;
            no_shape[i] %= (1000000007);
        }

    }
    cout << no_shape[n];
    return 0;
}
