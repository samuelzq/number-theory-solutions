/**
 * https://www.hackerrank.com/contests/projecteuler/challenges/euler002/problem
 *
 * @File:   even_fib.cpp
 * @Author: Lao Zhang samuelzhang77@outlook.com
 * @Date:   2026-02-01
 *
 */
#include <iostream>
using namespace std;

int main() {
    int T;
    cin >> T;
    while (T--) {
        long long N;
        cin >> N;

        long long a = 1, b = 2;  // 题目定义：F1=1, F2=2
        long long sum = 0;

        while (a <= N) {
            if (a % 2 == 0) {
                sum += a;
            }
            long long next = a + b;
            a = b;
            b = next;
        }

        cout << sum << '\n';
    }
    return 0;
}
