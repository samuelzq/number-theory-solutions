/**
 * https://www.luogu.com.cn/problem/P1495
 *
 * @File:   P1495.cpp
 * @Author: Lao Zhang samuelzhang77@outlook.com
 * @Date:   2026-05-01
 *
 */
#include <iostream>
#include <vector>
using namespace std;

typedef long long ll;

ll exgcd(ll a, ll b, ll &x, ll &y) {
    if (b == 0) {
        x = 1; y = 0;
        return a;
    }
    ll d = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
}

ll mod_inv(ll a, ll m) {
    ll x, y;
    exgcd(a, m, x, y);
    // 确保逆元为正
    x %= m;
    if (x < 0) x += m;
    return x;
}

ll crt(const vector<pair<ll, ll>>& congruences) {
    __int128 M = 1;           // 使用 __int128 防止溢出
    for (auto &p : congruences) {
        M *= p.first;
    }

    __int128 ans = 0;
    for (auto &p : congruences) {
        ll ai = p.first;
        ll bi = p.second;

        __int128 Mi = M / ai;
        // 关键：先取模再求逆
        ll Mi_mod = (ll)(Mi % ai);
        ll inv = mod_inv(Mi_mod, ai);
        ans = (ans + (__int128)bi * Mi % M * inv) % M;
    }
    return (ll)ans;
}

int main() {
    int n;
    cin >> n;
    vector<pair<ll, ll>> cong(n);
    for (int i = 0; i < n; i++) {
        cin >> cong[i].first >> cong[i].second;
    }

    ll result = crt(cong);
    cout << result << endl;
    return 0;
}
