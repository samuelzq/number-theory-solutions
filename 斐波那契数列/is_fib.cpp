/**
 * https://www.hackerrank.com/challenges/is-fibo/problem
 *
 * @File:   is_fib.cpp
 * @Author: Lao Zhang samuelzhang77@outlook.com
 * @Date:   2026-02-01
 *
 */
#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);

/*
 * Complete the 'isFibo' function below.
 *
 * The function is expected to return a STRING.
 * The function accepts LONG_INTEGER n as parameter.
 */

string isFibo(long n) {
    if (n < 0)
        return "IsNotFibo";

	long a, b, c;
	a = 0;
	b = 1;

	while (b < n) {
		c = a + b;
		a = b;
		b = c;
	}

	if (b == n)
		return "IsFibo";
	else
        return "IsNotFibo";
}

int main()
{

	int t;
	cin >> t;

	while (t--) {
		int n;
		cin >> n;

        string result = isFibo(n);

        cout << result << "\n";
    }


    return 0;
}
