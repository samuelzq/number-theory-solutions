/**
 * http://poj.org/problem?id=3070
 * https://vjudge.net/problem/POJ-3070
 *
 * @File:   POJ_3070.cpp
 * @Author: Lao Zhang samuelzhang77@outlook.com
 * @Date:   2026-02-07
 *
 */
#include <iostream>
#include <vector>
using namespace std;

const int MOD = 10000;  // 我们需要最后4位，所以模10000

// 2x2矩阵乘法，结果模10000
vector<vector<int>> multiply(const vector<vector<int>>& a, const vector<vector<int>>& b) {
    vector<vector<int>> result(2, vector<int>(2, 0));
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 2; k++) {
                result[i][j] = (result[i][j] + a[i][k] * b[k][j]) % MOD;
            }
        }
    }
    return result;
}

// 矩阵快速幂，计算矩阵base的exp次幂
vector<vector<int>> matrixPower(vector<vector<int>> base, long long exp) {
    vector<vector<int>> result = {{1, 0}, {0, 1}};  // 单位矩阵

    while (exp > 0) {
        if (exp & 1) {  // 如果当前位为1
            result = multiply(result, base);
        }
        base = multiply(base, base);  // 矩阵平方
        exp >>= 1;  // 指数右移一位
    }

    return result;
}

// 计算第n个斐波那契数的最后4位
int fibonacciLast4(long long n) {
    if (n == 0) return 0;
    if (n == 1) return 1;

    // 斐波那契矩阵: [[1,1],[1,0]]
    vector<vector<int>> base = {{1, 1}, {1, 0}};

    // 计算矩阵的(n-1)次幂
    // 公式: [[1,1],[1,0]]^(n-1) = [[F(n), F(n-1)], [F(n-1), F(n-2)]]
    vector<vector<int>> result = matrixPower(base, n - 1);

    // 结果矩阵的左上角元素就是F(n)
    return result[0][0] % MOD;
}

int main() {
    long long n;

    // 持续读取测试用例，直到遇到-1
    while (cin >> n && n != -1) {
        // 计算并输出结果
        int result = fibonacciLast4(n);

        // 直接输出结果，C++会自动省略前导零
        // 如果结果是0，就输出0
        cout << result << endl;
    }

    return 0;
}
