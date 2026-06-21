/**
 * https://www.spoj.com/problems/TDPRIMES/
 * https://vjudge.net/problem/SPOJ-TDPRIMES
 *
 * @File:   SPOJ_TDPRIMES.cpp
 * @Author: Lao Zhang samuelzhang77@outlook.com
 * @Date:   2026-02-08
 *
 */
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

const long long N = 100000000;  // 10^8
const int BLOCK_SIZE = 100000;  // 每块处理10^5个数

int main() {
    // 第一步：生成所有不超过 sqrt(N) 的质数
    int limit = sqrt(N) + 1;
    vector<bool> base_sieve(limit + 1, true);
    vector<int> primes;

    base_sieve[0] = base_sieve[1] = false;
    for (int i = 2; i <= limit; i++) {
        if (base_sieve[i]) {
            primes.push_back(i);
            for (int j = i * i; j <= limit; j += i) {
                base_sieve[j] = false;
            }
        }
    }

    // 第二步：分段筛选并输出
    int total_count = 1;

    // 先单独处理2
    cout << 2 << "\n";

    // 从3开始分段处理
    for (long long low = 3; low <= N; low += BLOCK_SIZE) {
        long long high = min(low + BLOCK_SIZE - 1, N);

        // 创建当前块的标记数组
        vector<bool> block(high - low + 1, true);

        // 用基础质数筛选当前块
        for (int p : primes) {
            if (p * p > high) break;

            // 找到当前块内第一个p的倍数
            long long start = max((long long)p * p,
                                 ((low + p - 1) / p) * p);

            // 标记所有倍数
            for (long long j = start; j <= high; j += p) {
                if (j >= low) {  // 确保在块内
                    block[j - low] = false;
                }
            }
        }

        // 输出当前块内符合要求的质数
        // 注意：只检查奇数，因为偶数不是质数（除了2）
        for (long long i = max(low, 3LL); i <= high; i++) {
            if (i % 2 == 0) continue;  // 跳过偶数

            if (block[i - low]) {
                total_count++;
                if (total_count % 100 == 1) {
                    cout << i << "\n";
                }
            }
        }
    }

    return 0;
}
