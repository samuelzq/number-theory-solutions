/**
 * https://lightoj.com/problem/mathematically-hard
 * https://vjudge.net/problem/LightOJ-1007
 *
 * @File:   loj1007.cpp
 * @Author: Lao Zhang samuelzhang77@outlook.com
 * @Date:   2026-02-22
 *
 */
#include <bits/stdc++.h>
using namespace std;

const int N = 5e6;
int phi[N + 5];
unsigned long long sum[N + 5];

/**
 * 经典筛法求欧拉函数
 * 时间复杂度 O(N log log N)
 */
void computePhi() {
    // 初始化
    for (int i = 1; i <= N; i++)
        phi[i] = i;

    // 筛法求欧拉函数
    for (int i = 2; i <= N; i++) {
        if (phi[i] == i) {  // i 是素数
            for (int j = i; j <= N; j += i) {
                // 欧拉函数公式：φ(j) = j * (1 - 1/i)
                // 等价于 φ(j) -= φ(j) / i
                phi[j] -= phi[j] / i;
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    computePhi();

    // 计算平方和前缀和（使用 unsigned long long）
    sum[0] = 0;
    for (int i = 1; i <= N; i++) {
        unsigned long long val = phi[i];
        sum[i] = sum[i - 1] + val * val;
    }

    int T;
    cin >> T;

    for (int caseNum = 1; caseNum <= T; caseNum++) {
        int a, b;
        cin >> a >> b;

        unsigned long long ans = sum[b] - sum[a - 1];

        cout << "Case " << caseNum << ": " << ans << '\n';
    }

    return 0;
}
