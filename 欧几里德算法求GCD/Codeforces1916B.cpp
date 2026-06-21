/**
 * https://codeforces.com/contest/1916/problem/B
 *
 * @File:   Codeforces1916B.cpp
 * @Author: Lao Zhang samuelzhang77@outlook.com
 * @Date:   2026-01-11
 *
 */
#include <iostream>
#include <numeric> // C++17 及以后版本包含 std::gcd 和 std::lcm

typedef long long ll;

// 手写二进制 GCD 优化版本 (Stein 算法)
ll get_gcd(ll a, ll b) {
    if (a == 0) return b;
    if (b == 0) return a;
    int shift = __builtin_ctzll(a | b);
    a >>= __builtin_ctzll(a);
    do {
        b >>= __builtin_ctzll(b);
        if (a > b) std::swap(a, b);
        b -= a;
    } while (b != 0);
    return a << shift;
}

// 求最小公倍数
ll get_lcm(ll a, ll b) {
    if (a == 0 || b == 0) return 0;
    // 先除后乘防止中间过程溢出
    return (a / get_gcd(a, b)) * b;
}

void solve() {
    ll a, b;
    std::cin >> a >> b;

    if (b % a == 0) {
        // 情况 1: b 是 a 的倍数
        std::cout << b * (b / a) << "\n";
    } else {
        // 情况 2: b 不是 a 的倍数
        std::cout << get_lcm(a, b) << "\n";
    }
}

int main() {
    // 优化 IO 性能
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int t;
    std::cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
