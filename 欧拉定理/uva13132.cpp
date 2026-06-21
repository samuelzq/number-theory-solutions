/**
 * UVA 13132 - Laser Mirrors
 * https://vjudge.net/problem/UVA-13132
 *
 * 做出选择的 X 必须和 N 互质，这样才能保证反射后再次回到起点。
 *
 * @File:   uva13132.cpp
 * @Author: Lao Zhang <samuelzhang77@yahoo.com>
 * @Date:   2022-01-20
 *
 **/
#include <bits/stdc++.h>

using namespace std;
const int N = 1e5;
int phi[N + 1];

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
}

int main(void)
{
	int t;

	phi_one2n();
	cin >> t;
	while (t--) {
		int n;
		cin >> n;
		cout << phi[n] << '\n';
	}
	return 0;
}
