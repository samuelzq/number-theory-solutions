/**
 * UVA 12995 - Farey Sequence
 * https://vjudge.net/problem/UVA-12995
 *
 * @File:   uva12995.cpp
 * @Author: Lao Zhang <samuelzhang77@yahoo.com>
 * @Date:   2022-01-20
 *
 **/
#include <bits/stdc++.h>

using namespace std;

const int N = 1e6;
int phi[N + 1];
long long f[N + 1];

void phi_one2n(void)
{
	for (int i = 0; i <= N; i++)
		phi[i] = i;

	for (int i = 2; i <= N; i++) {
		if (phi[i] == i) {
			for (int j = i; j <= N; j += i)
				phi[j] -= phi[j] / i;
		}
	}

	f[1] = 0;
	for (int i = 2; i <= N; i++)
		f[i] = f[i - 1] + phi[i];
}

int main(void)
{
	int n;

	phi_one2n();
	while (cin >> n && n)
		cout << f[n] << '\n';

	return 0;
}
