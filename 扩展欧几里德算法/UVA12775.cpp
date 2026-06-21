/**
 * https://vjudge.net/problem/UVA-12775
 *
 * @File:   UVA12775.cpp
 * @Author: Lao Zhang samuelzhang77@outlook.com
 * @Date:   2026-01-18
 *
 */
#include <iostream>
#include <algorithm>
#include <cmath>
#include <tuple>

using namespace std;

typedef long long ll;

// 扩展欧几里得算法迭代版
ll exgcd(ll a, ll b, ll &x, ll &y) {
    x = 1, y = 0;
    ll x1 = 0, y1 = 1, a1 = a, b1 = b;
    while (b1) {
        ll q = a1 / b1;
        tie(x, x1) = make_tuple(x1, x - q * x1);
        tie(y, y1) = make_tuple(y1, y - q * y1);
        tie(a1, b1) = make_tuple(b1, a1 - q * b1);
    }
    return a1;
}

ll gcd(ll a, ll b) {
    while (b) {
        a %= b;
        swap(a, b);
    }
    return a;
}

void solve(int caseNum) {
    ll A, B, C, P;
    if (!(cin >> A >> B >> C >> P)) return;

    ll g = gcd(A, gcd(B, C));
    if (P % g != 0) {
        cout << "Case " << caseNum << ": 0" << endl;
        return;
    }

    // 约分
    A /= g; B /= g; C /= g; P /= g;

    ll totalWays = 0;
    ll x0, y0;
    ll d = exgcd(A, B, x0, y0);
    ll stepX = B / d;
    ll stepY = A / d;

    // 枚举 z
    for (ll z = 0; z * C <= P; ++z) {
        ll M = P - z * C;
        if (M % d == 0) {
            // 当前 z 下，Ax + By = M 的特解
            ll curX = x0 * (M / d);
            ll curY = y0 * (M / d);

            // 将 curX 调整到最小非负整数解，找到 k 的下界
            // x = curX + k * stepX >= 0 -> k >= -curX / stepX
            ll kMin = ceil(-(double)curX / stepX);
            if (curX < 0) {
                ll k = (-curX + stepX - 1) / stepX;
                curX += k * stepX;
                curY -= k * stepY;
            } else {
                ll k = curX / stepX;
                curX -= k * stepX;
                curY += k * stepY;
            }

            // 此时 curX 是最小非负解，如果对应的 curY 仍 >= 0，则有解
            if (curY >= 0) {
                totalWays += (curY / stepY + 1);
            }
        }
    }

    cout << "Case " << caseNum << ": " << totalWays << endl;
}

int main() {
    int T;
    cin >> T;
    for (int i = 1; i <= T; ++i) {
        solve(i);
    }
    return 0;
}
