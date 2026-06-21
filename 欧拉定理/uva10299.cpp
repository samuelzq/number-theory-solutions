
/**
 * UVA #10299 "Relatives" [Difficulty: Easy]
 * https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1240
 * https://vjudge.net/problem/UVA-10299
 *
 * 直接使用欧拉公式解决。
 *
 * @File:   uva10299.cpp
 * @Author: Lao Zhang <samuelzhang77@yahoo.com>
 * @Date:   2022-01-19
 *
 **/
#include <bits/stdc++.h>

using namespace std;

int phi(int n) {
	int result = n;

	if (n == 1)
		return 0;

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
