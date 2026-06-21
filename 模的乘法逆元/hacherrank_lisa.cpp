/**
 * https://www.hackerrank.com/contests/world-codesprint-5/challenges/longest-increasing-subsequence-arrays
 *
 * @File:   hacherrank_lisa.cpp
 * @Author: Lao Zhang samuelzhang77@outlook.com
 * @Date:   2026-03-14
 *
 */
#include <bits/stdc++.h>
using namespace std;

#define LL long long

const int M = 5e5;      // 最大可能的 m 值
const int N = 1e5;      // 最大可能的 n 值（实际未使用）
const int MOD = 1e9 + 7; // 模数，是一个质数

LL f[M + 1];    // f[i] 存储 i! (阶乘) 模 MOD 的值
LL invf[M + 1]; // invf[i] 存储 i! 的模逆元

/**
 * 快速幂算法
 * 计算 a^b mod MOD
 * 用于求阶乘的逆元 (通过费马小定理)
 */
LL bpower(LL a, LL b)
{
    LL ret = 1;
    while (b) {
        if (b & 1)
            ret = ret * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return ret;
}

/**
 * 预计算阶乘和阶乘的逆元
 *
 * 阶乘：f[i] = i! mod MOD
 * 逆元：先用快速幂求出 M! 的逆元，然后反向递推出所有阶乘的逆元
 * 原理：invf[i] = invf[i+1] * (i+1) mod MOD
 */
void factorials(void)
{
    LL ret = 1;

    f[0] = 1;
    for (int i = 1; i <= M; i++)
        f[i] = ret = ret * i % MOD;

    // 用费马小定理求 M! 的逆元：a^(MOD-2) ≡ a^(-1) (mod MOD)
    invf[M] = bpower(f[M], MOD - 2);

    // 反向递推求所有阶乘的逆元
    for (int i = M - 1; i >= 0; i--)
        invf[i] = invf[i + 1] * (i + 1) % MOD;
}

/**
 * 扩展欧几里得算法
 * 求解 ax + by = gcd(a, b) 的一组整数解 (x, y)
 */
LL ext_gcd(LL a, LL b, int &x, int &y)
{
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }

    int x1, y1;
    int g = ext_gcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a / b);
    return g;
}

/**
 * 求 a 在模 m 下的逆元
 * 使用扩展欧几里得算法
 * 要求 gcd(a, m) = 1
 */
LL get_inv(int a, int m)
{
    int x, y;
    int g = ext_gcd(a, m, x, y);
    if (g != 1)
        x = -1;  // 逆元不存在
    else
        x = (x % m + m) % m;  // 调整到 [0, m-1] 范围
    return x;
}

/**
 * 计算组合数 C(a, b) mod MOD
 * 使用预计算的阶乘和阶乘逆元
 *
 * 公式：C(a, b) = a! / (b! * (a-b)!) mod MOD
 *               = f[a] * (invf[a-b] * invf[b]) mod MOD
 */
LL comb(LL a, LL b)
{
    if (a < b)
        return 0;
    if (a == b)
        return 1;
    return f[a] * (invf[a - b] * invf[b] % MOD) % MOD;
}

int main(void)
{
    int p;

    factorials();  // 预计算阶乘和逆元

    cin >> p;
    while (p--) {
        LL m, n;
        cin >> m >> n;
        LL ans = 0;

        // 特殊情况：如果 n == 1，所有元素只能是 1，只有一种数组
        if (n == 1) {
            cout << "1\n";
            continue;
        }

        /**
         * 核心计算公式：
         * ans = Σ_{i=0}^{m-n} C(m-i-1, n-1) * n^i * (n-1)^(m-n-i)
         *
         * 其中：
         * - i 表示从 1 到 n 的数字中，有多少个数字出现了多于一次
         * - C(m-i-1, n-1) 是组合数部分
         * - n^i 是 i 个"多余数字"的分配方式
         * - (n-1)^(m-n-i) 是剩余位置的分配方式
         *
         * 代码中采用递推方式计算，避免重复计算幂
         */

        LL nn = 1;                    // 初始时 n^0 = 1
        LL bb = bpower(n - 1, m - n); // 初始时 (n-1)^(m-n)
        LL invb = get_inv(n - 1, MOD); // (n-1) 的逆元，用于递推

        for (int i = 0; i <= m - n; i++) {
            int nm;
            // 计算当前项：n^i * (n-1)^(m-n-i) * C(m-i-1, n-1)
            nm = nn * bb % MOD;
            nm = nm * comb(m - i - 1, n - 1) % MOD;
            ans = (ans + nm) % MOD;

            // 递推更新，为下一项做准备
            nn = nn * n % MOD;           // n^(i+1) = n^i * n
            bb = bb * invb % MOD;        // (n-1)^(m-n-(i+1)) = (n-1)^(m-n-i) * (n-1)^(-1)
        }

        cout << ans << '\n';
    }
    return 0;
}
