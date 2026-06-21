/**
 * UVA #10179 "Irreducible Basic Fractions" [Difficulty: Easy]
 * https://onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=1120
 * https://vjudge.net/problem/UVA-10179
 *
 * 直接使用欧拉公式解决。
 *
 * @File:   uva10179.cpp
 * @Author: Lao Zhang <samuelzhang77@yahoo.com>
 * @Date:   2022-01-19
 *
 **/
#include <bits/stdc++.h>

using namespace std;

int phi(int n) {
	int result = n;
	for (int i = 2; i * i <= n; i++) {
		if (n % i == 0) {
			while (n % i == 0)
				n /= i;
			result -= result / i;
		}
	}
	if (n > 1)
		result -= result / n;
	return result;
}

int main(void)
{
	int n;

	while (cin >> n && n) {
		cout << phi(n) << '\n';
	}
	return 0;
}

