/**
 * SPOJ-MAIN74
 * https://www.spoj.com/problems/MAIN74/en/
 * https://vjudge.net/problem/SPOJ-MAIN74
 *
 * 本题需要分段考虑：
 *     n=0时，无解输出0；
 *     n=1时，只可能是2；
 *     n>1时，实质上是求第n+2个斐波拿契数
 *
 * @File      spoj_main74.cpp
 * @Author    Lao Zhang <samuelzhang77@yahoo.com>
 * @Date      12-20-2021
 *
 **/

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
	int k;

	cin >> k;

	while (k--) {
		long long n;
		cin >> n;

		if (n == 0) {
			cout << "0\n";
			continue;
		} else if (n == 1) {
			cout << "2\n";
			continue;
		} else {
			pair<int, int> ans;
			ans = fib(n + 1);
			cout << (ans.first + ans.second) % mod << endl;
		}
	}
	return 0;
}
