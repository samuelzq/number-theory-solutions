/**
 * https://www.luogu.com.cn/problem/P1835
 *
 * @File:   P1835.cpp
 * @Author: Lao Zhang samuelzhang77@outlook.com
 * @Date:   2026-03-28
 *
 */
#include <iostream>
#include <vector>
#include <cmath>
#include <cstring>
using namespace std;

typedef long long ll;

const int MAXN = 50000;  // sqrt(2^31) ≈ 46341，取 50000 足够
const int MAXM = 1000005;  // 区间长度最大值

vector<int> lp(MAXN + 1);  // 存储最小质因子
vector<int> primes;        // 存储素数
bool isPrimeInRange[MAXM];  // 标记区间 [L, R] 内的数是否为素数

// 线性筛预处理小素数（使用统一模版）
void linearSieve(int n) {
    for (int i = 2; i <= n; ++i) {
        if (lp[i] == 0) {
            lp[i] = i;          // i 是素数，最小质因子是自身
            primes.push_back(i);
        }
        for (int j = 0; i * primes[j] <= n; ++j) {
            lp[i * primes[j]] = primes[j];  // 记录最小质因子
            if (primes[j] == lp[i]) {       // 关键：primes[j] 是 i 的最小质因子
                break;
            }
        }
    }
}

// 区间筛法
int intervalSieve(ll L, ll R) {
    // 初始化，先假设区间内所有数都是素数
    memset(isPrimeInRange, true, sizeof(isPrimeInRange));

    // 特殊处理 L = 1 的情况
    if (L == 1) {
        isPrimeInRange[0] = false;  // 1 不是素数
    }

    // 用每个小素数去筛区间内的合数
    for (int p : primes) {
        // 如果 p^2 > R，则 p 不可能再筛掉区间内的任何数
        if ((ll)p * p > R) {
            break;
        }

        // 找到区间内第一个 p 的倍数
        // 从 max(p * p, ceil(L / p) * p) 开始
        ll start = max((ll)p * p, (L + p - 1) / p * p);

        // 标记所有 p 的倍数为合数
        for (ll j = start; j <= R; j += p)
            isPrimeInRange[j - L] = false;
    }

    // 统计素数个数
    int count = 0;
    for (ll i = L; i <= R; i++) {
        if (isPrimeInRange[i - L]) {
            count++;
        }
    }

    return count;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll L, R;
    cin >> L >> R;

    // 预处理 sqrt(R) 以内的所有素数
    int limit = sqrt(R) + 5;  // 多筛一点确保安全
    linearSieve(limit);

    // 区间筛法统计素数个数
    int ans = intervalSieve(L, R);

    cout << ans << endl;

    return 0;
}
