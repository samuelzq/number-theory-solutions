/**
 * SPOJ - DCEPC12G (G Force)
 * 题目链接: https://www.spoj.com/problems/DCEPC12G/
 *
 * 问题：定义了一个函数 g(n)，其计算与欧拉函数 φ(n) 和素数个数相关。
 * 核心公式：g(1)=1；对于 n>1，g(n) = φ(n) ^ ( (cnt - φ(n))! )  mod MOD
 * 其中 cnt 是小于等于 n 的素数个数，(cnt - φ(n))! 表示阶乘。
 *
 * 算法步骤：
 * 1. 使用筛法预处理 1~N 所有数的欧拉函数值 phi[]。
 * 2. 在筛法过程中，同步统计素数个数 cnt。
 * 3. 对于每个 i，计算指数 exp = factorial(cnt - phi[i])。
 * 4. 使用快速幂计算 g[i] = phi[i] ^ exp % MOD。
 * 5. 对每个查询 O(1) 输出 g[n]。
 *
 * 时间复杂度：O(N log log N) 预处理 + O(T) 查询
 * 空间复杂度：O(N)
 *
 * @File:   spoj_dcepc12g.cpp
 * @Author: Lao Zhang <samuelzhang77@yahoo.com>
 * @Date:   2022-01-25
 **/

#include <bits/stdc++.h>
using namespace std;

const int N = 1e7;          // 题目给定的最大 n 值 (10,000,000)
const int MOD = 1e9 + 7;    // 模数，用于取模运算

int phi[N + 1];             // phi[i] 存储 i 的欧拉函数值
int g[N + 1];               // g[i] 存储最终答案，即函数 G 在 i 处的值

/**
 * 快速幂取模运算
 * 计算 (a^b) % mod
 *
 * @param a 底数
 * @param b 指数
 * @param mod 模数
 * @return 计算结果
 */
int bin_exp(int a, int b, int mod)
{
    int ret = 1;
    a = a % mod;            // 先对底数取模

    while (b) {             // 当指数不为0时循环
        if (b & 1)          // 如果当前二进制位为1
            ret = ret * a % mod;  // 乘上当前底数并取模
        a = a * a % mod;    // 底数平方并取模
        b >>= 1;            // 指数右移一位
    }
    return ret;
}

/**
 * 阶乘计算（取模）
 * 计算 a! % mod
 *
 * @param a 非负整数
 * @param mod 模数
 * @return 阶乘结果对 mod 取模的值
 */
int factorial(int a, int mod)
{
    int ret = 1;
    for (int i = 1; i <= (a < 0) ? 0 : a; i++)
        ret = ret * i % mod;  // 累乘并取模
    return ret;
}

/**
 * 预处理函数：计算 phi[] 和 g[]
 * 使用筛法同时完成欧拉函数计算和答案预处理
 */
void sieve(void)
{
    // --- 1. 初始化 phi 数组 ---
    for (int i = 0; i <= N; i++)
        phi[i] = i;         // 初始假设 phi[i] = i

    // --- 2. 初始化 g[1] ---
    g[1] = 1;               // 根据定义，g[1] = 1

    // --- 3. 筛法计算欧拉函数并同步计算 g[i] ---
    int cnt = 0;            // 计数器：记录小于等于当前 i 的素数个数
    for (int i = 2; i <= N; i++) {
        // 如果 phi[i] == i，说明 i 是质数
        if (phi[i] == i) {
            // 用质数 i 更新所有倍数 j 的 phi 值
            for (int j = i; j <= N; j += i) {
                // 欧拉函数公式：φ(j) -= φ(j)/i
                phi[j] -= phi[j] / i;
            }
            cnt++;          // 发现一个素数，计数器加1
        }

        // --- 4. 计算 g[i] ---
        // 指数 f = factorial(cnt - phi[i], MOD)
        // 注意：cnt 是当前素数个数，phi[i] 是 i 的欧拉函数值
        int f = factorial(cnt - phi[i], MOD);
        // g[i] = phi[i] ^ f % MOD
        g[i] = bin_exp(phi[i], f, MOD);
    }
}

int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    sieve();                // 预处理答案

    int t;
    cin >> t;               // 读取测试用例数

    while (t--) {
        int n;
        cin >> n;           // 读取当前查询的 n
        cout << g[n] << '\n'; // 直接输出预计算的结果
    }

    return 0;
}
