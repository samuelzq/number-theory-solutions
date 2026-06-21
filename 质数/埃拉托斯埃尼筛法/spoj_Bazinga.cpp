/**
 * SPOJ - Bazinga!
 * https://www.spoj.com/problems/DCEPC505/
 * https://vjudge.net/problem/SPOJ-DCEPC505
 *
 * 先筛出所有满足条件的数。
 *
 * @File:   Bazinga.cpp
 * @Author: Lao Zhang <samuelzhang77@yahoo.com>
 * @Date:   2021-12-31
 *
 **/
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 22000000;
int cnt[MAXN + 1];    // 记录不同质因数的个数
bool is_sq[MAXN + 1]; // 记录是否含有平方因子
int bazinga[2000005]; // 存储第 K 个 Bazinga 数
int total = 0;

void sieve() {
    for (int i = 2; i <= MAXN; ++i) {
        // 如果 cnt[i] == 0，说明 i 是质数
        if (cnt[i] == 0) {
            // 将所有 i 的倍数的质因数计数加 1
            for (int j = i; j <= MAXN; j += i) {
                cnt[j]++;
            }
            // 将所有 i^2 的倍数标记为含有平方因子
            // 注意：使用 long long 防止 i*i 溢出
            if (1LL * i * i <= MAXN) {
                for (int j = i * i; j <= MAXN; j += i * i) {
                    is_sq[j] = true;
                }
            }
        }
    }

    // 收集满足条件的数：恰好 2 个不同质因数且无平方因子
    for (int i = 2; i <= MAXN; ++i) {
        if (cnt[i] == 2 && !is_sq[i]) {
            bazinga[++total] = i;
            if (total >= 2000000) break;
        }
    }
}

int main() {
    // 快速 I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    sieve();

    int T, K;
    if (cin >> T) {
        while (T--) {
            cin >> K;
            cout << bazinga[K] << "\n";
        }
    }

    return 0;
}
