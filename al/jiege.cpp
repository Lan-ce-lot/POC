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

int main() {
    n = read(), k = read();
    int t = n - 1;
    memset(h, 0, sizeof h);
    while (t--) {
        int a = read(), b = read();
        add(a, b);
    }
    return 0;
}




