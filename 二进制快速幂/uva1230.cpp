/**
 * https://vjudge.net/problem/UVA-1230
 * https://vjudge.net/problem/UVA-1230/origin
 *
 * @File:   uva1239.cpp
 * @Author: Lao Zhang samuelzhang77@outlook.com
 * @Date:   2026-01-04
 *
 */
#include <iostream>

using namespace std;

/**
 * 快速幂函数 (Binary Exponentiation)
 * 计算 (base^exp) % mod
 */
long long powerMod(long long base, long long exp, long long mod) {
    long long res = 1;
    base %= mod; // 先对底数取模，防止 base 过大

    while (exp > 0) {
        // 如果指数当前二进制位是 1
        if (exp & 1) {
            res = (res * base) % mod;
        }

        // 底数自乘（平方）
        base = (base * base) % mod;

        // 指数右移一位，相当于 exp / 2
        exp >>= 1;
    }
    return res;
}

int main() {
    int c;
    // 读取数据集的数量
    if (!(cin >> c) || c == 0) return 0;

    while (c--) {
        long long x, y, n;
        cin >> x >> y >> n;
        // 输出计算结果
        cout << powerMod(x, y, n) << endl;
    }

    // 处理最后的结束标志 '0'
    int endSignal;
    cin >> endSignal;

    return 0;
}
