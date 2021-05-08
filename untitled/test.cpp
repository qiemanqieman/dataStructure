//#include <list>
//#include <iostream>
//using namespace std;
//
//struct road{
//    int s, e, len;
//    road(int ss, int ee, int l){ s = ss; e = ee; len = l;}
//};
//int main(){
//    int n, k;
//    int ss, ee, l, tmp;
//    cin >> n >> k;
//    road* r = new road[n-1];
//    int dianpu[k];
//    for(int i = 0; i < n; ++i){
//        cin >> ss >> ee >> l;
//        if (ss > ee) { tmp = ss; ss = ee; ee = tmp;}
//        r[i] = road(ss,ee,l);
//    }
//    for (int i = 0; i < k; ++i) cin >> dianpu[i];
//
//
//    int min_start = 0; max_length = 0;
//    for (int i = min_start; i < n; ++i){
//        for (int j = 0; j < k; ++j)
//            if (r[i].e == dianpu[j] or r[i].s == dianpu[j]){
//                if (r[i].e == dianpu[j]) break;
//            }
//    }
//}