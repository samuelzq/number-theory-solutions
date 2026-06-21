/**
 * https://codeforces.com/problemset/problem/630/<D-s>I
 *
 * @File:   CodeForces_630I.cpp
 * @Author: Lao Zhang samuelzhang77@outlook.com
 * @Date:   2026-03-22
 *
 */
#include <bits/stdc++.h>  // 万能头文件

using namespace std;

// 快速幂函数：计算 s^n
// 注意：这里没有取模，因为答案可能很大，但题目保证在 long long 范围内
long long pp(long long s, long long n)
{
    long long a, ret;

    ret = 1;      // 结果初始化为 1
    a = s;        // 底数

    while (n) {   // 当指数 n 不为 0 时循环
        if (n & 1)        // 如果当前二进制位是 1
            ret *= a;     // 将当前底数乘入结果

        a *= a;           // 底数平方，准备下一位
        n >>= 1;          // 指数右移一位
    }

    return ret;   // 返回 s^n
}

int main(void)
{
    int n;              // n 是题目给出的参数，m 是停车场长度
    long long s1, s2;   // s1: 两端的情况，s2: 中间的情况

    cin >> n;           // 读入 n

    // 计算公共部分：4^(n-3)
    // 这个值在两端和中间的情况中都会用到
    s1 = pp(4, n - 3);      // 4 的 (n-3) 次方

    // 计算中间情况的数量
    // 公式：(n-3) × 3 × 3 × 4^(n-3)
    // (n-3)：中间块可以放置的位置数
    // 第一个 3：块左边的车不能与块相同
    // 第二个 3：块右边的车不能与块相同
    // 4^(n-3)：剩余 n-3 个车位的自由选择
    s2 = (n - 3) * 3 * 3 * s1;

    // 计算两端情况的数量
    // 公式：2 × 4 × 3 × 4^(n-3)
    // 2：左端和右端两种情况
    // 4：块本身有 4 种品牌选择
    // 3：相邻车位的车不能与块相同
    // 4^(n-3)：剩余 n-3 个车位的自由选择
    s1 *= 2 * 4 * 3;

    // 输出总方案数 = 两端情况 + 中间情况
    cout << s1 + s2 << endl;

    return 0;
}
