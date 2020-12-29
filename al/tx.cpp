//
// Created by Lance on 2020/12/8.
//

/**
* @Description:
* @author lance
* @version V1.0
*/

#include <bits/stdc++.h>

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

ll read() {
    ll x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}

ll t, n, ans = 0;

vector<PII> V;

bool cmp(PII a, PII b) {
    if (a.y != b.y) {
        return a.y < b.y;
    }
    return a.x < b.x;
}

/*
 4
 1 2
 3 5
 1 4
 4 5


 5
 1 2
 2 3
 3 4
 1 5
 5 10
 */
int dp[maxn];
void solve() {
    // 1.sort -> l,
    // 2.sort -> r,
    n = read();
    int maxx = -INF;
    for (int i = 0; i < n; i++) {
        V.push_back({read(), read()});
    }
    sort(V.begin(), V.end(), cmp);
//    for (int i = 0; i < n; i++) {
//        cout << V[i].x << ' ' << V[i].y << endl;
//    }
    for (int i = 0; i < n; i++) {
        dp[V[i].y] = max(V[i].y - V[i].x + dp[V[i].x], dp[V[i].y]);
//        if ((V[i].y - V[i].x) + dp[V[i].x] < dp[V[i].y]) {
//            dp[V[i].y] = V[i].y - V[i].x + dp[V[i].x];
//        }
    }
    for (int i = 0; i < 50005; i++) {
        ans = max(ans, 1ll* dp[i]);
    }
    printf("%d\n", ans);
}

int main() {
    const string list[6][7] = {{"", "i", "+", "*", "(", ")", "#"},
                               {"E", "TA", "", "", "TA", "", ""},
                               {"A", "", "+TA", "", "", "@", "@"},
                               {"T", "FB", "", "", "FB", "", ""},
                               {"B", "", "@", "*FB", "", "@", "@"},
                               {"F", "i", "", "", "(E)", "", ""}};
    for (int i = 0; i < 6; i ++) {
        for (int j = 0; j < 7; j++) {
            cout << list[i][j] << ' ';
        }
    }
//    string st[10][10] = {"1111", "111" ,"111"};
//    cout << st[0][1][1] << endl;
//    freopen("F:/Overflow/in.txt","r",stdin);
//    ios::sync_with_stdio(false);
//    solve();
    return 0;
}