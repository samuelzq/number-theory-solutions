/**
 * https://www.spoj.com/problems/FIBOSUM/en/
 * https://vjudge.net/problem/SPOJ-FIBOSUM
 *
 * @File:   SPOJ-FIBOSUM.cpp
 * @Author: Lao Zhang samuelzhang77@outlook.com
 * @Date:   2026-02-01
 *
 */
#include <bits/stdc++.h>

using namespace std;
const int mod = 1000000007;

pair<long long, long long> fib(long long n)
{
	if (n == 0)
		return {0, 1};

	auto p = fib(n >> 1);
	long long a, b;
	a = p.first * ((2 * p.second % mod - p.first + mod) % mod) % mod;
	b = (p.first * p.first % mod + p.second * p.second % mod) % mod;

	if (!(n & 1))
		return {a, b};
	else
		return {b, (a + b) % mod};
}

int main(void)
{
	int k;
	cin >> k;

	while (k--) {
		long long l, r;
		pair<long long, long long> p1(0, 1);
		cin >> l >> r;
		if (l > 0)
			p1 = fib(l - 1);
		auto p2 = fib(r);

		long long sum1, sum2, sum;
		sum1 = (p1.first + p1.second - 1) % mod;
		sum2 = (p2.first + p2.second - 1) % mod;
		sum = (sum2 - sum1 + mod) % mod;
		cout << sum << '\n';
	}
	return 0;
}
