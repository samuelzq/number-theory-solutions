/**
 * https://www.luogu.com.cn/problem/B4025
 * https://csacademy.com/contest/archive/task/gcd<D-a><D-c>/
 *
 * @File:   csacademy_gcd.cpp
 * @Author: Lao Zhang samuelzhang77@outlook.com
 * @Date:   2026-01-11
 *
 */
#include <iostream>
#include <algorithm> // 用于 std::swap

/**
 * 使用 Binary GCD 算法计算最大公约数
 * 时间复杂度: O(log(max(A, B)))，但在位运算层面进行了优化
 */
int get_gcd(int a, int b) {
    // 处理基准情况
    if (a == 0) return b;
    if (b == 0) return a;

    // 1. 提取 a 和 b 共同拥有的因子 2
    // __builtin_ctz 返回末尾 0 的个数，即该数能被 2 整除的次数
    int shift = __builtin_ctz(a | b);

    // 2. 将 a 剥离掉所有因子 2，使其变为奇数
    a >>= __builtin_ctz(a);

    // 3. 循环处理
    do {
        // 剥离 b 中所有的因子 2
        // 如果 a 是奇数，b 是偶数，这一步直接应用了 gcd(a, b) = gcd(a, b/2^k)
        b >>= __builtin_ctz(b);

        // 此时 a 和 b 均为奇数
        if (a > b) {
            std::swap(a, b);
        }

        // 利用 gcd(a, b) = gcd(a, b - a)
        // 两个奇数相减必然得到偶数，b 会在下一轮循环开始时被剥离因子 2
        b = b - a;

    } while (b != 0);

    // 4. 将最初提取的共同因子 2 乘回去
    return a << shift;
}

int main() {
    // 禁用同步提高输入输出效率
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int a, b;
    if (std::cin >> a >> b) {
        std::cout << get_gcd(a, b) << std::endl;
    }

    return 0;
}
