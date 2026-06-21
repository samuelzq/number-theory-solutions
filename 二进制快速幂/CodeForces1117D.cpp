/**
 * https://codeforces.com/problemset/problem/1117/D
 * D. Magic Gems
 *
 * @File:   CodeForces1117D.cpp
 * @Author: Lao Zhang <samuelzhang77@outlook.com>
 * @Date:   2026-01-06
 *
 **/
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int MOD = 1e9 + 7;

// 矩阵乘法 (M x M)
vector<vector<ll>> matMul(const vector<vector<ll>>& A, const vector<vector<ll>>& B, int M) {
    vector<vector<ll>> C(M, vector<ll>(M, 0));
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < M; j++) {
            for (int k = 0; k < M; k++) {
                C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % MOD;
            }
        }
    }
    return C;
}

// 矩阵快速幂
vector<vector<ll>> matPow(vector<vector<ll>> T, ll power, int M) {
    vector<vector<ll>> res(M, vector<ll>(M, 0));
    for (int i = 0; i < M; i++) res[i][i] = 1;
    while (power > 0) {
        if (power & 1) {
            res = matMul(res, T, M);
        }
        T = matMul(T, T, M);
        power >>= 1;
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll N;
    int M;
    cin >> N >> M;

    if (N < M) {
        cout << 1 << endl;
        return 0;
    }

    // 构建转移矩阵 T (M x M)
    vector<vector<ll>> T(M, vector<ll>(M, 0));
    T[0][0] = 1;
    T[0][M-1] = 1;
    for (int i = 1; i < M; i++) {
        T[i][i-1] = 1;
    }

    // 初始向量 v
    vector<ll> v(M, 1); // dp[M-1], dp[M-2], ..., dp[0] 都是 1

    // 需要乘的次数
    ll power = N - (M - 1);
    vector<vector<ll>> Tp = matPow(T, power, M);

    // 结果 = Tp 的第一行 点乘 v
    ll ans = 0;
    for (int j = 0; j < M; j++) {
        ans = (ans + Tp[0][j] * v[j]) % MOD;
    }

    cout << ans << endl;

    return 0;
}
