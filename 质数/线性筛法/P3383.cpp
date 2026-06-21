/**
 * https://www.luogu.com.cn/problem/P3383
 *
 * @File:   P3383.cpp
 * @Author: Lao Zhang samuelzhang77@outlook.com
 * @Date:   2026-03-28
 *
 */
#include <iostream>
#include <vector>
using namespace std;

const int N = 1e8 + 5;  // 根据题目 n ≤ 10^8 设置
int n, q;
vector<int> lp(N + 1, 0), pr;

void linearSieve() {
    for (int i = 2; i <= N; ++i) {
        if (lp[i] == 0) { // 发现质数
            lp[i] = i;
            pr.push_back(i);
        }

        for (int p : pr) {
            if (p > lp[i] || i * p > N) break; 
            lp[i * p] = p; // 用最小质因子标记
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q;

    linearSieve();  // 预处理

    while (q--) {
        int x;
        cin >> x;
        // 输出结果
        cout << pr[x - 1] << '\n';
    }

    return 0;
}
