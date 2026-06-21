/**
 * https://dmoj.ca/problem/fibonacci
 * https://vjudge.net/problem/DMOJ-fibonacci
 *
 * @File:   DMOJ_fibonacci.cpp
 * @Author: Lao Zhang samuelzhang77@outlook.com
 * @Date:   2026-02-01
 *
 */
#include <bits/stdc++.h>

using namespace std;

const long long MOD = 1000000007LL;
#define ll long long


pair<ll, ll> fib (unsigned ll n) {
    if (n == 0)
        return {0, 1};

    auto p = fib(n >> 1);
    ll c = p.first * ((2 * p.second % MOD - p.first + MOD) % MOD) % MOD;
    ll d = (p.first * p.first % MOD + p.second * p.second % MOD) % MOD;
    if (n & 1)
        return {d, (c + d) % MOD};
    else
        return {c, d};
}

int main(void)
{
	unsigned long long int n;

	cin >> n;
	cout << fib(n).first << endl;
	return 0;
}
