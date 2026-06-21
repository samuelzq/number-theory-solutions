/**
 *
 * @File:   spoj_prime2.cpp
 * @Author: Lao Zhang samuelzhang77@outlook.com
 * @Date:   2026-02-18
 *
 */
#include <iostream>
#include <vector>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <bitset>

using namespace std;

typedef long long ll;

const int MAX_N = 1000000000;
const int SEGMENT_SIZE = 1000000;
const int SQRT_MAX = 31623;

vector<int> base_primes;

/**
 * 生成基础质数表
 */
void generate_base_primes() {
    vector<bool> is_prime(SQRT_MAX + 1, true);
    is_prime[0] = is_prime[1] = false;

    for (int i = 2; i * i <= SQRT_MAX; i++) {
        if (is_prime[i]) {
            for (int j = i * i; j <= SQRT_MAX; j += i) {
                is_prime[j] = false;
            }
        }
    }

    base_primes.reserve(3401);  // π(31623) ≈ 3401
    for (int i = 2; i <= SQRT_MAX; i++) {
        if (is_prime[i]) {
            base_primes.push_back(i);
        }
    }
}

/**
 * 分段筛法主函数
 */
void segmented_sieve() {
    ll prime_count = 0;

    // 使用bitset进行位压缩
    vector<bool> segment(SEGMENT_SIZE, true);

    for (ll low = 2; low <= MAX_N; low += SEGMENT_SIZE) {
        ll high = min(low + SEGMENT_SIZE - 1, (ll)MAX_N);
        int seg_len = high - low + 1;

        // 重置当前段
        fill(segment.begin(), segment.begin() + seg_len, true);

        // 用基础质数筛选
        for (int p : base_primes) {
            if ((ll)p * p > high) break;

            ll start = max((ll)p * p, (low + p - 1) / p * p);

            // 优化：对于奇数质数，只处理奇数倍
            if (p == 2) {
                for (ll j = start; j <= high; j += p) {
                    segment[j - low] = false;
                }
            } else {
                if (start % 2 == 0) start += p;  // 确保从奇数开始
                for (ll j = start; j <= high; j += 2 * p) {  // 步长2p，跳过偶数倍
                    segment[j - low] = false;
                }
            }
        }

        // 收集质数
        for (int i = 0; i < seg_len; i++) {
            if (segment[i]) {
                prime_count++;
                if (prime_count % 500 == 1) {
                    cout << (low + i) << "\n";
                }
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    generate_base_primes();
    segmented_sieve();

    return 0;
}
