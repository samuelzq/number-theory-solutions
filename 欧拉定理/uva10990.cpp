/**
 * UVA 10990 - Another New Function
 * 计算区间 [m, n] 内所有数的 "欧拉函数深度" 之和。
 * 欧拉函数深度：反复对 n 应用欧拉函数 φ(x)，直到结果为 1 所需的迭代次数。
 * 递推关系：depthphi[n] = depthphi[phi[n]] + 1
 * 
 * @File:   uva10990.cpp
 * @Author: Lao Zhang <samuelzhang77@yahoo.com>
 * @Date:   2022-01-20
 **/

#include <bits/stdc++.h>

using namespace std;

const int N = 2e6; // 题目可能给定的最大上限 (2,000,000)

int phi[N + 1];      // phi[i] 存储 i 的欧拉函数值
int depthphi[N + 1]; // depthphi[i] 存储 i 的欧拉函数深度

/**
 * 计算 1 到 N 范围内所有数的欧拉函数值和欧拉函数深度
 * 使用了筛法思想高效计算 phi
 */
void phi_one2n(void)
{
    // --- 1. 初始化 ---
    for (int i = 0; i <= N; i++) {
        depthphi[i] = 1; // 初始化为1，为递推做准备（特别注意 depthphi[1] = 1 符合题意）
        phi[i] = i;       // 初始假设 phi[i] = i
    }

    // --- 2. 使用筛法计算 phi 值 ---
    for (int i = 2; i <= N; i++) {
        // 如果 phi[i] == i，说明 i 是质数（因为质数的倍数还未被筛过）
        if (phi[i] == i) {
            // 遍历 i 的所有倍数
            for (int j = i; j <= N; j += i) {
                // 欧拉函数公式：phi(j) = j * (1 - 1/p1) * ... * (1 - 1/pk)
                // 这里的操作 phi[j] -= phi[j] / i 等价于 phi[j] = phi[j] * (1 - 1/i)
                // 逐步应用所有质因子 i
                phi[j] -= phi[j] / i;
            }
        }
    }

    // --- 3. 根据递推关系计算 depthphi 值 ---
    // 从 3 开始，因为1，2 对应的值都是1。
    for (int i = 3; i <= N; i++) {
        depthphi[i] = depthphi[phi[i]] + 1;
    }
}

int main(void)
{
    int t; // 测试用例数量

    // 预处理：计算所有需要用到的 phi 和 depthphi
    phi_one2n();

    cin >> t;
    while (t--) {
        int m, n;          // 查询区间的下限和上限
        long long sodf = 0; // 深度之和 Sum of Depths of Phi，使用 long long 防止溢出

        cin >> m >> n;
        // 遍历区间 [m, n]，累加每个数的欧拉函数深度
        for (int i = m; i <= n; i++)
            sodf += depthphi[i];

        cout << sodf << '\n'; // 输出结果
    }
    return 0;
}
