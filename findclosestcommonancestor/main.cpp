#include <iostream>
using namespace std;


class tree {
private:
    struct node{
        int parent, left, right;
    };
    node *elem;
    int length;

public:
    explicit tree(int n = 10);
    ~tree(){delete [] elem;}
    int fccp(int x, int y); // find the closest common parent of node x and node y;
};


tree::tree(int n) {
    length = n; int l, r, p;
    elem = new node[length+ 1];
    elem[1].parent = 0;
    int i = 0;
    while(++i <= n){
        cin >> l >> r;
        elem[i].left = l;
        elem[i].right = r;
        elem[l].parent = elem[r].parent = i;
    }
}

int tree::fccp(int x, int y) {
    int px = elem[x].parent;
    int py = elem[y].parent;
    while (px != py){
        if (px > py) px = elem[px].parent;
        else py = elem[py].parent;
    }
    return px;
}
int main() {
    int N, X, Y;
    cin >> N >> X >> Y;
    tree t(N);
    cout << t.fccp(X, Y);
    return 0;
}


