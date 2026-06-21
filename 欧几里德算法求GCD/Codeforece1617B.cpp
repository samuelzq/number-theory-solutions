/**
 * https://codeforces.com/problemset/problem/1617/B
 *
 * @File:   CF1617B.cpp
 * @Author: Lao Zhang <samuelzhang77@yahoo.com>
 * @Date:   2024-06-11
 *
 **/
#include <bits/stdc++.h>
using namespace std;

int gcd(int a, int b)
{
	return (b) ? gcd(b, a % b) : a;
}

int main(void)
{
	int t;

	cin >> t;
	while (t--) {
		bool f = false;
		int n;

		cin >> n;
		for (int c = 1; c < n; c++) {
			for (int b = c * 2; b < n - c; b += c) {
				int a;
				a = n - c - b;
				if (c == gcd(a, b)) {
					cout << a << ' ' << b << ' ' << c << endl;
					f = true;
					break;
				}
			}
			if (f)
				break;
		}
	}
	return 0;
}
