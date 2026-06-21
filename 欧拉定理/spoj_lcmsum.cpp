/**
 * SPOJ - LCMSUM (LCM Sum)
 * 题目链接：https://www.spoj.com/problems/LCMSUM/
 * 
 * 问题：计算 S(n) = Σ lcm(i, n) ，其中 i 从 1 到 n。
 * 
 * 数学推导结果：
 *   S(n) = n/2 * (1 + Σ_{d|n} d * φ(d))
 * 
 * 算法步骤：
 * 1. 预处理 1~N 所有数的欧拉函数值 phi[]
 * 2. 对于每个因子 d，将贡献 d * phi[d] 累加到它的所有倍数 j 上
 * 3. 对于每个数 n，最终答案 sum[n] = (1 + 累加值) * n / 2
 * 
 * 时间复杂度：O(N log N) 预处理 + O(1) 查询
 * 空间复杂度：O(N)
 * 
 * @File:   spoj_lcmsum.cpp
 * @Author: Lao Zhang <samuelzhang77@yahoo.com>
 * @Date:   2022-01-21
 */

#include <bits/stdc++.h>
using namespace std;

const int N = 1e6;          // 题目给定的最大 n 值 (1,000,000)
long long sum[N + 1];       // sum[n] 存储最终答案 S(n)
int phi[N + 1];             // phi[i] 存储 i 的欧拉函数值

/**
 * 预处理函数：计算所有需要的 phi 值和答案 sum[]
 */
void get_sum(void)
{
    // --- 1. 初始化 phi 数组 ---
    for (int i = 0; i <= N; i++)
        phi[i] = i;         // 初始假设每个数都是质数，phi[i] = i

    // --- 2. 筛法计算欧拉函数值 ---
    for (int i = 2; i <= N; i++) {
        // 如果 phi[i] == i，说明 i 是质数（没有被前面的数更新过）
        if (phi[i] == i) {
            // 用质数 i 更新所有倍数 j 的 phi 值
            for (int j = i; j <= N; j += i) {
                // 欧拉函数公式：φ(j) = j * ∏(1 - 1/p)
                // 这里用减法实现：phi[j] -= phi[j] / i
                phi[j] -= phi[j] / i;
            }
        }
    }

    // --- 3. 计算核心贡献：d * φ(d) 对所有倍数的累加 ---
    // 对于每个因子 d，将 d * φ(d) 加到它的所有倍数 j 上
    // 这样，对于每个数 j，sum[j] 最终会累加所有它的因子 d 的贡献
    for (int d = 1; d <= N; d++) {
        long long contribution = (long long)d * phi[d];  // d * φ(d)
        for (int multiple = d; multiple <= N; multiple += d) {
            sum[multiple] += contribution;               // 贡献加到倍数上
        }
    }

    // --- 4. 根据公式构造最终答案 ---
    // 公式：S(n) = n/2 * (1 + Σ_{d|n} d * φ(d))
    // 此时 sum[n] 中已经存储了 Σ_{d|n} d * φ(d)
    for (int i = 1; i <= N; i++) {
        sum[i] = (sum[i] + 1) * (long long)i / 2;       // 套用公式
    }
}

int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    get_sum();                  // 预处理答案

    int t;
    cin >> t;                   // 读取测试用例数

    while (t--) {
        int n;
        cin >> n;               // 读取当前查询的 n
        cout << sum[n] << '\n'; // 直接输出预计算的结果
    }

    return 0;
}
