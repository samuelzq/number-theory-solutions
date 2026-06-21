/**
 * https://codeforces.com/problemsets/acmsguru/problem/99999/106
 *
 * @File:   SGU106.cpp
 * @Author: Lao Zhang samuelzhang77@outlook.com
 * @Date:   2026-01-31
 *
 */
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

typedef long long LL;

// 扩展欧几里得算法
LL exgcd(LL a, LL b, LL &x, LL &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    LL d = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
}

// 纯整数向上取整
LL ceilDiv(LL a, LL b) {
    if (b == 0) return 0; // 避免除零错误

    // 处理负数：我们希望分母为正
    bool neg = false;
    if (b < 0) {
        b = -b;
        a = -a;
    }

    if (a >= 0) {
        // (a + b - 1) / b 是常见的向上取整技巧
        return (a + b - 1) / b;
    } else {
        // a 为负数时直接除法就是向上取整
        return a / b;
    }
}

// 纯整数向下取整
LL floorDiv(LL a, LL b) {
    if (b == 0) return 0;

    bool neg = false;
    if (b < 0) {
        b = -b;
        a = -a;
    }

    if (a >= 0) {
        return a / b;
    } else {
        // a 为负数时，(a - b + 1) / b 是向下取整
        return (a - b + 1) / b;
    }
}

// 安全的区间整数个数计算
LL countInRange(LL L, LL R) {
    if (L > R) return 0;
    return R - L + 1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    LL a, b, c, x1, x2, y1, y2;
    cin >> a >> b >> c >> x1 >> x2 >> y1 >> y2;

    c = -c; // 转换为 ax + by = c

    // 特殊情况 1: a = 0 且 b = 0
    if (a == 0 && b == 0) {
        if (c == 0) {
            LL x_cnt = max(0LL, x2 - x1 + 1);
            LL y_cnt = max(0LL, y2 - y1 + 1);
            cout << x_cnt * y_cnt << endl;
        } else {
            cout << 0 << endl;
        }
        return 0;
    }

    // 特殊情况 2: a = 0, b ≠ 0
    if (a == 0) {
        if (c % b != 0) {
            cout << 0 << endl;
            return 0;
        }
        LL y = c / b;
        if (y >= y1 && y <= y2) {
            LL cnt = max(0LL, x2 - x1 + 1);
            cout << cnt << endl;
        } else {
            cout << 0 << endl;
        }
        return 0;
    }

    // 特殊情况 3: b = 0, a ≠ 0
    if (b == 0) {
        if (c % a != 0) {
            cout << 0 << endl;
            return 0;
        }
        LL x = c / a;
        if (x >= x1 && x <= x2) {
            LL cnt = max(0LL, y2 - y1 + 1);
            cout << cnt << endl;
        } else {
            cout << 0 << endl;
        }
        return 0;
    }

    // 一般情况：a ≠ 0 且 b ≠ 0
    LL x0, y0;
    LL g = exgcd(a, b, x0, y0);

    // 检查是否有解
    if (c % g != 0) {
        cout << 0 << endl;
        return 0;
    }

    // 缩放得到原方程的特解
    LL mult = c / g;
    x0 *= mult;
    y0 *= mult;

    // 通解参数
    LL dx = b / g;
    LL dy = a / g;

    // 计算 k 的取值范围
    LL kx_min, kx_max, ky_min, ky_max;

    // 处理 x 的不等式：x1 ≤ x0 + dx*k ≤ x2
    if (dx > 0) {
        // x0 + dx*k ≥ x1 => k ≥ (x1 - x0)/dx
        kx_min = ceilDiv(x1 - x0, dx);
        // x0 + dx*k ≤ x2 => k ≤ (x2 - x0)/dx
        kx_max = floorDiv(x2 - x0, dx);
    } else if (dx < 0) {
        // 注意：dx < 0 时，不等式方向会反转
        // x0 + dx*k ≥ x1 => dx*k ≥ x1 - x0 => k ≤ (x1 - x0)/dx (因为除以负数要反转不等号)
        kx_min = ceilDiv(x2 - x0, dx); // 注意这里交换了
        kx_max = floorDiv(x1 - x0, dx);
    }

    // 处理 y 的不等式：y1 ≤ y0 - dy*k ≤ y2
    // 即：y0 - dy*k ≥ y1 => -dy*k ≥ y1 - y0 => dy*k ≤ y0 - y1
    //     y0 - dy*k ≤ y2 => -dy*k ≤ y2 - y0 => dy*k ≥ y0 - y2

    if (dy > 0) {
        // dy*k ≥ y0 - y2 => k ≥ (y0 - y2)/dy
        ky_min = ceilDiv(y0 - y2, dy);
        // dy*k ≤ y0 - y1 => k ≤ (y0 - y1)/dy
        ky_max = floorDiv(y0 - y1, dy);
    } else if (dy < 0) {
        // dy < 0 时，不等式方向会反转
        // dy*k ≥ y0 - y2 => k ≤ (y0 - y2)/dy
        // dy*k ≤ y0 - y1 => k ≥ (y0 - y1)/dy
        ky_min = ceilDiv(y0 - y1, dy);
        ky_max = floorDiv(y0 - y2, dy);
    }

    // 取两个范围的交集
    LL k_low = max(kx_min, ky_min);
    LL k_high = min(kx_max, ky_max);

    // 计算满足条件的整数 k 的数量
    LL result = countInRange(k_low, k_high);
    cout << max(0LL, result) << endl;

    return 0;
}
