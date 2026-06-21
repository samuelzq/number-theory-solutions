/**
 * SPOJ - COMDIV
 * 问题：求两个正整数的共同因子（公约数）的个数
 * 链接：https://www.spoj.com/problems/COMDIV/
 *       https://vjudge.net/problem/SPOJ-COMDIV
 *
 * 核心思路：
 * 1. 两个数的公约数个数，等于它们最大公约数 (GCD) 的约数个数。
 * 2. 预处理：预先计算并存储 1 到 1e6 范围内每个数的约数个数。
 * 3. 查询：对于每对输入 (a, b)，先求 GCD，再直接查表输出结果。
 *
 * @File:   spoj_comdiv.cpp
 * @Author: Lao Zhang <samuelzhang77@yahoo.com>
 * @Date:   2022-01-26
 **/
#include <bits/stdc++.h>
using namespace std;

const int N = 1e6;
int d[N + 1];

void sieve() {
    // 正确的方法：从 1 开始，让每个因子 i 为所有倍数 j 贡献
    for (int i = 1; i <= N; i++) {
        for (int j = i; j <= N; j += i) {
            d[j]++;  // i 是 j 的一个约数
        }
    }
    // 此时 d[1] = 1，d[2] = 2，d[3] = 2，... 全部正确
}

int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    sieve();  // 预处理

    int t;
    cin >> t;
    while (t--) {
        int a, b;
        cin >> a >> b;
        int g = gcd(a, b);
        cout << d[g] << '\n';  // 直接查表，包括因子 1
    }
    return 0;
}
