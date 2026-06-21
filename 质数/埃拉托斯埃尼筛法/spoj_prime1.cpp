/**
 * SPOJ PRIME1 - 区间质数筛选
 * 题目链接：https://www.spoj.com/problems/PRIME1/
 *
 * 功能：对于每个测试用例，输出区间 [m, n] 内的所有质数
 * 特点：n 可能很大（最大 10^9），但区间长度 n-m ≤ 100000
 *
 * @File:   spoj_prime1.cpp
 * @Author: Lao Zhang samuelzhang77@outlook.com
 * @Date:   2024-06-07
 */
#include <bits/stdc++.h>
using namespace std;

#define MAX_INTERVAL_LEN 100005  // 最大区间长度 + 安全边界

// is_composite[i] = 1 表示 i+m 是合数，= 0 表示是质数（初始值0表示质数）
char is_composite[MAX_INTERVAL_LEN] = {0};

/**
 * 分段筛法初始化函数
 * @param l 区间左端点
 * @param r 区间右端点
 *
 * 原理：用不超过 √r 的质数去筛区间 [l, r] 内的合数
 * 标记数组：is_composite[pos] = 1 表示该位置对应的数是合数
 */
void init(int l, int r)
{
    int limit = sqrt(r);  // 只需要筛到 √r

    // 初始化标记数组，全部设为0（假设所有数都是质数）
    memset(is_composite, 0, MAX_INTERVAL_LEN);

    // 枚举所有不超过 √r 的数 i
    for (int i = 2; i <= limit; i++) {
        // 计算 i 在区间 [l, r] 内的第一个倍数
        // max(i*i, (l+i-1)/i * i) 的含义：
        // - i*i：从 i 的平方开始标记（小于 i² 的倍数已被更小的质数标记）
        // - (l+i-1)/i * i：大于等于 l 的最小 i 的倍数（向上取整）
        int start = max(i * i, (l + i - 1) / i * i);

        // 标记区间内所有 i 的倍数为合数
        for (int j = start; j <= r; j += i) {
            is_composite[j - l] = 1;  // 使用偏移量 j-l 作为数组索引，1表示合数
        }
    }

    // 特殊处理：如果区间包含 1，1 不是质数
    if (l == 1)
        is_composite[0] = 1;  // 标记 1 为合数
}

int main(void)
{
    int t;

    scanf("%d", &t);  // 读取测试用例个数

    while (t--) {
        int m, n;

        scanf("%d %d", &m, &n);  // 读取区间 [m, n]

        init(m, n);  // 分段筛法找出区间内的质数

        // 输出区间内的所有质数
        for (int i = 0; i <= n - m; i++) {
            if (!is_composite[i]) {  // is_composite[i] == 0 表示是质数
                printf("%d\n", i + m);  // 还原实际数值
            }
        }
        printf("\n");  // 每个测试用例后输出一个空行
    }

    return 0;
}
