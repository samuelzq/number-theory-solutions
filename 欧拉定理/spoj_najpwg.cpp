/**
 * SPOJ - NAJPWG (Playing with GCD)
 * 题目链接：https://www.spoj.com/problems/NAJPWG/
 *
 * 问题：统计在 1 到 n 的范围内，有多少对整数 (x, y) 满足：
 *       1 ≤ x ≤ y ≤ n 且 gcd(x, y) > 1
 *
 * 核心思路（补集法）：
 * 1. 总共有 n(n+1)/2 个数对（x ≤ y）
 * 2. 减去所有互质数对 (gcd=1) 的数量，即得到 gcd>1 的数对数量
 * 3. 互质数对的数量：对于每个 y，与 y 互质的 x ≤ y 有 φ(y) 个
 *    所以互质总数 = Σ φ(y) (y=1..n)
 * 4. 因此，答案 ans[n] = n(n+1)/2 - Σ φ(i)
 *
 * 递推实现：
 *   ans[i] = ans[i-1] + i - φ(i)
 *
 * @File:   spoj_najpwg.cpp
 * @Author: Lao Zhang <samuelzhang77@yahoo.com>
 * @Date:   2022-01-24
 **/

#include <bits/stdc++.h>
using namespace std;

const int N = 1e5;          // 题目给定的最大 n 值 (100,000)

int phi[N + 1];             // phi[i] 存储 i 的欧拉函数值
int ans[N + 1];             // ans[i] 存储对于 n=i 的最终答案

/**
 * 预处理函数：计算 1 到 N 所有数的欧拉函数值，并递推得到答案
 */
void phi_one2n(void)
{
    // --- 1. 初始化 phi 数组 ---
    for (int i = 0; i <= N; i++)
        phi[i] = i;

    // --- 2. 筛法计算欧拉函数值 ---
    for (int i = 2; i <= N; i++) {
        if (phi[i] == i) {              // i 是质数
            for (int j = i; j <= N; j += i)
                phi[j] -= phi[j] / i;   // φ(j) = φ(j) * (1 - 1/i)
        }
    }

    // --- 3. 递推计算答案 ---
    // ans[1] = 0，因为只有 (1,1) 且 gcd=1，不满足条件
    for (int i = 2; i <= N; i++) {
        // 从 i-1 扩展到 i：
        // - 新增的总对数：i 对 (1,i), (2,i), ..., (i,i)
        // - 其中互质的对数：φ(i) 对（x 与 i 互质）
        // - 所以新增的满足条件的对数为 i - φ(i)
        ans[i] = ans[i - 1] + i - phi[i];
    }
}

int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    phi_one2n();                    // 预处理

    int t;
    cin >> t;

    for (int i = 1; i <= t; i++) {
        int n;
        cin >> n;
        cout << "Case " << i << ": " << ans[n] << '\n';
    }

    return 0;
}
