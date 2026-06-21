/**
 * Exponial - 计算 exponial(n) mod m
 *
 * 题目来源：NCPC 2016 / SPOJ
 * 解题思路：欧拉降幂 + 递归
 *
 * 关键点：
 * 1. 当 n >= 5 时，exponial(n-1) 一定 >= φ(m)，可以直接使用降幂公式
 * 2. 当 n <= 4 时，直接计算数值
 * 3. 递归过程中模数快速下降，深度 O(log m)
 *
 * @File:   Kattis_exponial.cpp
 * @Author: Lao Zhang samuelzhang77@outlook.com
 * @Date:   2026-02-23
 *
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

/**
 * 计算欧拉函数 φ(n)
 * 时间复杂度 O(√n)
 */
ll euler_phi(ll n) {
    ll ans = n;
    for (ll i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            ans = ans / i * (i - 1);
            while (n % i == 0) n /= i;
        }
    }
    if (n > 1) ans = ans / n * (n - 1);
    return ans;
}

/**
 * 快速幂取模
 * 计算 a^b % mod
 */
ll qpow(ll a, ll b, ll mod) {
    ll res = 1;
    a %= mod;
    while (b) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

/**
 * 预计算 exponial(1) 到 exponial(4) 的值
 */
const ll small_val[] = {0, 1, 2, 9, 262144};  // small_val[n] = exponial(n)

/**
 * 递归求解 f(n, m) = exponial(n) mod m
 *
 * 返回值：exponial(n) mod m
 * 注意：当 n <= 4 时，返回值可能小于 m，也可能大于等于 m
 *       我们通过返回实际值来隐式传递比较信息
 */
ll solve(ll n, ll m) {
    // 边界条件：模数为 1，任何数模 1 都是 0
    if (m == 1) return 0;

    // 小 n 直接计算
    if (n <= 4) {
        return small_val[n] % m;
    }

    // 对于 n >= 5，使用欧拉降幂
    ll phi = euler_phi(m);
    // 递归计算指数部分：exponial(n-1) mod phi，并且自动处理了是否加 phi 的问题
    // 因为当 n-1 >= 5 时，exponial(n-1) 一定 >= phi，递归会自然加上 phi
    // 当 n-1 <= 4 时，small_val[n-1] 可能小于 phi，我们在递归中已经返回实际值
    ll exponent = solve(n - 1, phi);

    // 根据欧拉降幂公式，指数需要加上 phi（因为递归返回的 exponent 已经考虑了是否加 phi）
    return qpow(n, exponent + phi, m);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n, m;
    cin >> n >> m;
    cout << solve(n, m) << '\n';

    return 0;
}
