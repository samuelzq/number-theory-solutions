/**
 * https://vjudge.net/problem/UVA-374 Big Mod
 * https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=310
 *
 * @File:   uva374.cpp
 * @Author: Lao Zhang samuelzhang77@outlook.com
 * @Date:   2026-01-04
 *
 */
#include <iostream>

using namespace std;

/**
 * 快速幂算法 (Binary Exponentiation)
 * 计算 (B^P) % M
 */
long long powerMod(long long B, long long P, long long M) {
    if (M == 1) return 0; // 任何数对 1 取模结果都是 0

    long long res = 1;
    B %= M; // 预先取模，确保底数在 M 范围内

    while (P > 0) {
        // 如果当前指数 P 的二进制位为 1 (即 P 是奇数)
        if (P % 2 == 1) {
            res = (res * B) % M;
        }

        // 底数翻倍（平方）
        B = (B * B) % M;

        // 指数减半
        P /= 2;
    }
    return res;
}

int main() {
    long long B, P, M;
    // 循环读取 B, P, M 直至输入结束
    // 题目描述中 B, P, M 是每行一个数字
    while (cin >> B >> P >> M) {
        cout << powerMod(B, P, M) << endl;
    }
    return 0;
}
