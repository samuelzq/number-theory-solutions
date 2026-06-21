/**
 * SPOJ - Namit in Trouble
 * https://www.spoj.com/problems/NGIRL/
 * https://vjudge.net/problem/SPOJ-NGIRL
 *
 * 只有三个因数的数一定是质数的平方。
 *
 * @File:   spoj_ngirl.cpp
 * @Author: Lao Zhang <samuelzhang77@yahoo.com>
 * @Date:   2021-12-31
 *
 **/
#include <bits/stdc++.h>

using namespace std;

const int N = 110005;       // N最大值10^10，取其平方根上限
vector<bool> is_prime(N, true);
vector<long long> primes;

void sieve(void)
{
	is_prime[0] = is_prime[1] = false;

	for (int i = 2; i * i <= N; i++) {
		if (is_prime[i]) {
			for (int j = i * i; j <= N; j += i)
				is_prime[j] = false;
		}
	}

	for (int i = 2; i <= N; i++) {
		if (is_prime[i])
			primes.push_back(i);
	}
}

int main()
{
	long long t, n, k;

	sieve();
	cin >> t;
	while (t--) {
		long long cnt, ncnt;
		cin >> n >> k;
		cnt = ncnt = 0;
		for (vector<long long>::iterator it = primes.begin(); it != primes.end(); it++) {
			long long tmp = (*it) * (*it);
			if (tmp > n)
				break;
			if (tmp > k)
				ncnt++;
			cnt++;
		}
		cout << cnt << ' ' << ncnt << '\n';
	}
	return 0;
}
