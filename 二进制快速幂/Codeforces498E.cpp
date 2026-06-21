/**
 * https://codeforces.com/contest/498/problem/E
 *
 * @File:   Codeforces498E.cpp
 * @Author: Lao Zhang samuelzhang77@outlook.com
 * @Date:   2026-01-11
 *
 */
#include <iostream>
#include <vector>

using namespace std;

const int MOD = 1e9 + 7;

typedef vector<vector<long long>> Mat;

Mat multiply(const Mat& A, const Mat& B) {
    int n = A.size();
    Mat C(n, vector<long long>(n, 0));
    for (int i = 0; i < n; i++)
        for (int k = 0; k < n; k++)
            if (A[i][k])
                for (int j = 0; j < n; j++)
                    C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % MOD;
    return C;
}

Mat power(Mat A, long long p) {
    int n = A.size();
    Mat res(n, vector<long long>(n, 0));
    for (int i = 0; i < n; i++) res[i][i] = 1;
    while (p > 0) {
        if (p & 1) res = multiply(res, A);
        A = multiply(A, A);
        p >>= 1;
    }
    return res;
}

// 核心：计算高度为 h 的列，左右竖直边状态 L, R 之间的水平边填法
long long get_ways(int L, int R, int h) {
    vector<long long> dp(2, 0);  // dp[0] 表示当前正处理到的那一层格子的“底边”未染色的方案数；dp[1] 表示已染色。
    dp[1] = 1; // 初始化：因为阶梯的最底边是图形的外边界，按题意必须染色。所以底边状态为 1 的方案数初始为 1。底边固定为1
    for (int i = 0; i < h; i++) {
        vector<long long> next_dp(2, 0);  //用于存储当前格子顶边的状态方案数。当前的“顶边”就是下一层格子的“底边”。
        int l = (L >> i) & 1, r = (R >> i) & 1;  //从掩码 L 和 R 中提取出第 $i$ 个格子左边和右边那条竖直边的染色状态（1 为染，0 为不染）。
        for (int h_down = 0; h_down < 2; h_down++) {
            if (!dp[h_down]) continue;  //遍历当前格子底边的可能状态（由上一层决定）。如果某种状态的方案数为 0，直接跳过。
            for (int h_up = 0; h_up < 2; h_up++) {   // 尝试为当前格子的顶边分配一个状态 h_up：染 (1) 或不染 (0)。
                if (i == h - 1 && h_up == 0) continue; // 顶边固定为1
                if (l && r && h_down && h_up) continue; // 四边全满约束
                next_dp[h_up] = (next_dp[h_up] + dp[h_down]) % MOD;
            }
        }
        dp = next_dp;
    }
    return dp[1];
}

int main() {
    vector<long long> w(8);
    int last_h = 0;
    for (int i = 1; i <= 7; i++) {
        cin >> w[i];
        if (w[i] > 0) last_h = i;
    }

    // 初始状态：假想在最左侧有一条全染的竖直边（边界）
    // 状态向量表示当前竖直边的各种 mask 方案数
    vector<long long> dp_vec;
    int cur_h = 0;

    for (int h = 1; h <= 7; h++) {
        if (w[h] == 0) continue;

        // 1. 升维：处理高度变化产生的边界
        if (cur_h == 0) {
            dp_vec.assign(1 << h, 0); // 第一个矩形
            dp_vec[(1 << h) - 1] = 1; // 初始最左边是全染边界
        } else {
            vector<long long> next_vec(1 << h, 0);
            for (int mask = 0; mask < (1 << cur_h); mask++) {
                // 关键：高度增加的部分，竖直边暴露在外，必须是1
                int new_mask = mask | (((1 << (h - cur_h)) - 1) << cur_h);
                next_vec[new_mask] = (next_vec[new_mask] + dp_vec[mask]) % MOD;
            }
            dp_vec = next_vec;
        }
        cur_h = h;

        // 2. 矩阵快速幂处理当前矩形的宽度 w[h]
        int sz = 1 << h;
        Mat T(sz, vector<long long>(sz));
        for (int i = 0; i < sz; i++)
            for (int j = 0; j < sz; j++)
                T[i][j] = get_ways(i, j, h);

        Mat Tw = power(T, w[h]);  // 这是算法提速的核心。它计算在高度为 h 的区域连续走过 w[h] 宽度后的总转移效果。
        vector<long long> next_dp(sz, 0);
        for (int j = 0; j < sz; j++)
            for (int i = 0; i < sz; i++)
                next_dp[j] = (next_dp[j] + dp_vec[i] * Tw[i][j]) % MOD; // 用当前步的转移矩阵 Tw 乘以状态向量 dp_vec，得到这一段宽度处理完后，最右侧竖直边的状态分布。

        dp_vec = next_dp;
    }

    // 最终：图形最右侧的竖直边也是边界，必须是全染状态 (1<<cur_h)-1
    if (cur_h == 0) cout << 0 << endl;
    else cout << dp_vec[(1 << cur_h) - 1] << endl;

    return 0;
}
