/**
 * SPOJ - FACT0
 * 问题：对给定的超大整数（最大可达 2^31 量级，即约 21亿）进行质因数分解，输出每个质因数的幂次
 * 原题链接：https://www.spoj.com/problems/FACT0/
 * 镜像链接：https://vjudge.net/problem/SPOJ-FACT0
 *
 * @File:   spoj_fact0.cpp
 * @Author: Lao Zhang <samuelzhang77@yahoo.com>
 * @Date:   2022-01-13
 *
 * 核心算法：优化的试除法（仅检查质数2和奇数）
 * 数据类型：使用 64 位有符号整数（long long），可处理最大约 9e18 的数值
 * 注：原题 n ≤ 2^31-1，因此 long long 完全足够
 *
 */

#include <bits/stdc++.h>

using namespace std;

/**
 * @brief 优化的试除法质因数分解（适用于 long long 范围内的整数）
 * @param n 待分解的正整数（假设 n ≤ 2^63-1）
 * @return 质因数及其指数的配对向量，例如 n = 12 返回 [(2,2), (3,1)]
 *
 * 算法特点：
 * 1. 单独处理质数2（最小的偶质数）
 * 2. 只检查奇数因子（步长为2），跳过所有偶数
 * 3. 当 d*d > n 时提前终止（此时若 n>1 则 n 为质数）
 *
 * 时间复杂度：O(√n) 最坏情况（当 n 为质数或大质数平方时）
 * 空间复杂度：O(log n) 存储质因数
 */
vector<pair<long long, int>> trial_division2(long long n)
{
    vector<pair<long long, int>> factorization;  // 存储质因数和对应指数（底数，指数）
    int cnt = 0;

    // 第一步：处理质数 2（唯一的偶质数）
    while (n % 2 == 0) {
        n /= 2;
        cnt++;
    }
    if (cnt)
        factorization.push_back({2, cnt});        // 记录 2 的指数

    // 第二步：处理奇数因子（从 3 开始，每次增加 2）
    for (long long d = 3; d * d <= n; d += 2) {
        cnt = 0;
        while (n % d == 0) {
            n /= d;
            cnt++;
        }
        if (cnt)
            factorization.push_back({d, cnt});    // 记录奇质因数的指数
    }

    // 第三步：若剩余 n > 1，则 n 本身是一个大于 sqrt(原n) 的质数
    if (n > 1)
        factorization.push_back({n, 1});

    return factorization;
}

int main(void)
{
    long long t;  // 待分解的整数（输入直到 0 结束）

    // 循环读入，直到输入 0 为止
    while (cin >> t && t) {
        // 调用分解函数，获取质因数及指数列表
        vector<pair<long long, int>> dividors = trial_division2(t);
        int i;

        // 输出格式："p1^e1 p2^e2 ... pn^en"（质因数按升序排列，中间用空格分隔，末尾换行）
        // 先输出前 n-1 个因子（后面带空格）
        for (i = 0; i < dividors.size() - 1; i++) {
            cout << dividors[i].first << '^' << dividors[i].second << ' ';
        }
        // 输出最后一个因子（后面不带空格，直接换行）
        cout << dividors[i].first << '^' << dividors[i].second << '\n';
    }
    return 0;
}
