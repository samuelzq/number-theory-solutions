/**
 * https://codeforces.com/contest/222/problem/E
 *
 * @File:   CodeForces222E.cpp
 * @Author: Lao Zhang samuelzhang77@outlook.com
 * @Date:   2026-03-22
 *
 */

#include <iostream>
#include <vector>
#include <string>
#include <cstring>
using namespace std;

typedef long long ll;
const int MOD = 1000000007;

// 将字母映射到 0..m-1
int toIndex(char c) {
    if (c >= 'a' && c <= 'z') return c - 'a';
    else return c - 'A' + 26;
}

// 矩阵乘法，模 MOD
vector<vector<ll>> matMul(const vector<vector<ll>>& A, const vector<vector<ll>>& B) {
    int m = A.size();
    vector<vector<ll>> C(m, vector<ll>(m, 0));
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            for (int k = 0; k < m; k++) {
                C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % MOD;
            }
        }
    }
    return C;
}

// 矩阵快速幂
vector<vector<ll>> matPow(vector<vector<ll>> M, ll power) {
    int m = M.size();
    // 单位矩阵
    vector<vector<ll>> res(m, vector<ll>(m, 0));
    for (int i = 0; i < m; i++) res[i][i] = 1;

    while (power > 0) {
        if (power & 1) {
            res = matMul(res, M);
        }
        M = matMul(M, M);
        power >>= 1;
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll n;
    int m, k;
    cin >> n >> m >> k;

    // 构建允许矩阵，初始全部允许
    vector<vector<ll>> M(m, vector<ll>(m, 1));

    // 读取禁止对
    for (int i = 0; i < k; i++) {
        string s;
        cin >> s;
        int a = toIndex(s[0]);
        int b = toIndex(s[1]);
        if (a < m && b < m) { // 确保不超过 m
            M[a][b] = 0;
        }
    }

    if (n == 1) {
        // 长度为 1 的链，每种核苷酸都可作为起点
        cout << m % MOD << endl;
        return 0;
    }

    // 计算 M^(n-1)
    vector<vector<ll>> Mn1 = matPow(M, n - 1);

    // 初始向量 v1 全 1
    ll ans = 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            ans = (ans + Mn1[i][j]) % MOD;
        }
    }

    cout << ans << endl;

    return 0;
}
