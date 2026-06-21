/**
 * SPOJ - N-Factorful
 * 问题：统计区间 [a, b] 内恰好有 n 个不同质因数的数的个数
 * https://www.spoj.com/problems/NFACTOR/
 * https://vjudge.net/problem/SPOJ-NFACTOR
 *
 * @File:   N_Factorful.cpp
 * @Author: Lao Zhang <samuelzhang77@yahoo.com>
 * @Date:   2022-01-04
 *
 **/

#include <bits/stdc++.h>

using namespace std;

const int N = 1e6 + 0xAC;  // 最大数值范围：1e6 + 172，0xAC = 172
const int K = 11;          // 质因数个数的上限（题目要求最多10个，这里取11留余量）

vector<int> no_of_factors(N, 0);           // no_of_factors[i] 表示 i 的不同质因数的个数
vector <vector<int>> ans(N, vector<int>(K, 0));  // ans[i][j] 表示从1到i中，恰好有j个不同质因数的数的个数（前缀和数组）

/**
 * @brief 预处理每个数的不同质因数个数，并构建前缀和数组
 *
 * 算法原理：
 * 1. 使用类似埃氏筛的方法计算每个数的不同质因数个数
 * 2. 对于每个质数 i，将其所有倍数 j 的质因数计数加1
 * 3. 构建二维前缀和，便于 O(1) 时间查询任意区间 [a, b] 内满足条件的数的个数
 */
void precompute_prime_factors()
{
    // 第一阶段：计算每个数的不同质因数个数
    for (long long i = 2; i < N; i++) {
        if (no_of_factors[i] == 0) {        // no_of_factors[i] == 0 表示 i 是质数
            for(long long j = i; j < N; j += i)  // 遍历 i 的所有倍数
                no_of_factors[j]++;         // i 是 j 的一个质因数，计数加1
        }
    }

    // 第二阶段：构建前缀和数组 ans[][]
    ans[0][0] = 0;                          // 边界初始化，0 不在考虑范围内
    for (int i = 1; i < N; i++) {
        // 继承前一个数的统计结果
        for(int j = 1; j < K; j++)
            ans[i][j] = ans[i - 1][j];

        // 将当前数 i 加入统计：根据其质因数个数 no_of_factors[i] 增加计数
        ans[i][no_of_factors[i]]++;

        ans[i][0] = 1;                      // ans[i][0] 未使用，保持为1（占位）
    }
}

int main(void)
{
    int t;  // 测试用例数量

    precompute_prime_factors();             // 预处理，只执行一次
    cin >> t;                               // 读入测试用例数
    while (t--) {
        int a, b, n;                        // 查询区间 [a, b] 内恰好有 n 个不同质因数的数的个数

        cin >> a >> b >> n;
        // 利用前缀和数组计算区间答案：前缀和性质 ans[b][n] - ans[a-1][n]
        cout <<  ans[b][n] - ans[a - 1][n] << '\n';
    }
    return 0;
}
