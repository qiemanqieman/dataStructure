
#include <iostream>
using namespace std;
struct node{
    int end;
    node* next;
    int size;
    node(int e = 0, node* n = nullptr, s= 0){end = e; next = n; size = s;}
};

class road{
    int length;
    node * data;

public:
    road(int l){ length= l;data = new node[n+1];}
    void create(){
        int s,e;
        for (int i = 1; i < length+1; ++i){
            cin >> s >> e;
            if (s > e) { tmp = s; s = e; e = tmp;}
            data[s] = new node(e,data[s].next, data[s].size + 1);
        }
    }
    double getLen(int start_node){
        int ans = 0.0;
        node* p = data[start_node].next;
        if (!p) return 0.0;
        for (int i = 0; i < data[start_node].size; ++i){
            ans += 1.0/size *getLen(p->end);
        }
        return ans;
    }
};
int main(){
    int n;
    cin >> n;
    road r(n);
    r.create();

    cout << r.getLen(1);
}