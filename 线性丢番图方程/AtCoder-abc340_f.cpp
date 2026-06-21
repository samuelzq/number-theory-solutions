/**
 * https://atcoder.jp/contests/abc340/tasks/abc340_f
 *
 * @File:   AtCoder-abc340_f.cpp
 * @Author: Lao Zhang samuelzhang77@outlook.com
 * @Date:   2026-01-31
 *
 */
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll gcd (ll a, ll b) {
    while (b) {
        a %= b;
        swap(a, b);
    }
    return a;
}

// 非负输入的扩展欧几里得
ll extgcd(ll a, ll b, ll &x, ll &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    ll d = extgcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
}

bool find_any_solution(ll a, ll b, ll c, ll &x0, ll &y0, ll &g) {
    g = extgcd(abs(a), abs(b), x0, y0);
    if (c % g) {
        return false;
    }

    x0 *= c / g;
    y0 *= c / g;
    if (a < 0) x0 = -x0;
    if (b < 0) y0 = -y0;
    return true;
}

int main() {
    ll X, Y;
    cin >> X >> Y;

    // 计算gcd
    ll g = gcd(llabs(X), llabs(Y));

    if (g > 2) {
        cout << -1 << endl;
        return 0;
    }

    // 尝试两种可能的目标值：2 和 -2
    // 因为方程 |X*B - Y*A| = 2 等价于 X*B - Y*A = 2 或 -2

    const ll targets[2] = {2, -2};
    const ll LIMIT = 1'000'000'000'000'000'000LL;

    for (ll target : targets) {
        // 方程：X*B - Y*A = target
        // 即：(-Y)*A + X*B = target

        // 使用扩展欧几里得解：a*A + b*B = gcd(a,b)
        // 其中 a = -Y, b = X

        ll a = -Y;
        ll b = X;

        ll A, B, d;

        if (find_any_solution(a, b, target, A, B, d) == false)
            continue;

        // 验证解
        ll check = X * B - Y * A;

        if (check == target) {
            // 检查是否在范围内
            if (abs(A) <= LIMIT && abs(B) <= LIMIT) {
                cout << A << " " << B << endl;
                return 0;
            }

            // 如果不在范围内，尝试调整通解
            // 通解：A = A + (b/d)*k, B = B - (a/d)*k
            // 对于大多数测试用例，特解 (A, B) 通常已经接近原点，调整几个单位就能进入范围 

            ll dx = b / d;
            ll dy = a / d;

            // 尝试几个k值
            for (ll k = -10; k <= 10; k++) {
                ll A_new = A + dx * k;
                ll B_new = B - dy * k;

                if (abs(A_new) <= LIMIT && abs(B_new) <= LIMIT) {
                    ll check_new = X * B_new - Y * A_new;
                    if (check_new == target) {
                        cout << A_new << " " << B_new << endl;
                        return 0;
                    }
                }
            }
        }
    }

    cout << -1 << endl;
    return 0;
}
