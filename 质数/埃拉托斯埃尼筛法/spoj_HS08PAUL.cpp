/**
 * https://www.spoj.com/problems/HS08PAUL/
 *
 * @File:   spoj_HS08PAUL.cpp
 * @Author: Lao Zhang samuelzhang77@outlook.com
 * @Date:   2026-02-08
 *
 */
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

const int MAX_N = 10000000;      // n的最大值
const int MAX_Y = 57;            // 因为 57^4 = 10556001 > 10^7

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // 步骤1：标记所有形如 x² + y⁴ 的数
    vector<bool> is_form(MAX_N + 1, false);

    // 枚举 y
    for (int y = 0; y <= MAX_Y; y++) {
        long long y4 = (long long)y * y * y * y;
        if (y4 > MAX_N) break;

        // 枚举 x
        int max_x = sqrt(MAX_N - y4);
        for (int x = 0; x <= max_x; x++) {
            long long num = (long long)x * x + y4;
            if (num <= MAX_N) {
                is_form[num] = true;
            }
        }
    }

    // 步骤2：筛法求质数，并标记满足条件的质数
    vector<bool> is_prime(MAX_N + 1, true);
    vector<int> prefix_count(MAX_N + 1, 0);  // 前缀和

    is_prime[0] = is_prime[1] = false;

    int count = 0;
    for (int i = 2; i <= MAX_N; i++) {
        if (is_prime[i]) {
            // 标记 i 的倍数
            if ((long long)i * i <= MAX_N) {
                for (int j = i * i; j <= MAX_N; j += i) {
                    is_prime[j] = false;
                }
            }

            // 如果 i 是满足条件的质数
            if (is_form[i]) {
                count++;
            }
        }
        prefix_count[i] = count;
    }

    // 步骤3：处理查询
    int T;
    cin >> T;

    while (T--) {
        int n;
        cin >> n;
        cout << prefix_count[n] << "\n";
    }

    return 0;
}
