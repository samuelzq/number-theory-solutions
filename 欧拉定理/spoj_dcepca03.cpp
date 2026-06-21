/**
 * SPOJ - Totient Extreme
 * https://www.spoj.com/problems/DCEPCA03/
 * https://vjudge.net/problem/SPOJ-DCEPCA03
 *
 * 最终结果即为一级累加的平方。
 *
 * @File:   spoj_dcepca03.cpp
 * @Author: Lao Zhang <samuelzhang77@yahoo.com>
 * @Date:   2022-01-24
 *
 **/
#include <bits/stdc++.h>
using namespace std;

const int N = 1e4;          // 题目给定的最大 n 值 (10,000)
long long h[N + 1];         // h[n] 存储最终答案，即 (Σφ(k))²
int phi[N + 1];             // phi[i] 存储 i 的欧拉函数值

/**
 * 预处理函数：计算所有需要的 phi 值和答案 h[]
 * 优化：使用前缀和避免内层循环
 */
void get_h(void)
{
    // --- 1. 初始化 phi 数组 ---
    for (int i = 0; i <= N; i++)
        phi[i] = i;         // 初始假设每个数都是质数，phi[i] = i

    // --- 2. 筛法计算欧拉函数值 ---
    for (int i = 2; i <= N; i++) {
        // 如果 phi[i] == i，说明 i 是质数
        if (phi[i] == i) {
            // 用质数 i 更新所有倍数 j
            for (int j = i; j <= N; j += i) {
                // 欧拉函数公式：φ(j) -= φ(j)/i
                phi[j] -= phi[j] / i;
            }
        }
    }

    // --- 3. 使用前缀和计算答案，避免内层循环 ---
    long long sum = 0;      // 累加变量，存储 Σφ(k)
    for (int i = 1; i <= N; i++) {
        sum += phi[i];       // 累加当前 phi[i]
        h[i] = sum * sum;    // 平方后存入 h[i]
    }
}

int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    get_h();                // 预处理答案

    int t;
    cin >> t;

    while (t--) {
        int n;
        cin >> n;
        cout << h[n] << '\n';
    }

    return 0;
}
