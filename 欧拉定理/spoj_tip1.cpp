/**
 * SPOJ - Totient in Permutation (easy)
 * 问题：寻找小于 M 的数 N，使得 φ(N) 是 N 的排列，且 N/φ(N) 最小
 * 如果有多个，取最大的 N
 *
 * 核心优化：
 * 1. 预处理所有答案，查询 O(1)
 * 2. 只用一个数组 ans[] 存储每个 M 对应的最优解
 * 3. 在筛法计算 phi 的同时，动态维护最优解
 *
 * @File:   spoj_tip1.cpp
 * @Author: Lao Zhang <samuelzhang77@yahoo.com>
 * @Date:   2022-01-19
 **/

#include <bits/stdc++.h>
using namespace std;

const int M = 1e7;      // 题目给定的最大范围 10^7
int phi[M + 0xac];      // 欧拉函数值数组，多开一点空间防止越界
int ans[M + 0xac];      // ans[x] 存储小于等于 x 的最优解

/**
 * 检查两个数是否为排列关系
 * 方法：用计数数组统计每个数字出现次数
 *
 * @param n 原数
 * @param m 要比较的数（通常是 φ(n)）
 * @return true 如果两个数由相同数字组成（允许前导零？题目要求整数>0不允许前导零）
 */
bool check(int n, int m)
{
    char bit1[10] = {0};  // 数字 0-9 的计数器，用 char 节省空间
    char bit2[10] = {0};

    // 统计 n 的各位数字
    while (n) {
        int b = n % 10;
        bit1[b]++;
        n /= 10;
    }

    // 统计 m 的各位数字
    while (m) {
        int b = m % 10;
        bit2[b]++;
        m /= 10;
    }

    // 比较每个数字出现次数
    for (int i = 0; i < 10; i++) {
        if (bit1[i] != bit2[i])
            return false;
    }
    return true;
}

/**
 * 计算 1 到 M 所有数的欧拉函数值
 * 同时动态维护 ans[] 数组，存储当前最优解
 *
 * 核心思想：随着 i 增加，逐步更新最优解
 * 对于每个 i，如果它满足条件，就与当前最优解比较
 * 比较规则：
 *   1. 比值 i/phi[i] 越小越好（用交叉乘法避免浮点）
 *   2. 比值相同时，取较大的 i
 */
void phi_one2n(void)
{
    // --- 1. 初始化 phi 数组 ---
    for (int i = 0; i <= M; i++)
        phi[i] = i;  // 初始假设 phi[i] = i

    // --- 2. 筛法求欧拉函数 ---
    for (int i = 2; i <= M; i++) {
        // 如果 phi[i] == i，说明 i 是质数（没被更新过）
        if (phi[i] == i) {
            // 用质数 i 更新所有倍数
            for (int j = i; j <= M; j += i) {
                // 欧拉函数公式：φ(j) = j * (1 - 1/p1) * ... * (1 - 1/pk)
                // 这里用减法实现：phi[j] -= phi[j] / i
                phi[j] -= phi[j] / i;
            }
        }
    }

    // --- 3. 动态维护 ans 数组 ---
    int ans1 = 21;  // 初始最优解设为 21（已知第一个满足条件的数）
                    // 注意：题目要求 N > 1，所以从 2 开始，但 21 是已知最小解

    // 从 21 开始遍历到 M
    for (int i = 21; i <= M; i++) {
        // 检查 i 是否满足条件：φ(i) 是 i 的排列
        if (check(i, phi[i])) {
            // 满足条件，与当前最优解比较
            // 比较规则：i/phi[i] 与 ans1/phi[ans1]
            // 交叉乘法：i * phi[ans1] <= ans1 * phi[i] 等价于 i/phi[i] <= ans1/phi[ans1]
            // 注意：这里用 long long 防止乘法溢出
            if ((long long)i * phi[ans1] <= (long long)ans1 * phi[i]) {
                ans1 = i;  // 更新最优解
            }
        }
        // ans[i] 存储小于等于 i 的最优解
        // 注意：这里 ans[i] 可能等于 i，如果 i 本身是最优解
        // 否则 ans[i] 继承之前的最优解
        ans[i] = ans1;
    }

    // 注意：对于 i < 21 的情况，ans[i] 没有被赋值
    // 但题目输入 M ≥ 2，且 M < 21 时，ans[M-1] 会是 0
    // 主函数中会据此判断 "No solution."
}

int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // 预处理
    phi_one2n();

    int t;
    cin >> t;

    while (t--) {
        int m;
        cin >> m;

        // 注意：题目要找 N < M，所以检查 ans[m-1]
        // 如果 ans[m-1] == 0，说明在 [2, m-1] 范围内没有找到解
        if (ans[m - 1] == 0) {
            cout << "No solution.\n";
        } else {
            cout << ans[m - 1] << '\n';
        }
    }

    return 0;
}
