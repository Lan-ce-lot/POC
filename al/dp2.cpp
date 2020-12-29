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


/*
3
 2 3 5
*/


ll a[maxn], sum = 0, dp[3005][3005];
// l, r, abandon

void solve() {
    n = read();

    for (int i = 1; i <= n; i++) {
        a[i] = read();
        sum += a[i];
    }
    memset(dp, -INF, sizeof(dp));
    dp[0][0] = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = sum; j >= 0; j--) {
            dp[i][j] = max(dp[i][j], dp[i - 1][j]); //
            dp[i][j] = max(dp[i][j], dp[i - 1][j + a[i]]);
//            debug(dp[i][j]);
            if (j >= a[i]) {
                dp[i][j] = max(dp[i][j], dp[i - 1][j - a[i]] + a[i]);
            }
            if (j <= a[i]) {
                dp[i][j] = max(dp[i][j], dp[i - 1][a[i] - j] + j);
            }
        }
    }

    printf("%d\n", dp[n][0] ? dp[n][0] : -1);
}

int main() {

//    freopen("F:/Overflow/in.txt","r",stdin);
//    ios::sync_with_stdio(false);
    solve();
    return 0;
}

