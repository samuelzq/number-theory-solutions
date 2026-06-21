/**
 * https://vjudge.net/problem/UVA-11029
 * https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1970
 *
 * @File:   uva_11029.cpp
 * @Author: Lao Zhang samuelzhang77@outlook.com
 * @Date:   2026-03-22
 *
 */
#include <bits/stdc++.h>  // 万能头文件，包含所有常用库

// 快速幂取模函数
// 计算 (b^p) % m
int bigmod(int b, int p, int m)
{
    int r = 1;           // 结果初始化为 1

    b %= m;              // 先将底数取模，避免中间结果过大

    while (p) {          // 当指数 p 不为 0 时循环
        if (p & 1)       // 如果当前二进制位是 1
            r = (r * b) % m;   // 将当前底数乘入结果并取模

        b = (b * b) % m;       // 底数平方，准备下一位
        p >>= 1;               // 指数右移一位
    }

    return r;            // 返回最终结果
}

// 计算 n^k 的前 l 位数字（这里是 l=2，表示前三位）
// 注意：实际计算时，l=2 对应前三位（因为 10^(l+0.xxx) 前三位）
int first_digit(int a, int b, int l)
{
    double x, y;

    // 计算 k * log10(n)
    x = b * log10(a);

    // 取出小数部分
    // floor(x) 是整数部分，x - floor(x) 是小数部分
    x = x - floor(x);

    // 10^(l + 小数部分)
    // 当 l=2 时，这个数在 100 到 999.9 之间
    y = floor(pow(10, l + x));

    return (int)y;       // 返回前三位数字
}

int main(void)
{
    int t;               // 测试用例数

    scanf("%d", &t);     // 读入测试用例数

    while (t--) {        // 循环处理每个测试用例
        int n, k;        // 底数和指数
        scanf("%d %d", &n, &k);

        // 输出格式：
        // first_digit(n, k, 2) 得到前三位
        // bigmod(n, k, 1000) 得到后三位，用 %03d 保证输出三位（不足补零）
        printf("%d...%03d\n", first_digit(n, k, 2), bigmod(n, k, 1000));
    }

    return 0;
}
