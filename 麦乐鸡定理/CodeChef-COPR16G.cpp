/**
 * https://www.codechef.com/problems/COPR16G
 *
 * @File:   CodeChef-COPR16G.cpp
 * @Author: Lao Zhang samuelzhang77@outlook.com
 * @Date:   2026-01-31
 *
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;

    while (t--) {
        LL a, b;
        cin >> a >> b;

        // 确保 a ≤ b
        if (a > b) swap(a, b);

        // 特殊情况
        if (a == 1) {
            cout << "0\n";
            continue;
        }

        // 检查是否互质
        if (__gcd(a, b) > 1) {
            cout << "-1\n";
            continue;
        }

        // 弗罗贝尼乌斯公式
        LL result = a * b - a - b + 1;
        cout << result << "\n";
    }

    return 0;
}
