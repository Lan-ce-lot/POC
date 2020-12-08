//
// Created by Lance on 2020/11/21.
//

/**
* @Title: ${file_name}
* @Description: 
* @author lance
* @date ${date} ${time}
* @version V1.0
*/
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int INF = 0x3f3f3f3f;
const int maxn = 1000005;
int n, m, k;
ll read()
{
    ll x = 0,f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}

int h[maxn], e[maxn], ne[maxn], tot = 1;

void add(int a, int b) {
    e[tot] = b, ne[tot] = h[a], h[a] = tot++;
}

void dfs() {

}
int a, b;

ll gcd(int a, int b) {
    if (b) return gcd(b, a % b);
    else return a;
}

bool isP(int a) {
    if (a == 2) return 1;
    if (a == 1 || a == 0) return 0;
    for (int i = 2; i * i <= a; i++) {
        if (a % i == 0) {
            return 0;
        }
    }
    return 1;
}
/*


*/
int maxx[5], minn[5];
int map1[5][5];
int main() {

    string str;
    cin >> str;
    map<char, int> M{{'1',1}, {'2', 2}, {'3',3},{'4',4},
                     {5,'5'},{6,'6'},{'7',7},{'8',8},
                     {9,'9'},{'0',0},{'a',10},{'b',11},
                     {'c',12},{'d',13},{'e',14},{'f',15}
    };
    int ans = 0;
    for (int i = 0; i < str.size(); i++) {
        ans *= 16;
        ans += M[str[i]];
    }
    cout << ans << endl;
//    n = read();
//    for (int i = 0; i < 4; i++) {
//        for (int j = 0; j < 4; j++) {
//            map1[i][j] = read();
//        }
//    }
//    memset(maxx, -1, sizeof maxx);
//    memset(minn, -1, sizeof minn);
//
//    for (int i = 0; i < 4; i++) {
//        int MAX = -INF;
//        for (int j = 0; j < 4; j++) {
//            if (map1[i][j] > MAX) {
//                MAX = map1[i][j];
//                maxx[i] = j;
//            }
//        }
//    }
//
//    for (int i = 0; i < 4; i++) {
//        int MIN = INF;
//        for (int j = 0; j < 4; j++) {
//            if (map1[j][i] < MIN) {
//                MIN = map1[j][i];
//                minn[i] = j;
//            }
//        }
//    }
//
////    for (int i = 0; i < 4; i++) {
////        cout << minn[i] << endl;
////    }
///*
//1 2 3 4
//0 1 2 3
//-1 0 1 2
//-2 -1 0 1
//
//1 2 3 4
//2 3 4 5
//3 4 5 6
//4 5 6 7
//
//1 2 3 4
//5 6 7 8
//9 10 11 12
//13 14 15 16
//
//1 2 3 4
//4 3 2 1
//1 2 3 4
//4 3 2 1
//
//1 2 3 5
//5 3 2 1
//1 2 3 5
//5 3 2 1
// */
//    bool flag = 0;
//    for (int i = 0; i < 4; i ++) {
//        for (int j = 0; j < 4; j++) {
//            if (minn[j] == i && maxx[i] == j) {
//                cout << i + 1 << ' ' << j + 1 << ' ' << map1[i][j] << endl;
//                flag = 1;
//                break;
//            }
//        }
//    }
//    if (flag == 0) cout << -1 << endl;
    return 0;
}




