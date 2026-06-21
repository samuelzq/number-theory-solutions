/**
 * https://www.spoj.com/problems/VECTAR8/
 *
 * @File:   spoj_VECTAR8.cpp
 * @Author: Lao Zhang samuelzhang77@outlook.com
 * @Date:   2026-02-08
 *
 */
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

const int MAX_N = 1000000;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // 筛法求质数
    vector<bool> is_prime(MAX_N + 1, true);
    is_prime[0] = is_prime[1] = false;

    for (int i = 2; i * i <= MAX_N; i++) {
        if (is_prime[i]) {
            for (int j = i * i; j <= MAX_N; j += i) {
                is_prime[j] = false;
            }
        }
    }

    // 1位数开始构建恐惧质数
    vector<bool> is_afraid(MAX_N + 1, false);

    // 初始化1位数恐惧质数
    vector<int> afraid_primes = {2, 3, 5, 7};
    for (int p : afraid_primes) {
        is_afraid[p] = true;
    }

    // 构建更多位数的恐惧质数
    vector<int> current = afraid_primes;

    // BFS: 按位数分层构造
    for (int digits = 2; digits <= 6; digits++) {  // N<10^6，最多6位数
        vector<int> next_level;      // 每一轮 digits 循环开始时都会被重新定义，因此会被“清空” 
        for (int prime : current) {  // current 存储当前位数的“恐惧质数”
            // 在当前质数前面加上1-9的数字
            for (int d = 1; d <= 9; d++) {
                // 计算新数字
                int new_num = d;
                int temp = prime;
                int multiplier = 1;

                // 计算需要的倍数
                while (temp > 0) {
                    multiplier *= 10;
                    temp /= 10;
                }

                new_num = d * multiplier + prime;

                if (new_num > MAX_N) continue;

                if (is_prime[new_num]) {
                    // 新数需要检查所有截断，但由于我们是递推构建的，
                    // 所以只需检查new_num本身是否为质数
                    is_afraid[new_num] = true;
                    next_level.push_back(new_num);
                }
            }
        }

        current = next_level;    // 保留“新生成的合法结果”。
    }

    // 计算前缀和
    vector<int> prefix(MAX_N + 1, 0);
    int count = 0;
    for (int i = 2; i <= MAX_N; i++) {
        if (is_afraid[i]) count++;
        prefix[i] = count;
    }

    // 处理查询
    int T;
    cin >> T;

    while (T--) {
        int N;
        cin >> N;
        cout << prefix[N] << '\n';
    }

    return 0;
}
	
