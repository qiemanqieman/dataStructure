#include <iostream>
int main() {
    int t, s, n, total_wait_time = 0, current_time = 0;
    std::scanf("%d", &n);
    int i = n;
    while(i--){
        std::scanf("%d%d", &t, &s);
        if (t < current_time) total_wait_time += (current_time - t);
        else {current_time = t;}
        current_time += s;
    }

    std::printf("%.2f", (double)total_wait_time / (double)n);
//    std::cout << double(total_wait_time) / n;
    return 0;
}
