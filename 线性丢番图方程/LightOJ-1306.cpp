/**
 * https://lightoj.com/problem/solutions-to-an-equation
 *
 * @File:   LightOJ-1306.cpp
 * @Author: Lao Zhang samuelzhang77@outlook.com
 * @Date:   2026-01-31
 *
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

LL exgcd(LL a, LL b, LL &x, LL &y) {
    if (!b) { x = 1; y = 0; return a; }
    LL d = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
}

LL ceilDiv(LL a, LL b) {
    if (b < 0) { a = -a; b = -b; }
    if (a % b == 0) return a / b;
    return a / b + (a > 0);
}

LL floorDiv(LL a, LL b) {
    if (b < 0) { a = -a; b = -b; }
    if (a % b == 0) return a / b;
    return a / b - (a < 0);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int T;
    cin >> T;

    for (int caseNum = 1; caseNum <= T; caseNum++) {
        LL A, B, C, x1, x2, y1, y2;
        cin >> A >> B >> C;
        cin >> x1 >> x2 >> y1 >> y2;

        // 转换方程为 Ax + By = D
        LL D = -C;

        // 处理特殊情况
        if (A == 0 && B == 0) {
            cout << "Case " << caseNum << ": " << (D == 0 ? (x2-x1+1)*(y2-y1+1) : 0) << "\n";
            continue;
        }

        if (A == 0) {
            if (D % B != 0) {
                cout << "Case " << caseNum << ": 0\n";
            } else {
                LL y = D / B;
                if (y >= y1 && y <= y2) {
                    cout << "Case " << caseNum << ": " << max(0LL, x2 - x1 + 1) << "\n";
                } else {
                    cout << "Case " << caseNum << ": 0\n";
                }
            }
            continue;
        }

        if (B == 0) {
            if (D % A != 0) {
                cout << "Case " << caseNum << ": 0\n";
            } else {
                LL x = D / A;
                if (x >= x1 && x <= x2) {
                    cout << "Case " << caseNum << ": " << max(0LL, y2 - y1 + 1) << "\n";
                } else {
                    cout << "Case " << caseNum << ": 0\n";
                }
            }
            continue;
        }

        // 一般情况
        LL x0, y0;
        LL g = exgcd(A, B, x0, y0);

        if (D % g != 0) {
            cout << "Case " << caseNum << ": 0\n";
            continue;
        }

        // 缩放特解
        x0 *= D / g;
        y0 *= D / g;

        LL dx = B / g;
        LL dy = A / g;  // 注意：通解中 y = y0 - dy*k

        // 计算 k 的范围
        LL kx_low, kx_high, ky_low, ky_high;

        // x 的范围：x1 ≤ x0 + dx*k ≤ x2
        if (dx > 0) {
            kx_low = ceilDiv(x1 - x0, dx);
            kx_high = floorDiv(x2 - x0, dx);
        } else {
            kx_low = ceilDiv(x2 - x0, dx);
            kx_high = floorDiv(x1 - x0, dx);
        }

        // y 的范围：y1 ≤ y0 - dy*k ≤ y2
        if (dy > 0) {
            ky_low = ceilDiv(y0 - y2, dy);
            ky_high = floorDiv(y0 - y1, dy);
        } else {
            ky_low = ceilDiv(y0 - y1, dy);
            ky_high = floorDiv(y0 - y2, dy);
        }

        // 取交集
        LL low = max(kx_low, ky_low);
        LL high = min(kx_high, ky_high);
        LL ans = max(0LL, high - low + 1);

        cout << "Case " << caseNum << ": " << ans << "\n";
    }

    return 0;
}
