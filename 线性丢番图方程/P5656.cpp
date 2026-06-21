/**
 * https://www.luogu.com.cn/problem/P5656
 *
 * @File:   P5656.cpp
 * @Author: Lao Zhang samuelzhang77@outlook.com
 * @Date:   2026-01-24
 *
 */
#include <iostream>
#include <cmath>
using namespace std;
typedef long long ll; // 使用 long long 防止溢出

// 扩展欧几里得算法
ll exgcd(ll a, ll b, ll &x, ll &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    ll d = exgcd(b, a % b, y, x); // 递归，并交换x, y
    y -= (a / b) * x; // 更新y
    return d;
}

// 安全的向上取整函数 (计算 ceil(n/m) ，用于整数)
ll ceil_div(ll n, ll m) {
    // 处理n和m可能异号的情况，确保向上取整逻辑正确
    if (n % m == 0) {
        return n / m;
    }
    // 判断结果的正负以决定取整方式
    ll q = n / m;
    if ((n > 0 && m > 0) || (n < 0 && m < 0)) {
        return q + 1; // 同号时，余数同号，需要加1
    } else {
        return q; // 异号时，商为负或0，余数符号与被除数相同，直接取商
    }
}

int main() {
    // 关闭同步流，提高输入输出效率
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        ll a, b, c;
        cin >> a >> b >> c;

        ll x0, y0;
        ll g = exgcd(a, b, x0, y0); // 求出 g = gcd(a, b) 和一组特解 (x0, y0)

        // 情况1：根据裴蜀定理，无整数解
        if (c % g != 0) {
            cout << "-1\n";
            continue;
        }

        // 情况2：有整数解
        // 将特解缩放，得到原方程 ax + by = c 的一组特解 (x1, y1)
        x0 *= (c / g);
        y0 *= (c / g);

        // 通解公式中的步长
        ll dx = b / g; // x 每次变化的值
        ll dy = a / g; // y 每次变化的值 (注意是减，所以这里取正值)

        // 计算使 X > 0 和 Y > 0 的 k 的边界 L 和 R
        // L 是满足 x1 + k*dx > 0 的最小整数 k，即 k > (1 - x1) / dx
        ll L = ceil_div(1 - x0, dx); // 注意这里使用安全的向上取整
        // R 是满足 y1 - k*dy > 0 的最大整数 k，即 k < (y1 - 1) / dy
        ll R = floor((y0 - 1.0) / dy); // floor向下取整，这里用浮点避免复杂情况

        // 情况2.1：有正整数解 (存在整数k满足 L <= k <= R)
        if (L <= R) {
            // 正整数解的数量
            ll num = R - L + 1;
            // x的最小值 (k = L 时取得)
            ll x_min = x0 + L * dx;
            // y的最大值 (k = L 时，y = y0 - L*dy 最大)
            ll y_max = y0 - L * dy;
            // x的最大值 (k = R 时取得)
            ll x_max = x0 + R * dx;
            // y的最小值 (k = R 时取得)
            ll y_min = y0 - R * dy;

            cout << num << " " << x_min << " " << y_min << " " << x_max << " " << y_max << "\n";
        }
        // 情况2.2：无正整数解，但有无整数解
        else {
            // 需要分别找 x 的最小正整数值和 y 的最小正整数值
            // x 的最小正整数值：满足 x ≥ 1 的最小 k 就是 L
            ll x_min_pos = x0 + L * dx;

            // 计算 y 的最小正整数值, 满足 y ≥ 1 的最大 k 就是 R
            ll y_min_pos = y0 - R * dy;

            cout << x_min_pos << " " << y_min_pos << "\n";
        }
    }
    return 0;
}
