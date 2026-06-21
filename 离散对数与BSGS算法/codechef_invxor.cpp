/**
 * https://www.codechef.com/problems/INVXOR/
 *
 * @File:   codechef_invxor.cpp
 * @Author: Lao Zhang samuelzhang77@outlook.com
 * @Date:   2026-05-09
 *
 */
#include <bits/stdc++.h>
using namespace std;

using int64 = long long;

const int MOD = 998244353;
const int INV2 = 499122177;

int64 modpow(int64 a, int64 b, int64 mod) {
    int64 r = 1 % mod;

    while (b) {
        if (b & 1)
            r = (__int128)r * a % mod;

        a = (__int128)a * a % mod;
        b >>= 1;
    }

    return r;
}

// 2^N mod mod
// N extremely huge decimal string
int64 pow2_big(const string& N, int64 mod) {

    int64 r = 1 % mod;

    for (char c : N) {

        r = modpow(r, 10, mod);
        r = (__int128)r * modpow(2, c - '0', mod) % mod;
    }

    return r;
}

int64 discrete_log(int64 a, int64 b, int64 mod) {

    a %= mod;
    b %= mod;

    if (b == 1)
        return 0;

    // 小指数先暴力（官方做法）
    int64 cur = 1 % mod;

    for (int64 k = 0; k <= 10000; k++) {

        if (cur == b)
            return k;

        cur = (__int128)cur * a % mod;
    }

    int64 t = 1;
    int64 add = 0;

    while (true) {

        int64 g = gcd(a, mod);

        if (g == 1)
            break;

        if (b % g)
            return -1;

        mod /= g;
        b /= g;

        t = (__int128)t * (a / g) % mod;

        add++;

        if (t == b)
            return add;
    }

    int64 m = sqrt((long double)mod) + 1;

    unordered_map<int64, int64> mp;

    // baby steps
    int64 e = 1;

    for (int64 i = 0; i < m; i++) {

        int64 v = (__int128)e * b % mod;

        if (!mp.count(v))
            mp[v] = i;

        e = (__int128)e * a % mod;
    }

    int64 giant = e;
    int64 cur2 = t;

    int64 ans = -1;

    for (int64 i = 1; i <= m + 1; i++) {

        cur2 = (__int128)cur2 * giant % mod;

        if (mp.count(cur2)) {

            int64 cand = i * m - mp[cur2] + add;

            if (ans == -1 || cand < ans)
                ans = cand;
        }
    }

    return ans;
}

int main() {

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {

        string N;
        int64 X, M;

        cin >> N >> X >> M;

        // hidden trap
        if (M == 1) {
            cout << 0 << '\n';
            continue;
        }

        // hidden trap
        if (X == 0) {

            if (N == "1")
                cout << -1 << '\n';
            else
                cout << 1 << '\n';

            continue;
        }

        int64 base = (pow2_big(N, M) - 1 + M) % M;

        int64 p = discrete_log(base, X, M);

        if (p == -1) {

            cout << -1 << '\n';
            continue;
        }

        int64 pow2N = pow2_big(N, MOD);

        int64 ans =
            pow2N * INV2 % MOD *
            ((modpow(2, p, MOD) - 1 + MOD) % MOD)
            % MOD;

        cout << ans << '\n';
    }
}
