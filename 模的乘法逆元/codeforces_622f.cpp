/**
 *
 * @File:   codeforces_622f.cpp
 * @Author: Lao Zhang samuelzhang77@outlook.com
 * @Date:   2026-03-14
 *
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int MOD = 1e9 + 7;
const int MAXK = 1e6 + 10;

// 快速幂：计算 a^b % MOD
ll power(ll a, ll b) {
    ll res = 1;
    while (b > 0) {
        if (b & 1) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

// 计算逆元：a^(-1) % MOD
ll inv(ll a) {
    return power(a, MOD - 2);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    ll n, k;
    cin >> n >> k;

    int m = k + 2;  // 需要 m 个点进行插值

    // y[i] = f(i) = sum_{j=1}^{i} j^k
    vector<ll> y(m + 1, 0);

    // 计算前 m 个点的值
    for (int i = 1; i <= m; i++) {
        y[i] = (y[i-1] + power(i, k)) % MOD;
    }

    // 如果 n <= m，直接返回预计算的值
    if (n <= m) {
        cout << y[n] << '\n';
        return 0;
    }

    // 预处理前缀积和后缀积
    // pre[i] = (n-1)(n-2)...(n-i)
    // suf[i] = (n-i)(n-(i+1))...(n-m)
    vector<ll> pre(m + 2, 1), suf(m + 2, 1);
    for (int i = 1; i <= m; i++) {
        pre[i] = pre[i-1] * (n - i) % MOD;
    }
    for (int i = m; i >= 1; i--) {
        suf[i] = suf[i+1] * (n - i) % MOD;
    }

    // 预处理阶乘
    vector<ll> fact(m + 1, 1);
    for (int i = 1; i <= m; i++) {
        fact[i] = fact[i-1] * i % MOD;
    }

    // 拉格朗日插值
    ll ans = 0;
    for (int i = 1; i <= m; i++) {
        // 分子：prod_{j!=i} (n - j)
        ll numerator = pre[i-1] * suf[i+1] % MOD;

        // 分母：prod_{j!=i} (i - j)
        // = (i-1)(i-2)...(1) * (-1)(-2)...(i-m)
        // = (i-1)! * (-1)^(m-i) * (m-i)!
        ll denominator = fact[i-1] * fact[m-i] % MOD;
        if ((m - i) % 2 == 1) {
            denominator = MOD - denominator;  // 处理负号
        }

        // 拉格朗日基函数：L_i(n) = numerator / denominator
        ll Li = numerator * inv(denominator) % MOD;

        // 累加：f(n) += f(i) * L_i(n)
        ans = (ans + y[i] * Li) % MOD;
    }

    // 确保结果非负
    ans = (ans % MOD + MOD) % MOD;
    cout << ans << '\n';

    return 0;
}
