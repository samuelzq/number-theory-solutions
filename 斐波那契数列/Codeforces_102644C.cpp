/**
 * https://codeforces.com/problemset/gymProblem/102644/C
 *
 * @File:   Codeforces_102644C.cpp
 * @Author: Lao Zhang samuelzhang77@outlook.com
 * @Date:   2026-02-07
 *
 */

#include <bits/stdc++.h>

using namespace std;
const int mod = 1000000007;

pair<long long, long long> fib (long long n)
{
	if (n == 0)
		return {0, 1};

	auto p = fib(n >> 1);
	long long c = p.first * ((2 * p.second - p.first + mod) % mod) % mod;
	long long d = (p.first * p.first % mod + p.second * p.second % mod) % mod;
	if (n & 1)
		return {d, (c + d) % mod};
	else
		return {c, d};
}

int main(void)
{
	long long n;
	cin >> n;

	pair<int, int> ans;
	ans = fib(n);
	cout << ans.first << endl;

	return 0;
}
