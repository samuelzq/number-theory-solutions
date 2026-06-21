/**
 * https://lightoj.com/problem/number-sequence
 * https://vjudge.net/problem/LightOJ-1065
 *
 * @File:   Lightoj_1065.cpp
 * @Author: Lao Zhang samuelzhang77@outlook.com
 * @Date:   2026-02-07
 *
 * f(0) = a
 * f(1) = b
 * f(2) = a + b
 * f(3) = (a + b) + b = a + 2b
 * f(4) = (a + 2b) + (a + b) = 2a + 3b
 * f(5) = (2a + 3b) + (a + 2b) = 3a + 5b
 *
 * n=0: F(-1)未定义 → 但题目直接给出 f(0)=a
 * n=1: F(0)*a + F(1)*b = 0*a + 1*b = b
 * n=2: F(1)*a + F(2)*b = 1*a + 1*b = a+b ✓
 * n=3: F(2)*a + F(3)*b = 1*a + 2*b = a+2b ✓
 * n=4: F(3)*a + F(4)*b = 2*a + 3*b = 2a+3b
 */
#include <iostream>
using namespace std;

typedef long long ll;

ll MOD;  // 模数作为全局变量

// 快速倍增法计算 (F(n), F(n+1)) 对
pair<ll, ll> fib(ll n) {
    if (n == 0) return {0, 1};

    auto p = fib(n >> 1);
    ll a = p.first;
    ll b = p.second;

    // 计算 2b - a，确保非负
    ll two_b_minus_a = (2 * b % MOD - a % MOD + MOD) % MOD;
    ll c = (a * two_b_minus_a) % MOD;          // F(2k)
    ll d = (a * a % MOD + b * b % MOD) % MOD;  // F(2k+1)

    if (n & 1) {
        return {d, (c + d) % MOD};  // (F(2k+1), F(2k+2))
    }
    return {c, d};                  // (F(2k), F(2k+1))
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int T;
    cin >> T;

    for (int t = 1; t <= T; t++) {
        ll a, b, n, m;
        cin >> a >> b >> n >> m;

        // 计算模数 10^m
        MOD = 1;
        for (int i = 0; i < m; i++) MOD *= 10;

        // 计算答案
        ll ans;

        if (n == 0) {
            ans = a % MOD;
        } else {
            // 我们需要计算 F(n-1) 和 F(n)
            ll F_n_minus_1, F_n;

            if (n == 1) {
                // F(0) 和 F(1)
                F_n_minus_1 = 0 % MOD;
                F_n = 1 % MOD;
            } else {
                // 计算 (F(n-1), F(n))
                auto p = fib(n - 1);
                F_n_minus_1 = p.first;
                F_n = p.second;
            }

            // 公式：f(n) = F(n-1) * a + F(n) * b
            a %= MOD;
            b %= MOD;
            ans = (F_n_minus_1 * a % MOD + F_n * b % MOD) % MOD;
        }

        cout << "Case " << t << ": " << ans << "\n";
    }

    return 0;
}
