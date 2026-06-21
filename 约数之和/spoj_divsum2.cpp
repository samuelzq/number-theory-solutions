/**
 * SPOJ - DIVSUM2 (真因子之和 - 大数版)
 * 问题链接：https://www.spoj.com/problems/DIVSUM2/
 * 解题思路：使用质因数分解法计算所有因子之和，再减去自身
 *
 * @File:   spoj_divsum2.cpp
 * @Author: Lao Zhang <samuelzhang77@yahoo.com>
 * @Date:   2022-01-27
 *
 **/
#include <bits/stdc++.h>

using namespace std;
const int N = 11e7;      // 筛法预处理的上限，实际只需要到sqrt(最大输入)即可
#define LL long long

vector<bool> is_prime(N + 1, true);  // 布尔数组标记质数
vector<int> primes;                   // 存储质数的向量

/**
 * 埃拉托斯特尼筛法：预先生成质数表
 */
void sieve(void)
{
    // 0和1不是质数
    is_prime[0] = is_prime[1] = false;
    
    // 经典筛法：从2开始，标记合数
    for (int i = 2; i * i <= N; i++) {
        if (is_prime[i] == true) {
            // 从i*i开始标记，因为更小的倍数已经被更小的质数标记过了
            for (int j = i * i; j <= N; j += i)
                is_prime[j] = false;
        }
    }

    // 将质数收集到primes向量中（只存奇数，2单独处理）
    primes.emplace_back(2);
    for (int i = 3; i <= N; i += 2) {
        if (is_prime[i] == true)
            primes.emplace_back(i);
    }
}

/**
 * 快速幂：计算a的b次方
 * 使用二进制分解b的方法，时间复杂度O(log b)
 */
LL power(LL a, LL b)
{
    LL ret = 1;
    while (b) {
        if (b & 1)          // 如果b的当前二进制位为1
            ret *= a;       // 累乘当前a
        a *= a;             // a自乘，准备下一位
        b >>= 1;            // b右移一位
    }
    return ret;
}

/**
 * 计算数n的所有因子之和（包括自身）
 * 使用公式：σ(n) = ∏ (p_i^(a_i+1) - 1)/(p_i - 1)
 */
LL d(LL n)
{
    LL ret = 1;  // 初始化结果为1（乘法单位元）

    // 遍历质数表，只需要检查到√n
    for (LL i = 0; i < primes.size() && primes[i] * primes[i] <= n; i++) {
        int cnt = 0;  // 记录当前质因子的指数

        // 如果当前质数能整除n，说明它是n的一个质因子
        if (n % primes[i] == 0) {
            // 统计该质因子的指数，并不断除以它
            while (n % primes[i] == 0) {
                cnt++;
                n /= primes[i];
            }
            // 应用公式：p^(cnt+1)-1 除以 p-1
            // 注意：这里计算的是等比数列和 p^0 + p^1 + ... + p^cnt
            ret *= (power(primes[i], cnt + 1) - 1) / (primes[i] - 1);
        }
    }

    // 如果最后n大于1，说明剩下一个大于√原数的大质因子
    // 此时这个质因子的指数为1，贡献因子为 1 + p
    if (n > 1)
        ret *= 1LL + n;  // 即 (p^(1+1)-1)/(p-1) = (p^2-1)/(p-1) = p+1

    return ret;
}

int main(void)
{
    int t;

    sieve();  // 预处理质数表
    cin >> t;
    while (t--) {
        LL n;
        cin >> n;
        // 输出真因子之和 = 所有因子之和 - 自身
        cout << d(n) - n << '\n';
    }
    return 0;
}
