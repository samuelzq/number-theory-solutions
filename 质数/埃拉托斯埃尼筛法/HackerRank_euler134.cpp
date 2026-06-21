/**
 * Project Euler - Prime pair connection
 * https://www.hackerrank.com/contests/projecteuler/challenges/euler134/problem
 * https://vjudge.net/problem/HackerRank-euler134
 *
 * @File:   HackerRank_euler134.cpp
 * @Author: Lao Zhang samuelzhang77@outlook.com
 * @Date:   2026-02-09
 *
 */
#include <bits/stdc++.h>

using namespace std;

const int N = 2e6;
int cnt = 0;
long long primes[N];
vector<char> isPrime(N);
int ans[100];

// 扩展欧几里得算法
long long ext_gcd(long long a, long long b, long long &x, long long &y)
{
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }

    long long x1, y1;
    long long d = ext_gcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a / b);
    return d;
}

// 筛法生成质数
void sieve()
{
    // 生成所有质数到 sqrt(R) 的范围
    for (long long i = 3; i * i <= N; i += 2) {
        if (!isPrime[i]) {
            for (long long j = i * i; j <= N; j += i)
                isPrime[j] = true;
        }
    }

    cnt = 0;
    primes[cnt++] = 2;
    for (int i = 3; i <= N; i += 2) {
        if (isPrime[i] == false)
            primes[cnt++] = i;
    }
}

int main(void)
{
    int t;

    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    sieve();
    cin >> t;
    while (t--) {
        long long l, r, sum, p1;
        cin >> l >> r;

        // 使用分段筛法生成区间 [l, r+500] 内的质数
        // 需要 r+500 是为了确保能获取到 r 后面的质数（需要连续质数对）
        for (int i = 0; i <= r - l + 1000 ; i++)
            isPrime[i] = true;

        for (long long k = 0; k < cnt; k++) {
            long long prime = primes[k];
            for (long long j = max(prime * prime, (l + prime - 1) / prime * prime); j <= r + 500; j += prime) {
                isPrime[j - l] = false;
            }
        }

        p1 = sum = 0;
        for (int i = 0; i < 100; i++)
            ans[i] = 0;

        // 遍历从 l 到 r+1000 的所有数，寻找质数
        for (long long current = l; current < r + 1000; current++) {
            if (p1 > r)  // 如果前一个质数已经超过 r，停止
                break;

            if (isPrime[current - l] == false)  // 不是质数，跳过
                continue;

            if (p1 == 0) {  // 找到第一个质数
                p1 = current;
                continue;
            }

            // 找到连续质数对 (p1, p2)，其中 p2 = current
            long long p2 = current;

            // 计算 10^k，其中 k 是 p1 的位数
            long long temp_p1 = p1;
            long long power_of_10 = 1;
            int digit_count = 0;
            while (temp_p1) {
                digit_count++;
                temp_p1 /= 10;
                power_of_10 *= 10;
            }

            // 使用扩展欧几里得算法求解 S
            // 我们需要解: S ≡ p1 (mod 10^k) 且 S ≡ 0 (mod p2)
            // 设 S = x * 10^k + p1，则 x * 10^k + p1 ≡ 0 (mod p2)
            // 所以 x * 10^k ≡ -p1 (mod p2) ≡ p2 - p1 (mod p2)

            long long x, y;
            ext_gcd(power_of_10, p2, x, y);  // 求解 10^k * x ≡ 1 (mod p2)
            x = x * (p2 - p1) % p2;           // 调整 x 使得 10^k * x ≡ p2 - p1 (mod p2)
            if (x < 0)
                x += p2;

            // 计算 S = x * 10^k + p1
            long long S = x * power_of_10 + p1;

            // 将 S 加到结果中（大数加法）
            long long tmp = S;
            for (long long k = 0, carry = 0; k < 40; k++) {
                ans[k] += (tmp % 10 + carry);
                carry = ans[k] / 10;
                ans[k] %= 10;
                tmp /= 10;
            }

            // 更新 p1 为当前质数，为下一对做准备
            p1 = p2;
        }

        // 输出结果（大数输出）
        int i = 40;
        while (ans[i] == 0 && i >= 0)
            i--;
        if (i < 0) {
            cout << "0";
        } else {
            while (i >= 0)
                cout << ans[i--];
        }
        cout << '\n';
    }
    return 0;
}
