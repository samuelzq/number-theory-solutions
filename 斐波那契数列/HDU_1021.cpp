/**
 * https://vjudge.net/problem/HDU-1021/origin
 * https://vjudge.net/problem/HDU-1021
 *
 * @File:   HDU_1021.cpp
 * @Author: Lao Zhang samuelzhang77@outlook.com
 * @Date:   2026-02-07
 *
 */
#include <iostream>
using namespace std;

int main() {
    int n;

    while (cin >> n) {
        if (n == 0) {
            cout << "no" << endl;  // F(0)=7 mod 3 = 1
        } else if (n == 1) {
            cout << "no" << endl;  // F(1)=11 mod 3 = 2
        } else {
            // 动态规划计算模3的值
            int f_prev2 = 1;  // F(0) mod 3 = 7 mod 3 = 1
            int f_prev1 = 2;  // F(1) mod 3 = 11 mod 3 = 2
            int f_current;

            for (int i = 2; i <= n; i++) {
                f_current = (f_prev1 + f_prev2) % 3;
                f_prev2 = f_prev1;
                f_prev1 = f_current;
            }

            if (f_current == 0) {
                cout << "yes" << endl;
            } else {
                cout << "no" << endl;
            }
        }
    }

    return 0;
}
