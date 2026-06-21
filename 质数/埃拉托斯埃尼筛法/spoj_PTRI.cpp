/**
 * https://www.spoj.com/problems/PTRI/
 *
 * @File:   spoj_PTRI.cpp
 * @Author: Lao Zhang samuelzhang77@outlook.com
 * @Date:   2026-02-08
 *
 */
#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <bitset>

using namespace std;

// 10^8 范围内大约有 5,761,455 个素数
const int MAXN = 100000001;
bitset<MAXN> is_prime;
vector<int> primes;

void fast_sieve() {
    is_prime.set();
    is_prime[0] = is_prime[1] = 0;
    
    // 预估素数数量进行 reserve 避免动态扩容耗时
    primes.reserve(5761455);
    
    for (int p = 2; p < MAXN; p++) {
        if (is_prime[p]) {
            primes.push_back(p);
            // 只有当 p*p 不溢出且小于 MAXN 时才进入内层循环
            if (1LL * p * p < MAXN) {
                for (int i = p * p; i < MAXN; i += p)
                    is_prime[i] = 0;
            }
        }
    }
}

void solve() {
    int n;
    if (!(cin >> n)) return;

    // 快速排除非素数
    if (n < 2 || !is_prime[n]) {
        cout << -1 << "\n";
        return;
    }

    // 使用二分查找获取素数在 vector 中的序号 (k 从 1 开始)
    auto it = lower_bound(primes.begin(), primes.end(), n);
    long long k = distance(primes.begin(), it) + 1;

    // 计算行号 i (解不等式 i*(i+1)/2 >= k)
    long long i = ceil((-1.0 + sqrt(1.0 + 8.0 * k)) / 2.0);
    
    // 计算列号 j
    long long prev_total = (i - 1) * i / 2;
    long long j = k - prev_total;

    cout << i << " " << j << "\n";
}

int main() {
    // 必须关闭同步，加快 cin/cout 速度
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    fast_sieve();

    int t;
    if (!(cin >> t)) return 0;
    while (t--) {
        solve();
    }

    return 0;
}
