/**
 * https://www.spoj.com/problems/PRIMES2/
 *
 * @File:   spoj_primes2.cpp
 * @Author: Lao Zhang samuelzhang77@outlook.com
 * @Date:   2026-02-18
 *
 */
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

const int LIMIT = 1000000000;
const int SQRT_LIMIT = 31622;
const int S = 1 << 17; // 128KB，完美契合 L1/L2 Cache

bool is_p[SQRT_LIMIT + 1];
int base_primes[4000], p_cnt = 0;   //  1 ~ 31622 质数的精确个数是 3,401 个
int next_indices[4000]; // 存储每个基础素数在当前块的起始偏移
char mark[S];

void precompute() {
    fill(is_p + 2, is_p + SQRT_LIMIT + 1, true);
    for (int i = 2; i * i <= SQRT_LIMIT; i++) {
        if (is_p[i]) {
            for (int j = i * i; j <= SQRT_LIMIT; j += i)
                is_p[j] = false;
        }
    }
    for (int i = 3; i <= SQRT_LIMIT; i++) {
        if (is_p[i]) {
            base_primes[p_cnt] = i;
            // 预计算初始偏移：从该素数的平方开始筛
            next_indices[p_cnt] = (i * i - 1) / 2;
            p_cnt++;
        }
    }
}

int main() {
    precompute();

    int total_count = 1; // 2 是第一个
    printf("2\n");

    for (int low = 0; low < LIMIT; low += 2 * S) {
        fill(mark, mark + S, 0);
        int high = min(low + 2 * S, LIMIT);

        for (int i = 0; i < p_cnt; i++) {
            int p = base_primes[i];
            int j = next_indices[i];

            // 核心筛选循环：使用指针或紧凑循环
            while (j < S) {
                mark[j] = 1;
                j += p;
            }
            // 更新该素数在下一个分块中的起始位置
            next_indices[i] = j - S;
        }

        // 统计当前块中的素数
        for (int i = 0; i < S; i++) {
            int n = low + 2 * i + 1;
            if (n >= LIMIT) break;
            if (n <= 1) continue;

            if (!mark[i]) {
                total_count++;
                if ((total_count - 1) % 500 == 0) {
                    printf("%d\n", n);
                }
            }
        }
    }

    return 0;
}
