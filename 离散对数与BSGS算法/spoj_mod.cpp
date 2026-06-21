/**
 * https://www.spoj.com/problems/MOD/
 *
 * @File:   spoj_mod.cpp
 * @Author: Lao Zhang samuelzhang77@outlook.com
 * @Date:   2026-05-09
 *
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// ================= 手写哈希表 (开放寻址法) =================
const int HASH_CAP = 1 << 18;
struct HashMap {
    ll keys[HASH_CAP], vals[HASH_CAP];
    bool used[HASH_CAP];

    void init() { memset(used, 0, sizeof(used)); }

    inline int hash_func(ll k) {
        return (k * 131 + 131) & (HASH_CAP - 1);
    }

    void insert(ll k, ll v) {
        int idx = hash_func(k);
        while (used[idx] && keys[idx] != k)
            idx = (idx + 1) & (HASH_CAP - 1);
        if (!used[idx]) {
            used[idx] = true;
            keys[idx] = k;
            vals[idx] = v;  // 保留最小指数
        }
    }

    ll find(ll k) {
        int idx = hash_func(k);
        while (used[idx]) {
            if (keys[idx] == k) return vals[idx];
            idx = (idx + 1) & (HASH_CAP - 1);
        }
        return -1;
    }
} table;
// ==========================================================

ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }

ll exgcd(ll a, ll b, ll &x, ll &y) {
    if (!b) { x = 1; y = 0; return a; }
    ll d = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
}

ll get_inv(ll a, ll m) {
    ll x, y; exgcd(a, m, x, y);
    return (x % m + m) % m;
}

ll qpow(ll a, ll b, ll m) {
    ll res = 1 % m; a %= m;
    for (; b; b >>= 1, a = a * a % m)
        if (b & 1) res = res * a % m;
    return res;
}

// 基础 BSGS (加法版，与参考代码逻辑一致)
ll bsgs(ll a, ll b, ll m) {
    ll n = (ll)sqrt(m) + 1;  // 确保 n^2 >= m
    table.init();

    // Baby-step: 存 a^j
    ll cur = 1;
    for (ll j = 0; j < n; ++j) {
        table.insert(cur, j);
        cur = cur * a % m;
    }

    // Giant-step: 查 b * (a^n)^{-i}
    ll a_n = qpow(a, n, m);
    ll inv_a_n = get_inv(a_n, m);  // exgcd 求逆，兼容合数
    cur = b % m;
    for (ll i = 0; i < n; ++i) {
        ll j = table.find(cur);
        if (j != -1) return i * n + j;  // 首次命中即最小解
        cur = cur * inv_a_n % m;
    }
    return -1;
}

ll exbsgs(ll a, ll b, ll m) {
    a %= m; b %= m;
    if (m == 1) return 0;
    if (b == 1) return 0;

    // 完备的 a=0 特判
    if (a == 0) {
        if (b == 0) return 1;
        if (b == 1) return 0;
        return -1;
    }

    ll cnt = 0, D = 1;
    while (true) {
        ll g = gcd(a, m);
        if (g == 1) break;
        if (b % g != 0) return -1;

        m /= g; b /= g;
        D = D * (a / g) % m;
        cnt++;
        if (D == b) return cnt;  // 拦截 x = cnt
    }

    if (m == 1) return cnt;
    ll target = b * get_inv(D, m) % m;
    ll res = bsgs(a, target, m);
    return res == -1 ? -1 : res + cnt;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll x, z, k;
    while (cin >> x >> z >> k && (x || z || k)) {
        ll ans = exbsgs(x, k, z);
        if (ans == -1) cout << "No Solution\n";
        else cout << ans << '\n';
    }
    return 0;
}
