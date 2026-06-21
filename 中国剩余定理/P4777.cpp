/**
 * https://www.luogu.com.cn/problem/P4777
 *
 * @File:   P4777.cpp
 * @Author: Lao Zhang samuelzhang77@outlook.com
 * @Date:   2026-05-01
 *
 */
#include <iostream>
#include <vector>
using namespace std;

typedef long long ll;

ll exgcd(ll a, ll b, ll& x, ll& y) {
    if (b == 0) {
        x = 1, y = 0;
        return a;
    }
    ll d = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
}

ll excrt(const vector<pair<ll, ll>>& equations) {
    ll mod = 1;      // 当前合并后的模数
    ll ans = 0;      // 当前合并后的解

    for (auto& [m, r] : equations) {  // 当前方程: x ≡ r (mod m)
        // 合并两个方程: x ≡ ans (mod mod) 和 x ≡ r (mod m)

        ll p, q;  // 临时变量
        ll g = exgcd(mod, m, p, q);  // p * mod + q * m = g

        // 检查是否有解
        ll diff = r - ans;
        if (diff % g != 0) return -1;  // 题目保证有解，这行不会执行

        // 计算新的解
        ll lcm = mod / g * m;  // 注意：这里可能需要 __int128，但 mod/g*m ≤ 1e18
        __int128 k = (__int128)p * (diff / g) % (m / g);

        // 更新答案
        ans = (__int128)ans + (__int128)mod * k % lcm;
        ans %= lcm;
        if (ans < 0) ans += lcm;

        mod = lcm;  // 更新模数
    }

    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<pair<ll, ll>> equations(n);
    for (int i = 0; i < n; ++i) {
        cin >> equations[i].first >> equations[i].second;
    }

    cout << excrt(equations) << "\n";
    return 0;
}
