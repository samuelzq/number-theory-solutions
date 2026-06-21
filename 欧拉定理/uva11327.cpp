/**
 * UVA #11327 "Enumerating Rational Numbers" 枚举有理数 [难度: 中等]
 * https://vjudge.net/problem/UVA-11327
 *
 * 解题思路：
 * 1. 有理数按分母从小到大枚举，同一分母下分子从小到大
 * 2. 只保留最简分数（分子分母互质）
 * 3. 利用欧拉函数φ(n)统计以n为分母的最简分数个数
 *
 * @File:   uva11327.cpp
 * @Author: Lao Zhang <samuelzhang77@yahoo.com>
 * @Date:   2022-01-20
 *
 **/
#include <bits/stdc++.h>

using namespace std;

const int N = 2e5;  // 最大分母范围

int primes[N];      // 存储素数
int prime_num = 0;  // 素数个数
int phi[N + 5];     // 欧拉函数值，phi[i]表示小于等于i且与i互质的数的个数

/**
 * 筛法计算欧拉函数
 * 使用线性筛的思想，同时计算素数表和欧拉函数
 */
void sieve(void)
{
    // 初始化：假设所有数都与自己互质
    for (int i = 0; i <= N; i++)
        phi[i] = i;

    primes[0] = 1;  // 特殊标记分母1的情况（包含0/1）
    // 从2开始筛
    for (int i = 2; i <= N; i++) {
        // 如果phi[i] == i，说明i是质数（没有被前面的数更新过）
        if (phi[i] == i) {
            primes[++prime_num] = i;  // 记录素数
            // 用质数i更新所有i的倍数
            for (int j = i; j <= N; j += i)
                // 欧拉函数公式：φ(n) = n * ∏(1-1/p)
                // 这里用减法实现：φ(j) -= φ(j)/i
                phi[j] -= phi[j] / i;
        }
    }
}

/**
 * 计算最大公约数（辗转相除法）
 * @param a 第一个数
 * @param b 第二个数
 * @return a和b的最大公约数
 */
int gcd(int a, int b)
{
    return b ? gcd(b, a % b) : a;
}

/**
 * 主函数：处理输入并输出第n个有理数
 * 有理数枚举顺序：
 * 0/1, 1/1, 1/2, 2/1, 1/3, 2/3, 3/1, 1/4, 3/4, 4/1, ...
 * 即先按分母排序，同一分母下按分子排序，只保留最简分数
 */
int main(void)
{
    long long n;  // 使用long long因为可能有大数

    // 预处理欧拉函数
    sieve();

    // 循环处理每个输入，直到遇到0
    while (cin >> n && n) {
        // 特殊情况：第一个有理数是0/1
        if (n == 1) {
            cout << "0/1\n";
            continue;
        }

        int i;          // 分母
        n--;            // 减去第一个数0/1，从1/1开始计数

        // 第一步：确定第n个有理数的分母
        // 累加每个分母对应的最简分数个数（φ值），直到找到目标分母
        for (i = 0; i <= N; i++) {
            if (phi[i] >= n)  // 找到目标分母
                break;
            n -= phi[i];       // 减去前面所有分母的个数
        }

        // 第二步：在当前分母下，找到第n个与分母互质的分子
        int j = 0, k = 0;
        while (j < n) {
            k += 1;                // 尝试下一个分子
            if (gcd(i, k) == 1)    // 如果与分母互质
                j++;               // 计数器加1
        }

        // 输出结果：分子/分母
        cout << k << '/' << i << '\n';
    }
    return 0;
}
