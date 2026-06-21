/**
 * https://www.luogu.com.cn/problem/P3868
 *
 * @File:   P3868.cpp
 * @Author: Lao Zhang samuelzhang77@outlook.com
 * @Date:   2026-05-01
 *
 */
#include <iostream>
#include <vector>
using namespace std;

typedef long long ll;

// 扩展欧几里得：求 a 在模 m 下的逆元（gcd(a,m)=1）
ll mod_inv(ll a, ll m) {
    ll m0 = m, t, q;
    ll x0 = 0, x1 = 1;
    if (m == 1) return 0;
    while (a > 1) {
        q = a / m;
        t = m;
        m = a % m;
        a = t;
        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }
    if (x1 < 0) x1 += m0;
    return x1;
}

// 中国剩余定理：求解 x ≡ a_i (mod b_i) 的最小非负解
ll crt(const vector<ll>& a, const vector<ll>& b) {
    __int128 M = 1;          // 所有模数的乘积，用 __int128 防止计算时溢出
    for (ll x : b) M *= x;

    __int128 ans = 0;
    for (size_t i = 0; i < a.size(); ++i) {
        __int128 Mi = M / b[i];
        ll inv = mod_inv((ll)(Mi % b[i]), b[i]);  // 关键：先取模再求逆
        ans = (ans + (__int128)a[i] * Mi % M * inv) % M;
    }
    return (ll)ans;
}

int main() {
    int k;
    cin >> k;
    vector<ll> a(k), b(k);
    for (int i = 0; i < k; ++i) cin >> a[i];   // 余数
    for (int i = 0; i < k; ++i) cin >> b[i];   // 模数

    // 将余数调整到 [0, b[i]) 范围内，方便处理负数
    for (int i = 0; i < k; ++i) {
        a[i] = (a[i] % b[i] + b[i]) % b[i];
    }

    ll result = crt(a, b);
    cout << result << endl;

    return 0;
}
