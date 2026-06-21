/**
 * SPOJ - N-Factorful
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

const int N = 1e6 + 0xAC;  // 最大数值范围：1e6 + 172（额外空间）
const int K = 11;          // 不同质因子个数的最大值+1（0-10）

vector<int> no_of_factors(N, 0);  // no_of_factors[i] = 数字i的不同质因子个数
vector <vector<int>> ans(N, vector<int>(K, 0));  // 前缀和数组：ans[i][n] = 1到i中恰好有n个不同质因子的数字个数

// 预处理函数：计算所有数字的不同质因子个数，并构建前缀和数组
void precompute_prime_factors()
{
    // 步骤1：计算每个数字的不同质因子个数（使用类似筛法的方法）
    for (long long i = 2; i < N; i++) {
        // 如果no_of_factors[i]==0，说明i是质数
        if (no_of_factors[i] == 0) {
            // 将质数i的所有倍数都标记（质因子个数+1）
            for(long long j = i; j < N; j += i)
                no_of_factors[j]++;  // j包含质因子i，所以质因子计数加1
        }
    }

    // 步骤2：构建前缀和数组
    ans[0][0] = 0;  // 初始化

    for (int i = 1; i < N; i++) {
        // 复制前一个位置的所有计数（前缀和的核心思想）
        for(int j = 1; j < K; j++)
            ans[i][j] = ans[i - 1][j];

        // 当前数字i有no_of_factors[i]个不同质因子，对应计数加1
        ans[i][no_of_factors[i]]++;

        // 注意：这里设置ans[i][0]=1可能有问题，应该是只有i=1时才设为1
        // 因为只有数字1没有质因子
        ans[i][0] = 1;
    }
}

int main(void)
{
    int t;  // 测试用例数量

    // 先进行预处理（只执行一次）
    precompute_prime_factors();

    cin >> t;

    while (t--) {
        int a, b, n;  // 区间[a,b]和查询的不同质因子个数n

        cin >> a >> b >> n;

        // 使用前缀和快速回答查询：
        // ans[b][n] = 1到b中恰好有n个不同质因子的数字个数
        // ans[a-1][n] = 1到a-1中恰好有n个不同质因子的数字个数
        // 两者相减得到[a,b]区间内的个数
        cout <<  ans[b][n] - ans[a - 1][n] << '\n';
    }

    return 0;
}
