/**
 * https://vjudge.net/problem/UVA-756
 * https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=697
 *
 * @File:   UVA756.cpp
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

// 中国剩余定理：求解 x ≡ r_i (mod m_i) 的最小非负解
ll crt(const vector<ll>& mods, const vector<ll>& remainders) {
    ll M = 1;
    for (ll m : mods) M *= m;          // 模数乘积

    ll ans = 0;
    for (int i = 0; i < mods.size(); ++i) {
        ll Mi = M / mods[i];            // 除当前模数外的乘积
        ll inv = mod_inv(Mi % mods[i], mods[i]);  // Mi 在模 mods[i] 下的逆元
        ans = (ans + remainders[i] * Mi % M * inv) % M;
    }
    return ans;
}

int main() {
    ll p, e, i, d;
    int caseNo = 1;
    const vector<ll> mods = {23, 28, 33};
    const ll cycle = 21252;  // 23*28*33

    while (cin >> p >> e >> i >> d) {
        if (p == -1 && e == -1 && i == -1 && d == -1) break;

        // 将输入视为余数（注意 p、e、i 本身就是余数）
        vector<ll> rems = {p, e, i};
        ll x = crt(mods, rems);

        // 必须满足 x > d，且结果在周期内
        if (x <= d) {
            x += ((d - x) / cycle + 1) * cycle;
        }

        // 输出格式，注意即使相差 1 也要用 days
        cout << "Case " << caseNo++ << ": the next triple peak occurs in "
             << x - d << " days." << endl;
    }
    return 0;
}
