/*************************************************************************
 > FileName:
 > Author:      Lance
 > Mail:        lancelot_hcs@qq.com
 > Date:        9102.1.8
 > Description:
 ************************************************************************/
//#include <bits/stdc++.h>
//#pragma comment(linker, "/STACK:102400000,102400000")//add_stack
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <vector>
#include <cstdio>
#include <bitset>
#include <string>
#include <cmath>
#include <deque>
#include <queue>
#include <stack>
#include <map>
#include <set>
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;
const double pi = acos(-1.0);
const double eps = 1e-6;
const int mod = 1e9 + 7;
#define x first
#define y second
#define debug(a) cout << "*" << a << "*" << endl
const int INF = 0x3f3f3f3f;//int2147483647//ll9e18//unsigned ll 1e19
const int maxn = 1000005;
//sacnf("%lf") printf("%f")
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
int t, n, m, k, q;
int a[maxn], b[maxn], cost[maxn];
deque<PII> V[30];
void solve()
{

    n = read(), m = read(), k = read(), q = read();

    for (int i = 1; i <= k; i++) {
        a[i] = read();
    }


    int index = 1;
    int time = 0 + 8 * 60;
    if (k > m * n) {
        bool flag = 0;
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                V[j].push_back({a[index], index++});
            }
        }

        int minn = INF;

        int minn_i = 0;
        while (index < k) {
            for (int j = 1; j <= n; j++) {
                minn = min(minn, V[j][0].x);
//				debug(minn);
            }
            time += minn;
            for (int i = 1; i <= n && index < k; i++) {
                V[i][0].x -= minn;
//				debug(V[i][0].y);
                if (V[i][0].x == 0) {
                    if (cost[V[i][0].y] == 0)
                        cost[V[i][0].y] = time;

//					cout << cost[V[i][0].y] << ' ' << V[i][0].y << endl;
//					debug(cost[V[i][0].y]);
                    V[i].pop_front();
                    V[i].push_back({a[index], index++});
                }
            }
        }
    } else {
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                V[j].push_back({a[index], index++});
            }
        }
    }


    for (int i = 1; i <= q; i++) {
        int aaa = read();

        cout << cost[aaa] << endl;
    }



}

int main()
{

//    freopen("F:/Overflow/in.txt","r",stdin);
//    ios::sync_with_stdio(false);
    solve();
    return 0;
}